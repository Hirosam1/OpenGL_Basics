#include"game_object/Scene.hpp"

Scene::Scene(std::string scene_path, BasicsBlock* basic_block): scene_path(scene_path){
    Camera* m_camera = new Camera(basic_block->m_window);
    isReady = true;
    m_camera->camera_pos = glm::vec3(-3.0f,2.0f,20.0f);
    m_camera->camera_front = glm::vec3(0,0,-1);
    m_camera->LookAt(m_camera->camera_pos+ m_camera->camera_front);
    scene_data.main_camera = m_camera;
    
    if(!SceneLoader::LoadSceneFromFile(scene_path,basic_block,&scene_data)){
        isReady = false;
        std::cout<<"FILE::SCENE::LOADER:ERROR->" <<"Could not open file \""<<scene_path<<"\" \n";
        return;
    }
    m_camera->ReadyCameraUniform();
    std::cout<<"Loading scene-> "<< scene_path.substr(scene_path.find_last_of("/"), scene_path.length()) <<"\n";
    
}


Scene::~Scene(){
    std::cout<<"deleting scene -> "<< scene_data.scene_name <<"\n";
    /*Delete loaded models, loaded shaders and cameras*/
    for(unsigned int i =0; i < this->scene_data.AllObjects.size(); i++){
        delete this->scene_data.AllObjects.at(i);
    }
    
    for(auto it = this->scene_data.loaded_models.begin(); it != this->scene_data.loaded_models.end(); it++){
        delete it->second;
    }
    for(auto it = this->scene_data.loaded_textures.begin(); it != this->scene_data.loaded_textures.end(); it++){
        if(it->second != nullptr){
            it->second->UnloadTexture();
            delete it->second;
            it->second = nullptr;
        }
    }
    this->scene_data.AllObjects.clear();
    this->scene_data.AllLights.clear(); 
    this->scene_data.AllOpaques.clear();
    delete this->scene_data.cube_map;
    //Delete the camera list when I have one
    //for(unsigned int i =0; i <)
    this->scene_data.loaded_textures.clear();
    this->scene_data.loaded_models.clear();
    delete this->scene_data.main_camera;
}

bool Scene::ChangeScene(std::string scene_path, BasicsBlock* basic_block){
    //Load the scene out os sync with the main thread
    Scene* new_scene = new Scene(scene_path,  basic_block);
    if(!new_scene->isReady){
        delete new_scene;
        return false;
    }
    std::unique_lock<std::mutex>lck (basic_block->scene_mutex);
    //Delete and reset scene in sync with the main thread
    delete basic_block->global_data.active_scene;
    //Resets the new scene as the actice scene
    basic_block->global_data.active_scene = new_scene;
    //Run all the readyObjects
    for(unsigned int i = 0; i < new_scene->scene_data.AllObjects.size(); i++){
        new_scene->scene_data.AllObjects[i]->ReadyObject();
    }
    basic_block->GUI_gameObject->ReadyObject();
    lck.unlock();
    return true;
}