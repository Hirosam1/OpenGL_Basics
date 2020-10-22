#include "game_object/Camera.hpp"

Camera::Camera(Window* aWindow, float initial_pos[3]):m_window(aWindow){ 
    
    this->camera_pos = glm::vec3(glm::make_vec3(initial_pos));
    camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);
    this->projection_fov = glm::radians(45.0f);
    this->m_projection = new Projection(this->projection_fov,(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.01,1000);
    glGenBuffers(1,&uniform_buffer);
}

const glm::mat4 Camera::GetView(){
    return this->m_view;
}

Camera::~Camera(){
    glDeleteBuffers(1,&this->uniform_buffer);
}

void Camera::ReadyCameraUniform(){
    glBindBuffer(GL_UNIFORM_BUFFER,uniform_buffer);
    glBufferData(GL_UNIFORM_BUFFER,2* sizeof(glm::mat4),NULL,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0); 
    glBindBufferBase(GL_UNIFORM_BUFFER,0,uniform_buffer);
}

void Camera::UpdateCameraUniform(){
    glBindBuffer(GL_UNIFORM_BUFFER,uniform_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER,0,sizeof(glm::mat4),glm::value_ptr(this->m_projection->GetProjection()));
    glBufferSubData(GL_UNIFORM_BUFFER,sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(this->m_view));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}

void Camera::LookAt(float target[3]){
                                //position
    this->m_view = glm::lookAt( this->camera_pos,
                                //target
                                glm::make_vec3(target),
                                //up
                                this->camera_up);  
    delete target;
} 

void Camera::LookAt(glm::vec3 target){
                                //position
    this->m_view = glm::lookAt( this->camera_pos,
                                //target
                                target,
                                //up
                                this->camera_up);  
} 

const glm::mat4 Camera::GetProjection(){
    //Checks if there are changes in the aspect ratio given a threshold
    if(this->m_window->GetHeight() > 1 && this->m_window->GetWidth() > 1 &&(abs(this->width - this->m_window->GetWidth()) > 40 || 
    abs(this->height - this->m_window->GetHeight() > 40))){
        this->m_projection->MakePerspective(this->projection_fov,(float)this->m_window->GetWidth()/this->m_window->GetHeight(),m_projection->close_plane,m_projection->far_plane);
        this->width = this->m_window->GetWidth();
        this->height = this->m_window->GetHeight();
    }
    return this->m_projection->GetProjection();
}

void Camera::MakeProjection(float fov, float aspect_ratio){
    float close, far;
    if(aspect_ratio == -1 && this->m_window->GetHeight() > 1 && this->m_window->GetWidth() > 1){
        aspect_ratio = (float)this->m_window->GetWidth()/this->m_window->GetHeight();
    }
    close = m_projection->close_plane;
    far = m_projection->far_plane;    

    this->projection_fov = fov;
    this->m_projection->MakePerspective(fov,aspect_ratio,close,far);
}

void Camera::MakeProjection(float fov, float aspect_ratio,float close, float far){
    if(aspect_ratio == -1 && this->m_window->GetHeight() > 1 && this->m_window->GetWidth() > 1){
        aspect_ratio = (float)this->m_window->GetWidth()/this->m_window->GetHeight();
    }
    this->projection_fov = fov;
    this->m_projection->MakePerspective(fov,aspect_ratio,close,far);
}