#include "game_object/movnigObject.hpp"

MovingObject::MovingObject(BasicsBlock* bb, Camera* camera, Shape* shape, float initial_pos[3], std::string* v, std::string* f):GameObject(bb,camera,shape,initial_pos,v,f){
    lightCol_string = new std::string("lightColor");
    lightPos = glm::vec3(-1.5,1.2,1.2);
}

void MovingObject::Update(){
    int direction = m_input->ProcessInput(GLFW_KEY_KP_4,GLFW_PRESS) ? -1 : m_input->ProcessInput(GLFW_KEY_KP_6,GLFW_PRESS) ? 1: 0;
    model = glm::translate(model,glm::vec3(direction*m_time->delta_time*test_speed,0,0));

    int depth =  m_input->ProcessInput(GLFW_KEY_KP_8,GLFW_PRESS) ? 1 : m_input->ProcessInput(GLFW_KEY_KP_2,GLFW_PRESS) ? -1: 0;
    model = glm::translate(model,glm::vec3(0,0,-depth*m_time->delta_time*test_speed));

    int height = m_input->ProcessInput(GLFW_KEY_KP_7,GLFW_PRESS) ? 1 : m_input->ProcessInput(GLFW_KEY_KP_1,GLFW_PRESS) ? -1: 0;
    model = glm::translate(model,glm::vec3(0,height*m_time->delta_time*test_speed,0));

    if(m_input->ProcessInput(GLFW_KEY_J,GLFW_PRESS)){
        light -= 1 * m_time->delta_time;
    }else if(m_input->ProcessInput(GLFW_KEY_U,GLFW_PRESS)){
        light += 1 * m_time->delta_time;
    }
    if(light < 0){
        light = 0;
    }else if(light > 1){
        light = 1;
    }

    //std::string aux = std::string("lightPos");
    //shader->SetUniformVec3f(lightCol_string,light * glm::vec3(1,1,1));
    //shader->SetUniformVec3f(&aux,lightPos);
}

