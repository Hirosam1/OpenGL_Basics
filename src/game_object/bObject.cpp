#include "game_object/bObject.hpp"

bObject::bObject(Window* aWindow,InputManager* m_input, Time* m_time, Camera* m_camera ,float initial_pos[3]):GameObject
(aWindow,m_input,m_time,m_camera,initial_pos){
    yaw = -90.0f;
    sensitivity= 0.2;
    camera_front = glm::vec3(0,0,-1);
    lastX = m_window->GetWidth()/2;
    lastY = m_window->GetHeight()/2;
}

void bObject::Update(){
    if(firstMouse && m_input->isMouseReady){
        lastX = m_input->GetMouseX();
        lastY = m_input->GetMouseY();
        firstMouse = false;
    }
    float xoffset = m_input->GetMouseX() - lastX;
    float yoffset = lastY - m_input->GetMouseY();
    lastX = m_input->GetMouseX();
    lastY = m_input->GetMouseY();
    if(!firstMouse && (abs(xoffset) > 0.01 ||  abs(yoffset) > 0.01)){
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        pitch = pitch > 89.0f ? 89.0f : pitch < -89.0f ? -89.0f :  pitch; 
        camera_front.y = sin(glm::radians(pitch));
        camera_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front = glm::normalize(camera_front);
    }
    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_SHIFT,GLFW_PRESS)){
        this->test_speed = 15;
    }
    if(this->m_input->ProcessInput(GLFW_KEY_D,GLFW_PRESS)){
        *m_camera->camera_pos += glm::normalize(glm::cross(*m_camera->camera_front, *m_camera->camera_up)) * (float)(test_speed * m_time->delta_time); 
  
    }else if(this->m_input->ProcessInput(GLFW_KEY_A,GLFW_PRESS)){  
        *m_camera->camera_pos -= glm::normalize(glm::cross(*m_camera->camera_front, *m_camera->camera_up)) * (float)(test_speed * m_time->delta_time); 
    }
    if(this->m_input->ProcessInput(GLFW_KEY_S,GLFW_PRESS)){
        *m_camera->camera_pos -= (float)(test_speed * m_time->delta_time) * *m_camera->camera_front;

    }else if(this->m_input->ProcessInput(GLFW_KEY_W,GLFW_PRESS)){
        *m_camera->camera_pos += (float)(test_speed * m_time->delta_time) * *m_camera->camera_front;
    }

    else if(this->m_input->ProcessInput(GLFW_KEY_1,GLFW_PRESS)){
        Debugging::SetPoly2Fill();
    }else if(this->m_input->ProcessInput(GLFW_KEY_2,GLFW_PRESS)){
        Debugging::SetPoly2Line();
    }
    else if(this->m_input->ProcessInput(GLFW_KEY_3,GLFW_PRESS)){
        Debugging::SetPoly2Points();
    }

    if (m_input->ProcessInput(GLFW_KEY_LEFT_CONTROL,GLFW_PRESS)){
        yaw = -90;
        pitch = 0;
         camera_front = glm::vec3(0,0,-1);
         m_camera->camera_pos->x = 0;
         m_camera->camera_pos->y = 0;
         m_camera->camera_pos->z = 10;
    }

    m_camera->camera_front = &camera_front;
    m_camera->LookAt(*m_camera->camera_pos+ *m_camera->camera_front);

    this->test_speed = 5;
}