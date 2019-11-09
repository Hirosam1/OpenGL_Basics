#include "game_object/Camera.hpp"

Camera::Camera(float initial_pos[3]){ 
    this->m_view = new glm::mat4(1.0);
    *this->m_view = glm::rotate(*m_view,glm::radians(35.0f),glm::vec3(1.0f,0.0f,0.0f));
    *this->m_view = glm::translate(*m_view,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
}

const glm::mat4* Camera::GetView(){
    return this->m_view;
}