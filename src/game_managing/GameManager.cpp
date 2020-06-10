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
    this->main_time = new Time();

    this->basic_block = new BasicsBlock(main_window,main_input,main_time);

    glfwSetWindowUserPointer(this->main_window->GetWindow(),this->basic_block);

    this->supported_concurrency = std::thread::hardware_concurrency()-1;
    this->threads = new std::thread[this->supported_concurrency];


    SetUpObjects();

    this->ready_to_start = true;
    glEnable(GL_DITHER);
    Debugging::SetPointsSize(10);    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    use_threads = true;
   
    //V-sync
    glfwSwapInterval(1);


    //Update their info
    for(int i = 0; i < this->supported_concurrency; i++){
        
    this->threads[i] = std::thread(UpdateObjects,i,basic_block,supported_concurrency,main_window, 
                                       &basic_block->global_mutex,&lock_threads);
    }

}


void GameManager::SetUpObjects(){
    
    std::cout<<"creating game objects...\n";
    //Model* box = new Model("models/box/Box.obj");
    //cubemap_tex = new CubeMapTexture("textures/skybox1");
    ResourceLoader::LoadResourceFromFile("scenes/resource.snres", basic_block);
    basic_block->global_data.active_scene = new Scene("scenes/scene_boxes.snsc",basic_block);
    //current_scene_data = basic_block->global_data.active_scene->scene_data;

    //UI needs to be last?
    basic_block->GUI_gameObject = new bObject(basic_block,basic_block->global_data.active_scene->scene_data.main_camera,nullptr,new float[3]{0,0,0},nullptr);
    //all_objs->push_back(GUIObject);

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
                    basic_block->global_data.active_scene->scene_data.AllObjects.at(pos)->Update();
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
    Shader* shader = new Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/BasicLight.frag");
    std::string name;
    //Shader for the post processing effects
    Shader screen_shader = Shader("shaders/vertex_shaders/Basic_FrameBuffer.vert","shaders/fragment_shaders/Basic_FrameBuffer.frag");
    //Shader for the skybox
    //Shader skybox_shader = Shader("shaders/vertex_shaders/SkyBox.vert","shaders/fragment_shaders/SkyBox.frag");
    //Creates the quad to render scene
    Model plane = Model("models/plane/Plane.obj");
    //Model TexCube = Model("models/box/TexCube.obj");

    //CubeMap cube_map = CubeMap("textures/skybox2",&TexCube,&skybox_shader);
    //CubeMap cube_map = CubeMap(cubemap_tex,&TexCube,&skybox_shader);
    
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
        if(this->main_input->ProcessInput(GLFW_KEY_ESCAPE,GLFW_PRESS)){
            glfwSetWindowShouldClose(this->main_window->GetWindow(),true);
        }
        //Clear the screen
        glClearColor(0.03f,0.07f,0.07,1.0f);

        this->main_time->UpdateDelta();
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
        this->RenderObjects();
        //cube_map.UseCubeTexture(cube_map.m_shader,m_camera);
        this->RenderOpaques();
        
        //============================

        glBindFramebuffer(GL_FRAMEBUFFER,0);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        screen_shader.UseShader();
        glDisable(GL_DEPTH_TEST);
        plane.Draw(&screen_shader);
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

void GameManager::RenderObjects(){
    glEnable(GL_CULL_FACE);
     //Render non opaque Objects
    if(this->basic_block->global_data.active_scene->scene_data.AllObjects.size() > 0){
        for(auto it = this->basic_block->global_data.active_scene->scene_data.AllObjects.begin(); it != this->basic_block->global_data.active_scene->scene_data.AllObjects.end();it++){
            if(!use_threads){
                //Use this when giving that weird lag bug VVV
                (*it)->Update();
            }
            if((*it)->m_shader != nullptr){
                (*it)->UseShader();
                Light* is_light = dynamic_cast<Light*>(*it);
                if(is_light == NULL){
                    for(auto lit = this->basic_block->global_data.active_scene->scene_data.AllLights.begin(); lit != this->basic_block->global_data.active_scene->scene_data.AllLights.end(); lit++){
                        (*lit)->LightBuffering((*it));
                    }
                }else{
                    is_light->LampColorBuffering();
                }
                if(!(*it)->isOpaque){
                    (*it)->BufferAndDraw();
                }
                glUseProgram(0);
            }
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
        it->second->UseShader();
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
    std::cout<<"Error: " << error << " ->" << description<<"\n";
    exit(-1);
}

void GameManager::FrameBufferSizeCallback(GLFWwindow* windown, int width, int height){
    glViewport(0,0,width,height);
    GameManager* here = static_cast<GameManager*>(glfwGetWindowUserPointer(windown));
    here->main_window->SetWidthHeight(width,height);
    
}


