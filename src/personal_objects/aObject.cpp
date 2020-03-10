#include "personal_objects/aObject.hpp"

//That is not supposed to be a game engine class
aObject::aObject(BasicsBlock* bc, 
Camera* m_camera,float initial_pos[3]):GameObject
(bc,m_camera,initial_pos){
    m_camera->camera_pos = glm::vec3(-3.0f,0.0f,10.0f);
    yaw = -75.0f;
    pitch = -15.0f;
    sensitivity= 0.125;
    camera_front = glm::vec3(0,0,-1);
    lastX = m_window->GetWidth()/2;
    lastY = m_window->GetHeight()/2;
    fov = 45;
    didExit = false;
}

void aObject::Ready(){
    
    for(auto e = bb->all_objs->begin(); e != bb->all_objs->end(); e++){
        if((*e)->object_name == "GUI gameObject"){
            GUIObject = dynamic_cast<bObject*>(*e);
        }
    }
}

void aObject::Update(){
   
    if (m_input->ProcessInput(GLFW_KEY_TAB,GLFW_PRESS)){
        yaw = -75;
        pitch = -15;
         camera_front = glm::vec3(0,0,-1);
         m_camera->camera_pos.x = -3.0f;
         m_camera->camera_pos.y = 0.0f;
         m_camera->camera_pos.z = 10;
         fov = 45;
         m_camera->MakeProjection(glm::radians(fov));
    }

    if(GUIObject->show_cursor == GLFW_CURSOR_DISABLED) CalculateCam();

    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_SHIFT,GLFW_PRESS)){
        this->test_speed = 15;
    }
    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_CONTROL,GLFW_PRESS)){
        this->test_speed = 2;
    }
    if(this->m_input->ProcessInput(GLFW_KEY_D,GLFW_PRESS)){
        m_camera->camera_pos += glm::normalize(glm::cross(m_camera->camera_front, m_camera->camera_up)) * (float)(test_speed * m_time->delta_time); 
  
    }else if(this->m_input->ProcessInput(GLFW_KEY_A,GLFW_PRESS)){  
        m_camera->camera_pos -= glm::normalize(glm::cross(m_camera->camera_front, m_camera->camera_up)) * (float)(test_speed * m_time->delta_time); 
    }
    if(this->m_input->ProcessInput(GLFW_KEY_S,GLFW_PRESS)){
        m_camera->camera_pos -= (float)(test_speed * m_time->delta_time) * m_camera->camera_front;

    }else if(this->m_input->ProcessInput(GLFW_KEY_W,GLFW_PRESS)){
        m_camera->camera_pos += (float)(test_speed * m_time->delta_time) * m_camera->camera_front;
    }

    m_camera->camera_front = camera_front;
    m_camera->LookAt(m_camera->camera_pos+ m_camera->camera_front);

        this->test_speed = 5;

    if(m_input->ProcessInput(GLFW_KEY_F1) && GUIObject->f1KeyRealeased){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
    }
}

void aObject::CalculateCam(){
    if(firstMouse && m_input->isMouseReady){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
        firstMouse = false;
    }

    if(!m_input->is_cursor_in){
        didExit = true;
    }

    if(didExit && m_input->is_cursor_in){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
        didExit = false;
    }

    float xoffset = m_input->mouse_Xpos - lastX;
    float yoffset = lastY - m_input->mouse_Ypos;
    if(!firstMouse && !didExit && (abs(xoffset) > 0.1f ||  abs(yoffset) > 0.1f)){
        lastX = m_input->mouse_Xpos;
        lastY = m_input->mouse_Ypos;
        xoffset *= sensitivity;
        yoffset *= sensitivity;m_input;

        yaw += xoffset;
        pitch += yoffset;

        pitch = pitch > 89.4f ? 89.4f : pitch < -89.4f ? -89.4f :  pitch; 
    }
    camera_front.y = sin(glm::radians(pitch));
    camera_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(camera_front);
    fov -= m_input->scroll_y * (sensitivity * 20);
    fov = fov > 110 ? 110 : fov < 1 ? 1 : fov;
    m_camera->MakeProjection(glm::radians(fov));

}