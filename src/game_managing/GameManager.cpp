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


    Shape *cube1  = new Cube();
    Shape *cube2 = new Cube();

    this->go = new GameObject(this->main_window,main_input,main_time,cube1->vertex,cube2->vertex_count,cube2->indices,cube2->indices_count, new float[3]{-0.5,0.2,-10});
    this->go->SetUpObject();
    this->go2 = new GameObject(this->main_window,main_input,main_time,cube1->vertex,cube1->vertex_count,cube1->indices,cube1->indices_count, new float[3]{0.5,-0.8,-3});
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
    while(!glfwWindowShouldClose(this->main_window->GetWindow())){
        
        if(this->main_input->ProcessInput(GLFW_KEY_ESCAPE,GLFW_PRESS)){
            glfwSetWindowShouldClose(this->main_window->GetWindow(),true);
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
        glfwSwapBuffers(this->main_window->GetWindow());

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
    here->main_window->SetWidthHeight(width,height);
    
}




