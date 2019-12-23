#include "game_object/Camera.hpp"

Camera::Camera(Window* aWindow, float initial_pos[3]):m_window(aWindow){ 
    
    this->camera_pos = new glm::vec3(glm::make_vec3(initial_pos));
    camera_front = new glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up    = new glm::vec3(0.0f, 1.0f,  0.0f);
    this->projection_fov = glm::radians(45.0f);
    this->m_projection = new Projection(this->projection_fov,(float)this->m_window->GetWidth()/this->m_window->GetHeight());
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
    //delete target;
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
        this->m_projection->MakePerspective(this->projection_fov,(float)this->m_window->GetWidth()/this->m_window->GetHeight());
        this->width = this->m_window->GetWidth();
        this->height = this->m_window->GetHeight();
    }
    return this->m_projection->GetProjection();
}

void Camera::MakeProjection(float fov, float aspect_ratio,float close, float far){
    if(aspect_ratio == -1){
        aspect_ratio = (float)this->m_window->GetWidth()/this->m_window->GetHeight();
    }
    this->projection_fov = fov;
    this->m_projection->MakePerspective(fov,aspect_ratio,close,far);
}