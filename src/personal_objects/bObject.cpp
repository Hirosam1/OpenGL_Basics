#include "personal_objects/bObject.hpp"
#include <sys/time.h> 


bObject::bObject(BasicsBlock* bc, Camera* m_camera ,float initial_pos[3]):GameObject
(bc,m_camera,initial_pos){
    yaw = -90.0f;
    sensitivity= 0.125;
    camera_front = glm::vec3(0,0,-1);
    lastX = m_window->GetWidth()/2;
    lastY = m_window->GetHeight()/2;
    m_deque_test = new std::deque<char*>();
    fov = 45;
    didExit = false;
}

void bObject::Update(){
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
        camera_front.y = sin(glm::radians(pitch));
        camera_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera_front = glm::normalize(camera_front);

    }
    fov -= m_input->scroll_y * (sensitivity * 20);
    fov = fov > 110 ? 110 : fov < 1 ? 1 : fov;
    m_camera->MakeProjection(glm::radians(fov));
    
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
         fov = 45;
         m_camera->MakeProjection(glm::radians(fov));
    }
    #ifdef __unix__
    
    if(m_input->ProcessInput(GLFW_KEY_TAB,GLFW_PRESS)){
        std::cout<<"\r\tMemory Current Beeing Used--> "<<Debugging::GetMemoryUsage() << "  |";
    }
    //BE CAREFULL WHEN USING THIS, IT SIMULATES MEMORY LEAK
    if(m_input->ProcessInput(GLFW_KEY_9,GLFW_PRESS)){
        m_deque_test->push_back((char*) malloc (1000000) );
    }
    //THIS CLEANS THE WASTED MEMORY
    if(m_input->ProcessInput(GLFW_KEY_0,GLFW_PRESS)){
        for(int i = 0; i < m_deque_test->size(); i++){
            delete m_deque_test->at(i);
        }
        m_deque_test->clear();
    }
    #endif

    m_camera->camera_front = &camera_front;
    m_camera->LookAt(*m_camera->camera_pos+ *m_camera->camera_front);

    this->test_speed = 5;
}