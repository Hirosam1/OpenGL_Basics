#include "game_managing/GameManager.hpp"
#include "game_managing/SceneLoader.hpp"

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

    this->basic_block = new BasicsBlock(main_window,main_input);

    glfwSetWindowUserPointer(this->main_window->GetWindow(),this->basic_block);

    this->supported_concurrency = std::thread::hardware_concurrency()-1;
    this->threads = new std::thread[this->supported_concurrency];

    Debug::CleanErrorLog(); 
    SetUpObjects();

    this->ready_to_start = true;
    glEnable(GL_DITHER);
    Debug::SetPointsSize(10);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    use_threads = false;
   
    //V-sync
    glfwSwapInterval(1);

    //Update their info
    for(int i = 0; i < this->supported_concurrency; i++){
        
    this->threads[i] = std::thread(UpdateObjects,i,basic_block,supported_concurrency,main_window, 
                                       &basic_block->global_mutex,&lock_threads);
    }

}


void GameManager::SetUpObjects(){
    
    std::cout<<"creating first scene...\n";
    ResourceLoader::LoadResourceFromFile("scenes/resource.snres", basic_block);
    basic_block->global_data.active_scene = new Scene("scenes/scene_boxes.snsc",basic_block);

    //UI needs to be last?
    basic_block->GUI_gameObject = new bObject(basic_block,basic_block->global_data.active_scene->scene_data.main_camera,nullptr,new float[3]{0,0,0},nullptr);

}

void GameManager::UpdateObjects(int id, BasicsBlock* basic_block,
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
        if(basic_block->global_data.active_scene != nullptr){
            while(basic_block->global_data.active_scene->scene_data.AllObjects.size() > 0 && pos < basic_block->global_data.active_scene->scene_data.AllObjects.size()){
                pos = id + supported_concurrency * i++;
                if (pos < basic_block->global_data.active_scene->scene_data.AllObjects.size()){
                    try{
                    basic_block->global_data.active_scene->scene_data.AllObjects.at(pos)->Update();
                    }catch(std::exception &exp){
                        std::cout<<"Error Updating game object-> " <<  basic_block->global_data.active_scene->scene_data.AllObjects.at(pos)->object_name <<"\nError-> " << exp.what()<<"\n" ;
                        Debug::WriteErrorLog("Error Updating game object-> " + basic_block->global_data.active_scene->scene_data.AllObjects.at(pos)->object_name + "\nError-> " + exp.what());
                    }
                }
            }
        }
    }

}

void GameManager::EngnieStart(){
    std::unique_lock<std::mutex> lck(basic_block->global_mutex,std::defer_lock);
    if(!this->ready_to_start){
        std::cout<<"Engine is not ready to start run EngineInit\n";
        exit(-1);
    }
    std::string name;

    Model plane = Model("models/plane/Plane.obj");
    
    //Creates a frame buffer
    FrameBuffer frame_buffer = FrameBuffer(main_window->GetWidth(),main_window->GetHeight());
    plane.meshes[0].textures.push_back(frame_buffer.texture_color);
    
    std::cout<<"Ready to start!\n";
    //Execute Ready for all objects
    for(auto it = this->basic_block->global_data.active_scene->scene_data.AllObjects.begin(); it != this->basic_block->global_data.active_scene->scene_data.AllObjects.end();it++){
        (*it)->ReadyObject();
    }
    basic_block->GUI_gameObject->ReadyObject();
    while(!glfwWindowShouldClose(this->main_window->GetWindow())){
        glfwSetWindowShouldClose(this->main_window->GetWindow(),basic_block->should_close);
        //Clear the screen
        glClearColor(0.03f,0.07f,0.07,1.0f);

        Time::UpdateDelta();
        glfwPollEvents();
        //Lock here
        lck.lock();
        if(use_threads){
            // this when giving that weird lag bug VVV
            lock_threads.notify_all();
        }
        frame_buffer.UseFrameBuffer();
        glEnable(GL_DEPTH_TEST);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //Render all objects in scene
        glPolygonMode(GL_FRONT_AND_BACK, basic_block->global_data.fill_type);
        this->UpdateGlobalUniforms();
        this->RenderObjects();
        if(basic_block->global_data.active_scene->scene_data.cube_map != nullptr){
            basic_block->global_data.active_scene->scene_data.cube_map->UseCubeTexture(basic_block->global_data.active_scene->scene_data.cube_map->m_shader,
                                                                                    basic_block->global_data.active_scene->scene_data.main_camera);
        }
        this->RenderOpaques();
        //Frame buffer Begin
        
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        basic_block->global_data.frame_buffer_shader->UseShader();
        glDisable(GL_DEPTH_TEST);
        plane.Draw(basic_block->global_data.frame_buffer_shader);
        //Frame buffer End
        //Last object, the GUI, needs to be Updated on main thread
        basic_block->GUI_gameObject->Update();
        lck.unlock();
        
        glfwSwapBuffers(this->main_window->GetWindow());
         
        this->main_input->ResetValues();
        if(this->basic_block->was_resized){
            frame_buffer.ResetBuffers(this->main_window->GetWidth(),this->main_window->GetHeight());
            this->basic_block->was_resized = false;
        }

    }
    this->TerminateEngine();
    
}

void GameManager::UpdateGlobalUniforms(){
    //Update global uniform of camera
    this->basic_block->global_data.active_scene->scene_data.main_camera->UpdateCameraUniform();
    for(int i = 0; i < basic_block->global_data.active_scene->scene_data.AllLights.size();i++){
        basic_block->global_data.active_scene->scene_data.AllLights[i]->LightBuffering();
    }
    LightManager::UpdateLightNumbers(basic_block,basic_block->global_data.active_scene);
}

void GameManager::RenderObjects(){
    glEnable(GL_CULL_FACE);

     //Render non opaque Objects
    if(this->basic_block->global_data.active_scene->scene_data.AllObjects.size() > 0){
        for(auto it = this->basic_block->global_data.active_scene->scene_data.AllObjects.begin(); it != this->basic_block->global_data.active_scene->scene_data.AllObjects.end();it++){
            if((*it)->m_shader != nullptr){
                //Check if we are rendering wireframe mode
                if(basic_block->global_data.fill_type != GL_LINE){
                    (*it)->UseShader();
                }else{
                    basic_block->wireframe_shader.UseShader();
                }
                
                if(!(*it)->isOpaque){
                    (*it)->BufferAndDraw();
                }
            }
            if(!use_threads){
                try{
                //Use this when giving that weird lag bug VVV
                (*it)->Update();
                }catch(std::exception &exp){
                    std::cout<<"Error Updating game object-> " <<  (*it)->object_name <<"\nError-> " << exp.what()<<"\n" ;
                    Debug::WriteErrorLog("Error Updating game object-> "+ (*it)->object_name + "\nError-> " + exp.what());
                }
            }
            glUseProgram(0);
        }
    }

}

void GameManager::RenderOpaques(){
    glDisable(GL_CULL_FACE);
    //renders opaque objects
    std::map<float,GameObject*> sorted;
    
    for(unsigned int i = 0; i < this->basic_block->global_data.active_scene->scene_data.AllOpaques.size(); i++){
        float distance = glm::length(basic_block->global_data.active_scene->scene_data.main_camera->camera_pos - glm::vec3(this->basic_block->global_data.active_scene->scene_data.AllOpaques[i]->model_mat[3][0],
                                                                        this->basic_block->global_data.active_scene->scene_data.AllOpaques[i]->model_mat[3][1],
                                                                        this->basic_block->global_data.active_scene->scene_data.AllOpaques[i]->model_mat[3][2]));
        sorted[distance] = this->basic_block->global_data.active_scene->scene_data.AllOpaques[i];
    }       

    for(std::map<float,GameObject*>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it){
        
        if(basic_block->global_data.fill_type != GL_LINE){
            it->second->UseShader();
        }else{
            basic_block->wireframe_shader.UseShader();
        }
        it->second->BufferAndDraw();
    }
    glUseProgram(0);
    sorted.clear();
}

void GameManager::TerminateEngine(){
    delete basic_block->global_data.active_scene;
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
    std::cout<<"GLFW Error: " << error << " ->" << description<<"\n";
    Debug::WriteErrorLog("GLFW Error: " + std::to_string(error) + " ->" + description);
    exit(-1);
}

void GameManager::FrameBufferSizeCallback(GLFWwindow* windown, int width, int height){
    glViewport(0,0,width,height);
    GameManager* here = static_cast<GameManager*>(glfwGetWindowUserPointer(windown));
    here->main_window->SetWidthHeight(width,height);
    
}