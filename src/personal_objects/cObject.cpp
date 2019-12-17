#include"personal_objects/cObject.hpp"

cObject::cObject(BasicsBlock* bb, Camera* c, Shape* s, float ip[3], std::string* vs, std::string* fs,float size):GameObject(bb,c,s,ip,vs,fs){
    model  = glm::scale(model,glm::vec3(size,size,size));
}

void cObject::Update(){
    if(m_input->ProcessInput(GLFW_KEY_UP,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,0,-9*m_time->delta_time));
    }
    else if(m_input->ProcessInput(GLFW_KEY_DOWN,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,0,9*m_time->delta_time));
    }
    if(m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(-9*m_time->delta_time,0,0));
    }else if(m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(9*m_time->delta_time,0,0));
    }

}