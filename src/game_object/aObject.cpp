#include "game_object/aObject.hpp"

//That is not supposed to be a game engine class
aObject::aObject(Window* aWindow,InputManager* m_input, Time* m_time, 
Shape* m_shape,Camera* m_camera ,float initial_pos[3], std::string* vert_shader_path,std::string* frag_shader_path):GameObject
(aWindow,m_input,m_time,m_shape,m_camera,initial_pos,vert_shader_path,frag_shader_path){

}
void aObject::Update(){
    
    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_SHIFT,GLFW_PRESS)){
        this->test_speed = 10;
    }

    if(this->m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS)){
        this->m_camera->camera_pos[0] += test_speed*m_time->delta_time;      
    }else if(this->m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS)){  
        this->m_camera->camera_pos[0] -= test_speed*m_time->delta_time; 
    }
    if(this->m_input->ProcessInput(GLFW_KEY_DOWN,GLFW_PRESS)){
        this->m_camera->camera_pos[1] -= test_speed*m_time->delta_time;        

    }else if(this->m_input->ProcessInput(GLFW_KEY_UP,GLFW_PRESS)){
       this->m_camera->camera_pos[1] += test_speed*m_time->delta_time;     
    }

    else if(this->m_input->ProcessInput(GLFW_KEY_1,GLFW_PRESS)){
        Debugging::SetPoly2Fill();
    }else if(this->m_input->ProcessInput(GLFW_KEY_2,GLFW_PRESS)){
        Debugging::SetPoly2Line();
    }
    else if(this->m_input->ProcessInput(GLFW_KEY_3,GLFW_PRESS)){
        Debugging::SetPoly2Points();
    }

    this->test_speed = 3;
}
