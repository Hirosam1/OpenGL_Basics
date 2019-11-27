#include "game_object/Camera.hpp"

Camera::Camera(Window* aWindow, float initial_pos[3]):m_window(aWindow){ 
    
    this->camera_pos = new glm::vec3(glm::make_vec3(initial_pos));
    camera_front = new glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up    = new glm::vec3(0.0f, 1.0f,  0.0f);
    this->projection = glm::perspective(glm::radians(45.0f),(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.1f,100.0f);
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
                                *this->camera_up);  
} 

void Camera::LookAt(glm::vec3 target){
                                //position
    this->m_view = glm::lookAt( *this->camera_pos,
                                //target
                                target,
                                //up
                                *this->camera_up);  
} 

const glm::mat4 Camera::GetProjection(){
    //Checks if there are changes in the aspect ratio given a threshold
    if(this->width > (this->m_window->GetWidth() + 40) || this->height > (this->m_window->GetHeight() + 40) ||
        this->width < (this->m_window->GetWidth() - 40) || this->height < (this->m_window->GetHeight() - 40)){
        this->projection = glm::perspective(glm::radians(45.0f),(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.1f,100.0f);
        this->width = this->m_window->GetWidth();
        this->height = this->m_window->GetHeight();
    }
    return this->projection;
}
