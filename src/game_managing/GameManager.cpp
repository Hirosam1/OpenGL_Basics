#include "game_managing/GameManager.h"

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

    //Creating window
    std::cout<<"creating window...\n";
    this->main_windown = this->CreateContextWindow(this->width,this->height,this->game_name);
    glfwMakeContextCurrent(this->main_windown);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout<<"Error while initilazing GLAD\n";
    exit(-1);
    }

    //setting up callbacks
    std::cout<<"setting up callbacks...\n";
    glfwSetWindowUserPointer(main_windown,this);
    glfwSetErrorCallback(this->ErrorCallback);
    glfwSetFramebufferSizeCallback(this->main_windown,this->FrameBufferSizeCallback);
    this->main_input = new InputManager(this->main_windown);
    this->main_time = new Time();


    Shape *cube  = new Cube();


    this->go = new GameObject(this->main_input,this->main_time);
    this->go->SetUpObject();
    this->go2 = new GameObject(main_input,main_time,cube->vertex,cube->vertex_count,cube->indices,cube->indices_count, new float[3]{0.5,-0.8,-3});
    this->go2->SetUpObject();

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
    while(!glfwWindowShouldClose(this->main_windown)){
        
        if(this->main_input->ProcessInput(GLFW_KEY_ESCAPE,GLFW_PRESS)){
            glfwSetWindowShouldClose(this->main_windown,true);
        }

        //Clear the screen
        glClearColor(0.58f,0.32f,0.69f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->main_time->UpdateDelta();
        //Render Objects
        this->go->UpdateAndBuffer();
        this->go2->UpdateAndBuffer();

        glBindVertexArray(0);


        //Swap the buffers
        glfwSwapBuffers(this->main_windown);

        glfwPollEvents();
        //glBindVertexArray(0);


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
    here->current_width = width;
    here->current_height = height;
}

GLFWwindow* GameManager::CreateContextWindow(int width, int height,std::string window_name){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);

    GLFWwindow* window = glfwCreateWindow(width,height,this->game_name.c_str(),NULL,NULL);
        if(!window){
        std::cout<<"Error at creating windown!\n";
        glfwTerminate();
        exit(-1);
    }

    return window;
    
}



