#include "game_object/Camera.hpp"

Camera::Camera(float initial_pos[3]){ 
    
    this->camera_pos = new glm::vec3(glm::make_vec3(initial_pos));
    UpdateView();
}

const glm::mat4 Camera::GetView(){
    return this->m_view;
}

void Camera::UpdateView(){

}

void Camera::LookAt(float target[3]){
                                //position
    this->m_view = glm::lookAt( *this->camera_pos,
                                //target
                                glm::make_vec3(target),
                                //up
                                glm::vec3(0.0f,1.0f,0.0f));  
} 