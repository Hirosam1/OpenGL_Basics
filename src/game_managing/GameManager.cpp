#include "game_managing/GameManager.hpp"

GameManager::GameManager(std::string game_name,int width, int height)
:game_name(game_name),width(width),height(height),current_width(width),current_height(height),ready_to_start(false){
}

void GameManager::EngineInit(){
    //Checking libs
    std::cout<<"setting up libs...\n";
    if(!glfwInit()){
        std::cout<< "An error occured while initilizing the libs!" << "\n";
        exit(-1);
    }

    glfwSetErrorCallback(this->ErrorCallback);
    std::cout<<"creating the window...\n";
    this->main_window = new Window(this->width,this->height,this->game_name);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout<<"Error while initilazing GLAD\n";
    exit(-1);
    }

    this->main_input = new InputManager(this->main_window);
    this->main_time = new Time();

    this->all_objs = new std::vector<GameObject*>();
    this->all_lights = std::vector<Light*>();

    this->basic_block = new BasicsBlock(main_window,main_input,main_time, this->all_objs);

    glfwSetWindowUserPointer(this->main_window->GetWindow(),this->basic_block);

    this->supported_concurrency = std::thread::hardware_concurrency()-1;
    this->threads = new std::thread[this->supported_concurrency];


    SetUpObjects();

    this->ready_to_start = true;
    glEnable(GL_DITHER);
    Debugging::SetPointsSize(10);    
    glEnable(GL_DEPTH_TEST);
    glfwSwapInterval(1);
    //Update their info
    for(int i = 0; i < this->supported_concurrency; i++){
        this->threads[i] = std::thread(UpdateObjects,i,this->all_objs,supported_concurrency,main_window, &mtx, &lock_threads);
    }

}


void GameManager::SetUpObjects(){
    std::string* vertDefault = new std::string("shaders/vertex_shaders/MVP_vertex.vert");
    std::string* vertTex = new std::string("shaders/vertex_shaders/MVP_texture_vertex.vert");
    std::string* fragTex = new std::string("shaders/fragment_shaders/texture_light.frag");
    std::string* fragSpec = new std::string("shaders/fragment_shaders/textureSpecular_light.frag");
    std::string* fragDefault = new std::string("shaders/fragment_shaders/light.frag");
    std::string* lamp = new std::string("shaders/fragment_shaders/lamp.frag");


    m_camera = new Camera(this->main_window);
    m_camera->camera_pos = glm::vec3(-3.0f,2.0f,20.0f);
    m_camera->camera_front = glm::vec3(0,0,-1);
     m_camera->LookAt(m_camera->camera_pos+ m_camera->camera_front);
    std::cout<<"creating game objects...\n";

    Shader* shader = new Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/BasicLight.frag");
    Shader* shader_lamp = new Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/lamp.frag");
    std::string path_nanoSuit = std::string("models/nanosuit_simple/nanosuit.obj");
    std::string path_box = std::string("models/box/Box.obj");
    Model* box = new Model(path_box);
    Model* nano_suit = new Model(path_nanoSuit);

    GameObject* pointLight = new PointLight(basic_block,m_camera,box,new float[3]{-1,-2.2,2},shader_lamp,basic_block->n_point_lights++);
    pointLight->model_mat = glm::scale(pointLight->model_mat,glm::vec3(0.2,0.2,0.2));
    dynamic_cast<Light*>(pointLight)->light_color = glm::vec3(0.97,0.0,1.00);
    pointLight->object_name = "Point Light1";

    GameObject* pointLight2 = new  PointLight(basic_block,m_camera,box,new float[3]{2,1,-3},shader_lamp,basic_block->n_point_lights++);
    pointLight2->model_mat = glm::scale(pointLight2->model_mat,glm::vec3(0.2,0.2,0.2));
    dynamic_cast<Light*>(pointLight2)->light_color = glm::vec3(0.0,0.44,1.00);
    pointLight2->object_name = "Point Light 2";


    GameObject* spotLight = new SpotLight(basic_block,m_camera,glm::value_ptr(m_camera->camera_pos),glm::value_ptr(m_camera->camera_front));
    spotLight->object_name = "Spot Light";
    GameObject* GUIObject = new bObject(this->basic_block ,m_camera,new float[3]{0.0f,0.0f,0.0f});
    GUIObject->object_name = "GUI gameObject";

    GameObject* CameraMov = new aObject(this->basic_block,m_camera,new float[3]{0.0f,0.0f,0.0f});
    CameraMov->object_name = "Camera Movement Game Object";

    GameObject* NanoSuit = new NoBahaviorObject(basic_block,m_camera, nano_suit, new float[3]{0,-2,1},shader);
    NanoSuit->model_mat = glm::scale(NanoSuit->model_mat,glm::vec3(0.2,0.2,0.2));
    NanoSuit->object_name = "NanoSuit";

    GameObject* Box = new NoBahaviorObject(basic_block,m_camera,box,new float[3]{2,-1,1},shader);
    Box->object_name = "Box";
    Box->model_mat = glm::scale(Box->model_mat,glm::vec3(0.5,0.5,0.5));

    all_objs->push_back(CameraMov);
    all_objs->push_back(NanoSuit);
    all_objs->push_back(Box);
    all_objs->push_back(pointLight);
    all_objs->push_back(pointLight2);
    all_objs->push_back(spotLight);
    //UI needs to be last?
    all_objs->push_back(GUIObject);
    
    all_lights.push_back(dynamic_cast<Light*>(pointLight));
    all_lights.push_back(dynamic_cast<Light*>(pointLight2));
    all_lights.push_back(dynamic_cast<Light*>(spotLight));

    vertDefault->clear();
    vertTex->clear();
    fragTex->clear();
    fragSpec->clear();
    fragDefault->clear();
    lamp->clear();

    delete vertDefault;
    delete vertTex;
    delete fragTex;
    delete fragSpec;
    delete fragDefault;
    delete lamp;


}

void GameManager::UpdateObjects(int id, std::vector<GameObject*>* all_objs,
        unsigned int supported_concurrency,Window* window,
        std::mutex *mtx, std::condition_variable *wait_main){
    //Create its lock based on shared mutex, don't need to lock at this point that is why defer_lock
    std::unique_lock<std::mutex> lck(*mtx, std::defer_lock);

    while(!glfwWindowShouldClose(window->GetWindow())){
        int i = 0;
        int pos = 0;
        lck.lock();
        wait_main->wait(lck);
        lck.unlock();
        //Update all minus the last one
        while(all_objs->size() > 0 && pos < all_objs->size()-1){
            pos = id + supported_concurrency * i++;
            if (pos < all_objs->size()-1){
                all_objs->at(pos)->Update();
            }
        }
    
    }

}

void GameManager::EngnieStart(){
    std::unique_lock<std::mutex> lck(mtx,std::defer_lock);
    if(!this->ready_to_start){
        std::cout<<"Engine is not ready to start run EngineInit\n";
        exit(-1);
    }

    std::cout<<"Ready to start!\n";
    //Execute Ready for all objects
    for(auto it = this->all_objs->begin(); it != this->all_objs->end();it++){
        (*it)->ReadyObject();
    }
    while(!glfwWindowShouldClose(this->main_window->GetWindow())){
        if(this->main_input->ProcessInput(GLFW_KEY_ESCAPE,GLFW_PRESS)){
            glfwSetWindowShouldClose(this->main_window->GetWindow(),true);
        }
        
        //Clear the screen
        glClearColor(0.02f,0.06f,0.05,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        this->main_time->UpdateDelta();
        glfwPollEvents();
        /*Weird lag into position of gameobject, I belive that making a barrier after notify all will do*/
        //lock_threads.notify_all();
        //Render Objects     
        for(auto it = this->all_objs->begin(); it != this->all_objs->end() - 1;it++){
            (*it)->Update();
            if((*it)->m_shader != nullptr){
                (*it)->UseShader();
                Light* is_light = dynamic_cast<Light*>(*it);
                if(is_light == NULL){
                    for(auto lit = this->all_lights.begin(); lit != this->all_lights.end(); lit++){
                        (*lit)->LightBuffering((*it));
                    }
                }else{
                    is_light->LampColorBuffering();
                }

                (*it)->BufferAndDraw();
                glUseProgram(0);
            }
        }
        //Last object, the GUI, needs to be Updated on main thread
        all_objs->at(all_objs->size()-1)->Update();

        glfwSwapBuffers(this->main_window->GetWindow());
        this->main_input->ResetValues();

    }
    
    this->TerminateEngine();
    
}

void GameManager::TerminateEngine(){
    std::cout<<"\n==Shutiing down\n";
    //Makes sure all threads ends
    lock_threads.notify_all();
    std::cout<<"Joining Threads\n";
    for(int i = 0; i < this->supported_concurrency; i++){
        if( this->threads[i].joinable()){
            this->threads[i].join();
        }
    }
    std::cout<<"Terminate glfw\n";
    glfwTerminate();
}


void GameManager::ErrorCallback(int error, const char* description){
    std::cout<<"Error: " << error << " ->" << description<<"\n";
    exit(-1);
}

void GameManager::FrameBufferSizeCallback(GLFWwindow* windown, int width, int height){
    glViewport(0,0,width,height);
    GameManager* here = static_cast<GameManager*>(glfwGetWindowUserPointer(windown));
    here->main_window->SetWidthHeight(width,height);
    
}


