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
    std::string* frag = new std::string("shaders/fragment_shaders/texture_fragment.frag");
    std::string* fragLight = new std::string("shaders/fragment_shaders/light.frag");
    std::string* lamp = new std::string("shaders/fragment_shaders/lamp.frag");
    std::string* tex = new std::string("Arrow.png");

    this->all_objs = new std::deque<GameObject*>();


    Camera* m_camera = new Camera(this->main_window,new float[3]{0.0f,0.0f,10.0f});

    Shape* cube  = new Cube();
    Shape* plane = new Plane();
    Shape* triag = new Triangle();

    std::cout<<"creating game objects...\n";
    GameObject *go,*go2, *go4;
    go = new MovingObject(this->basic_block , m_camera,cube,new float[3]{0.5,-0.8,2},vert,fragLight);
    go->SetUpVertex();
    go2 = new aObject(this->basic_block ,m_camera,plane,new float[3]{-1,0.3,0},vert,frag);
    VAO* go2VAO = new VAO(GL_FLOAT);
        go2VAO->SetAttribPoint(3);
        go2VAO->SetAttribPoint(3);
        go2VAO->SetAttribPoint(2);
    go2VAO->SetUpObject();
    go2->SetUpVertex(go2VAO);
    go2->SetTexture(tex);
    GameObject* go3 = new aObject(this->basic_block ,m_camera,triag,new float[3]{0.1,0.2,-1});
    go3->SetUpVertex();
    GameObject* goglob = new bObject(this->basic_block ,m_camera,new float[3]{0.0f,0.0f,0.0f});

    go4 = new aObject(this->basic_block , m_camera,cube,new float[3]{-1.5,1.2,1.2},vert,lamp);
    go4->SetUpVertex();


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
        glClearColor(0.05f,0.05f,0.1f,1.0f);
        //glClearColor(0.58f,0.32f,0.69f,1.0f);
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




