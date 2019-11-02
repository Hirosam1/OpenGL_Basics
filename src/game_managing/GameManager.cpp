#include "game_managing/GameManager.h"

GameManager::GameManager(std::string game_name,int width, int height){
    this->game_name = game_name;
    this->width = width;
    this->height = height;
    this->current_width = width;
    this->current_height = height;
    this->ready_to_start = false;
    //this->go = new GameObject();
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
    this->main_input = new InputManager();
    


    this->go = new GameObject();
    this->go->SetUpObject();

    this->ready_to_start = true;

}

void GameManager::EngnieStart(){
    if(!this->ready_to_start){
        std::cout<<"Engine is not ready to start run EngineInit\n";
        exit(-1);
    }
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(4);
    std::cout<<"Ready to start!\n";
    while(!glfwWindowShouldClose(this->main_windown)){
        //Proccess the inputs
        this->main_input->ProcessInput(this->main_windown);

        //Clear the screen
        glClearColor(0.58f,0.32f,0.69f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Render Objects
        this->go->Update();

        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glBindVertexArray(0);


        //Swap the buffers
        glfwSwapBuffers(this->main_windown);

        glfwPollEvents();
        glBindVertexArray(0);


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
        return NULL;
    }

    return window;
    
}



