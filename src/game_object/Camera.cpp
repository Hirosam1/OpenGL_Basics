#include "game_object/Camera.hpp"

Camera::Camera(float initial_pos[3]):
camera_pos(initial_pos){ 
    
    //camera_target = new float[3]{0.0f,0.0f,0.0f};

    UpdateView();
}

const glm::mat4 Camera::GetView(){
    UpdateView();
    return this->m_view;
}

void Camera::UpdateView(){
                                //position
    this->m_view = glm::lookAt(glm::make_vec3(camera_pos),
                                //target
                                glm::vec3(0,0,0),
                                //up
                                glm::vec3(0.0f,1.0f,0.0f));
}