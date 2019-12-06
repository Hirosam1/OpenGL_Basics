#include "game_object/aObject.hpp"

//That is not supposed to be a game engine class
aObject::aObject(BasicsBlock* bc, 
Camera* m_camera,Shape* m_shape,float initial_pos[3], std::string* vert_shader_path,std::string* frag_shader_path):GameObject
(bc,m_camera,m_shape,initial_pos,vert_shader_path,frag_shader_path){
}
void aObject::Update(){
    
    if(isLight){
        if(m_input->ProcessInput(GLFW_KEY_UP,GLFW_PRESS)){
            model = glm::translate(model,glm::vec3(0,0,-3*m_time->delta_time));
        }
        else if(m_input->ProcessInput(GLFW_KEY_DOWN,GLFW_PRESS)){
            model = glm::translate(model,glm::vec3(0,0,3*m_time->delta_time));
        }
        if(m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS)){
            model = glm::translate(model,glm::vec3(-3*m_time->delta_time,0,0));
        }else if(m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS)){
            model = glm::translate(model,glm::vec3(3*m_time->delta_time,0,0));
        }
    }

}
