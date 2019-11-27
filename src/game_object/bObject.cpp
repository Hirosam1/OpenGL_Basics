#include "game_object/bObject.hpp"

bObject::bObject(Window* aWindow,InputManager* m_input, Time* m_time, Camera* m_camera ,float initial_pos[3]):GameObject
(aWindow,m_input,m_time,m_camera,initial_pos){

}

void bObject::Update(){
    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_SHIFT,GLFW_PRESS)){
        this->test_speed = 10;
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

    m_camera->LookAt(*m_camera->camera_pos+ *m_camera->camera_front);

    this->test_speed = 3;
}