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
    Light* aLight = new Light();
    aLight->light_ambient = aLight->light_color* 0.1f;

    Texture* boxTex = new Texture(tex2,GL_RGBA);
    Texture* boxSpec = new Texture(spec, GL_RGBA);
    
    aLight->light_color = glm::vec3(1.0,1.0,1.0);
    aLight->light_intensity = 1;
    go = new NoBahaviorObject(this->basic_block , m_camera,cubeTex,new float[3]{0.5,-0.8,2},vertTex,fragSpec);
    go->m_material = new Material();
    go->m_material->shininess = 64.0;
    go->m_material->specular_color  = glm::vec3(0.7,0.7,0.7);
    VAO* goVAO = new VAO(GL_FLOAT);
        goVAO->SetAttribPoint(3);
        goVAO->SetAttribPoint(3);
        goVAO->SetAttribPoint(2);
        goVAO->SetUpObject();
    go->SetUpVertex(goVAO);
    go->AddTexture(boxTex);
    go->AddTexture(boxSpec,new std::string("material.specular"));
    go->GiveLight(aLight);
    go->object_name = "Cube With Specular";

    go2 = new NoBahaviorObject(this->basic_block ,m_camera,plane,new float[3]{-1,0.3,0},vertTex,fragTex);
    go2->GiveLight(aLight);
    VAO* go2VAO = new VAO(GL_FLOAT);
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

    go4 = new cObject(this->basic_block , m_camera,cube,new float[3]{-1.5,1.2,1.2},vertDefault,lamp);
    VAO* go4VAO = new VAO(GL_FLOAT);
    go4VAO->SetAttribPoint(3,6);
    go4VAO->SetUpObject();
    go4->SetUpVertex(go4VAO);
    go4->GiveLight(aLight);
    go4->MakeLight();
    go4->object_name = "Light1";

    go5 = new NoBahaviorObject(basic_block,m_camera,cubeTex,new float[3]{0.5,-0.8,0},vertTex,fragTex);
    VAO* go5VAO = new VAO(GL_FLOAT);
        go5VAO->SetAttribPoint(3);
        go5VAO->SetAttribPoint(3);
        go5VAO->SetAttribPoint(2);
        go5VAO->SetUpObject();
    go5->GiveLight(aLight);
    go5->SetUpVertex(go5VAO);
    go5->m_material = new Material();
    go5->m_material->shininess = 128;
    go5->m_material->specular_color = glm::vec3(0.5,0.5,0.5);
    go5->AddTexture(boxTex);
    go5->AddTexture(boxSpec,new std::string("material.specular"));
    go5->object_name = "Cube without specular";

    all_objs->push_back(go);
    all_objs->push_back(go2);
    all_objs->push_back(go4);
    all_objs->push_back(go5);
    all_objs->push_back(CameraMov);
    //UI needs to be last?
    all_objs->push_back(GUIObject);

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
        std::mutex *mtx, std::condition_variable *cv){
    //Create its lock based on shared mutex, don't need to lock at this point that is why defer_lock
    std::unique_lock<std::mutex> lck(*mtx, std::defer_lock);

    while(!glfwWindowShouldClose(window->GetWindow())){
        int i = 0;
        int pos = 0;
        lck.lock();
        cv->wait(lck);
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
        lock_threads.notify_all();
        
        //Render Objects
        for(auto it = this->all_objs->begin(); it != this->all_objs->end();it++){
            (*it)->UpdateAndBuffer();
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


