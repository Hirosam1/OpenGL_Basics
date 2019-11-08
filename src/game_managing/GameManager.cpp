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

    this->main_window = new Window(this->width,this->height,this->game_name);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout<<"Error while initilazing GLAD\n";
    exit(-1);
    }
    
    this->main_window->GetWindow();
    //setting up callbacks
    std::cout<<"setting up callbacks...\n";
    glfwSetWindowUserPointer(this->main_window->GetWindow(),this);
    glfwSetErrorCallback(this->ErrorCallback);
    glfwSetFramebufferSizeCallback(this->main_window->GetWindow(),this->FrameBufferSizeCallback);
    this->main_input = new InputManager(this->main_window->GetWindow());
    this->main_time = new Time();

    std::string* vert = new std::string("shaders/vertex_shaders/MVP_vertex.vert");
    std::string* frag = new std::string("shaders/fragment_shaders/texture_fragment.frag");
    std::string* tex = new std::string("Arrow.png");

    this->all_objs = new std::deque<GameObject*>();

    Shape* cube  = new Cube();
    Shape* plane = new Plane();
    Shape* triag = new Triangle();
    std::cout<<"creating game objects...\n";
    this->go = new aObject(this->main_window,this->main_input,this->main_time,cube,new float[3]{0.5,-0.8,2});
    this->go->SetUpObject();
    this->go2 = new aObject(this->main_window,this->main_input,this->main_time,plane,new float[3]{-0.7,+0.3,0},vert,frag);
    this->go2->SetUpObject();
    this->go2->SetTexture(tex);
    GameObject* go3 = new aObject(this->main_window,this->main_input,this->main_time,triag,new float[3]{0.1,0.2,-1});
    go3->SetUpObject();

    all_objs->push_back(go);
    all_objs->push_back(go2);
    all_objs->push_back(go3);

    delete vert;
    delete frag;
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
        glClearColor(0.58f,0.32f,0.69f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->main_time->UpdateDelta();
        //Render Objects
        for(auto it = this->all_objs->begin(); it != this->all_objs->end();it++){
            (*it)->UpdateAndBuffer();
        }

        glfwSwapBuffers(this->main_window->GetWindow());

        glfwPollEvents();
    }


    std::cout<<"Shutiing down glfw...\n"; 
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




