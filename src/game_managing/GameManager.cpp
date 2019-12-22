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

    this->basic_block = new BasicsBlock(main_window,main_input,main_time);

    glfwSetWindowUserPointer(this->main_window->GetWindow(),this->basic_block);

    std::string* vert = new std::string("shaders/vertex_shaders/MVP_vertex.vert");
    std::string* vertTex = new std::string("shaders/vertex_shaders/MVP_texture_vertex.vert");
    std::string* frag = new std::string("shaders/fragment_shaders/texture_light.frag");
    std::string* fragSpec = new std::string("shaders/fragment_shaders/textureSpecular_light.frag");
    std::string* fragLight = new std::string("shaders/fragment_shaders/light.frag");
    std::string* lamp = new std::string("shaders/fragment_shaders/lamp.frag");
    std::string* tex = new std::string("textures/Arrow.png");
    std::string* tex2 = new std::string("textures/container2.png");
    std::string* spec = new std::string("textures/container2_specular.png");

    this->all_objs = new std::deque<GameObject*>();


    Camera* m_camera = new Camera(this->main_window,new float[3]{0.0f,0.0f,10.0f});

    Shape* cube  = new Cube();
    Shape* plane = new Plane();
    Shape* triag = new Triangle();
    Shape* cubeTex = new CubeTex();

    std::cout<<"creating game objects...\n";
    GameObject *go,*go2, *go4;
    Light* aLight = new Light();
    
    go = new MovingObject(this->basic_block , m_camera,cubeTex,new float[3]{0.5,-0.8,2},vertTex,fragSpec);
    go->m_material = new Material();
    go->m_material->shininess = 64.0;
    go->m_material->specular_color  = glm::vec3(0.7,0.7,0.7);
    VAO* goVAO = new VAO(GL_FLOAT);
        goVAO->SetAttribPoint(3);
        goVAO->SetAttribPoint(3);
        goVAO->SetAttribPoint(2);
        goVAO->SetUpObject();
    go->SetUpVertex(goVAO);
    go->SetTexture(tex2,GL_RGBA);
    go->SetTexture(spec,GL_RGBA,new std::string("material.specular"));
    

    go->GiveLight(aLight);
    go2 = new aObject(this->basic_block ,m_camera,plane,new float[3]{-1,0.3,0},vertTex,frag);
    go2->GiveLight(aLight);
    VAO* go2VAO = new VAO(GL_FLOAT);
        go2VAO->SetAttribPoint(3);
        go2VAO->SetAttribPoint(3);
        go2VAO->SetAttribPoint(2);
        go2VAO->SetUpObject();
    go2->SetUpVertex(go2VAO);
    go2->SetTexture(tex,GL_RGBA);

    go2->m_material = new Material(glm::vec3(0.9f,0.9f, 0.2f));
    go2->m_material->specular_color =  glm::vec3(0.3,0.6,0.2);
    go2->m_material->shininess = 64.0f;
    GameObject* go3 = new aObject(this->basic_block ,m_camera,triag,new float[3]{-1,-2,-1},vert,fragLight);
    go3->SetUpVertex();
    go3->m_material = new Material(glm::vec3(1,0,0));
    go3->GiveLight(aLight);
    GameObject* goglob = new bObject(this->basic_block ,m_camera,new float[3]{0.0f,0.0f,0.0f});

    go4 = new cObject(this->basic_block , m_camera,cube,new float[3]{-1.5,1.2,1.2},vert,lamp);
    VAO* go4VAO = new VAO(GL_FLOAT);
    go4VAO->SetAttribPoint(3,6);
    go4VAO->SetUpObject();
    go4->SetUpVertex(go4VAO);
    go4->GiveLight(aLight);
    go4->MakeLight();


    all_objs->push_back(go);
    all_objs->push_back(go2);
    all_objs->push_back(go3);
    all_objs->push_back(goglob);
    all_objs->push_back(go4);

    vert->clear();
    frag->clear();
    tex->clear();
    fragLight->clear();
    lamp->clear();
    delete vert;
    delete frag;
    delete fragLight;
    delete lamp;
    delete tex;

    this->ready_to_start = true;
    glEnable(GL_DITHER);
    Debugging::SetPointsSize(10);    
    glEnable(GL_DEPTH_TEST);

}

void GameManager::EngnieStart(){
    if(!this->ready_to_start){
        std::cout<<"Engine is not ready to start run EngineInit\n";
        exit(-1);
    }
    std::cout<<"Ready to start!\n";
    while(!glfwWindowShouldClose(this->main_window->GetWindow())){
        
        if(this->main_input->ProcessInput(GLFW_KEY_ESCAPE,GLFW_PRESS)){
            glfwSetWindowShouldClose(this->main_window->GetWindow(),true);
        }

        //Clear the screen
        glClearColor(0.07f,0.06f,0.05,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        this->main_time->UpdateDelta();
        //Render Objects
        for(auto it = this->all_objs->begin(); it != this->all_objs->end();it++){
            (*it)->UpdateAndBuffer();
        }

        glfwSwapBuffers(this->main_window->GetWindow());
        this->main_input->ResetValues();
        glfwPollEvents();

    }
    
    std::cout<<"\n==Shutiing down glfw\n"; 
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




