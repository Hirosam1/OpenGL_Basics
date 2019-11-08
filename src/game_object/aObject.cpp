#include "game_object/aObject.hpp"

aObject::aObject(Window* aWindow,InputManager* m_input, Time* m_time, 
Shape* m_shape, float initial_pos[3]):GameObject
(aWindow,m_input,m_time,m_shape,initial_pos){

}

aObject::aObject(Window* aWindow,InputManager* m_input, Time* m_time, 
Shape* m_shape, float initial_pos[3], std::string* vert_shader_path,std::string* frag_shader_path):GameObject
(aWindow,m_input,m_time,m_shape,initial_pos,vert_shader_path,frag_shader_path){

}
void aObject::Update(){
    
    if(this->m_input->ProcessInput(GLFW_KEY_LEFT_SHIFT,GLFW_PRESS)){
        this->test_speed = 10;
    }

    if(this->m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS)){
        model = glm::rotate(model,(float)test_speed * (float)m_time->delta_time, glm::vec3(0,1,0));
    }else if(this->m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS)){
        
        model = glm::rotate(model,-(float)test_speed * (float)m_time->delta_time,glm::vec3(0,1,0));
    }
    if(this->m_input->ProcessInput(GLFW_KEY_DOWN,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,-3*m_time->delta_time,0));
    }else if(this->m_input->ProcessInput(GLFW_KEY_UP,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,3*m_time->delta_time,0));
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