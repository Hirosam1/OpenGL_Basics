#include"game_object/Scene.hpp"

Scene::Scene(std::string scene_path, BasicsBlock* basic_block): scene_path(scene_path){
    Camera* m_camera = new Camera(basic_block->m_window);
    m_camera->camera_pos = glm::vec3(-3.0f,2.0f,20.0f);
    m_camera->camera_front = glm::vec3(0,0,-1);
    m_camera->LookAt(m_camera->camera_pos+ m_camera->camera_front);
    scene_data.main_camera = m_camera;
    //basic_block->global_data.main_camera = m_camera;
    SceneLoader::LoadSceneFromFile(scene_path,basic_block,&scene_data);
}