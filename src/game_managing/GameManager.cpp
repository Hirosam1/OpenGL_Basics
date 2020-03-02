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


    //SetUpObjects();

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
    std::string* tex = new std::string("textures/Arrow.png");
    std::string* tex2 = new std::string("textures/container2.png");
    std::string* spec = new std::string("textures/container2_specular.png");
    std::string* spec2 = new std::string("textures/Arrow_specular.png");

    Camera* m_camera = new Camera(this->main_window);


    Shape* cube  = new Cube();
    Shape* plane = new Plane();
    Shape* triag = new Triangle();
    Shape* cubeTex = new CubeTex();

    std::cout<<"creating game objects...\n";
    GameObject *go,*go2, *go4, * go5;

    GameObject* m_light = new PointLight(this->basic_block,m_camera,cube,new float[3]{0.3,0.5,-0.5},vertDefault,lamp,this->basic_block->n_point_lights++);
    VAO* light_vao = new VAO();
        light_vao->SetAttribPoint(3,6);
        light_vao->SetUpObject();
    m_light->SetUpVertex(light_vao);
    m_light->model = glm::scale(m_light->model,glm::vec3(0.2,0.2,0.2));
    dynamic_cast<Light*>(m_light)->light_intensity = 0.7;
    m_light->object_name = "Point Light 1";

    GameObject* light2 = new PointLight(this->basic_block,m_camera,cube,new float[3]{0.0,0.2,3.0},vertDefault,lamp,this->basic_block->n_point_lights++);
    VAO* light2_vao = new VAO();
        light2_vao->SetAttribPoint(3,6);
        light2_vao->SetUpObject();
    light2->SetUpVertex(light2_vao);
    light2->model = glm::scale(light2->model,glm::vec3(0.2,0.2,0.2));
    dynamic_cast<Light*>(light2)->light_intensity = 0.8;
    dynamic_cast<Light*>(light2)->light_color = glm::vec3(1,1,0.6);
    light2->object_name = "Point Light 2";

    GameObject* m_dirLight = new DirLight(this->basic_block,m_camera,cube,new float[3]{-0.3,-1,1.2},vertDefault,lamp);
    VAO* DirLight_vao = new VAO();
        DirLight_vao->SetAttribPoint(3,6);
        DirLight_vao->SetUpObject();
    m_dirLight->SetUpVertex(DirLight_vao);
    m_dirLight->model = glm::scale(m_dirLight->model,glm::vec3(0.4,0.4,0.4));
    dynamic_cast<Light*>(m_dirLight)->light_intensity = 0.2;
    m_dirLight->object_name = "Directional light";


    GameObject* spotLight = new SpotLight(basic_block,m_camera,glm::value_ptr(m_camera->camera_pos),glm::value_ptr(m_camera->camera_front));
    spotLight->object_name = "Spot Light";

    Texture* boxTex = new Texture(*tex2,GL_RGBA);
    Texture* boxSpec = new Texture(*spec, GL_RGBA);
    
    go = new NoBahaviorObject(this->basic_block , m_camera,cubeTex,new float[3]{0.5,-0.8,2},vertTex,fragSpec);
    go->m_material = new Material();
    go->m_material->shininess = 64.0;
    go->m_material->specular_color  = glm::vec3(0.7,0.7,0.7);
    VAO* goVAO = new VAO();
        goVAO->SetAttribPoint(3);
        goVAO->SetAttribPoint(3);
        goVAO->SetAttribPoint(2);
        goVAO->SetUpObject();
    go->SetUpVertex(goVAO);
    go->AddTexture(boxTex);
    go->AddTexture(boxSpec,new std::string("material.specular"));
    go->object_name = "Cube With Specular 1";

    go2 = new NoBahaviorObject(this->basic_block ,m_camera,plane,new float[3]{-1,0.3,0},vertTex,fragTex);
    VAO* go2VAO = new VAO();
        go2VAO->SetAttribPoint(3);
        go2VAO->SetAttribPoint(3);
        go2VAO->SetAttribPoint(2);
        go2VAO->SetUpObject();
    go2->SetUpVertex(go2VAO);
    go2->AddTexture(tex,GL_RGBA);
    go2->m_material = new Material(glm::vec3(0.9f,0.9f, 0.2f));
    go2->m_material->specular_color =  glm::vec3(0.3,0.6,0.2);
    go2->m_material->shininess = 64.0f;
    go2->object_name = "Arrow";
    
    GameObject* GUIObject = new bObject(this->basic_block ,m_camera,new float[3]{0.0f,0.0f,0.0f});
    GUIObject->object_name = "GUI gameObject";

    GameObject* CameraMov = new aObject(this->basic_block,m_camera,new float[3]{0.0f,0.0f,0.0f});
    CameraMov->object_name = "Camera Movement Game Object";

    go5 = new NoBahaviorObject(basic_block,m_camera,cubeTex,new float[3]{0.5,-0.8,0},vertTex,fragSpec);
    VAO* go5VAO = new VAO();
        go5VAO->SetAttribPoint(3);
        go5VAO->SetAttribPoint(3);
        go5VAO->SetAttribPoint(2);
        go5VAO->SetUpObject();
    go5->SetUpVertex(go5VAO);
    go5->m_material = new Material();
    go5->m_material->shininess = 64;
    go5->m_material->specular_color = glm::vec3(0.5,0.5,0.5);
    go5->AddTexture(boxTex);
    go5->AddTexture(boxSpec,new std::string("material.specular"));
    go5->object_name = "Cube with specular 2";

    all_objs->push_back(go);
    all_objs->push_back(go5);
    all_objs->push_back(go2);
    all_objs->push_back(CameraMov);
    all_objs->push_back(m_light);
    all_objs->push_back(light2);
    all_objs->push_back(m_dirLight);
    all_objs->push_back(spotLight);
    //UI needs to be last?
    all_objs->push_back(GUIObject);

    all_lights.push_back(dynamic_cast<Light*>(m_light));
    all_lights.push_back(dynamic_cast<Light*>(m_dirLight));
    all_lights.push_back(dynamic_cast<Light*>(light2));
    all_lights.push_back(dynamic_cast<Light*>(spotLight));

    vertDefault->clear();
    vertTex->clear();
    fragTex->clear();
    fragSpec->clear();
    fragDefault->clear();
    lamp->clear();
    tex->clear();
    tex2->clear();
    spec->clear();
    spec2->clear();

    delete vertDefault;
    delete vertTex;
    delete fragTex;
    delete fragSpec;
    delete fragDefault;
    delete lamp;
    delete tex;
    delete tex2;
    delete spec;
    delete spec2;

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
        while(pos < all_objs->size()-1){
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
        glClearColor(0.00f,0.00f,0.0,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       

        this->main_time->UpdateDelta();
        glfwPollEvents();
        //lock_threads.notify_all();
        //Render Objects
        for(auto it = this->all_objs->begin(); it != this->all_objs->end();it++){
            (*it)->UpdateAndBuffer();
            Light* is_light = dynamic_cast<Light*>(*it);
            if(is_light == NULL){
                for(auto lit = this->all_lights.begin(); lit != this->all_lights.end(); lit++){
                    (*lit)->LightBuffering((*it));
                }
            }else{
                is_light->LampColorBuffering();
            }
        }
        //Last object, the GUI, needs to be Updated on main thread
        //all_objs->at(all_objs->size()-1)->Update();

        glfwSwapBuffers(this->main_window->GetWindow());
        //this->main_input->ResetValues();

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


