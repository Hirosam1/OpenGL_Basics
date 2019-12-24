#include "personal_objects/movnigObject.hpp"

MovingObject::MovingObject(BasicsBlock* bb, Camera* camera, Shape* shape, float initial_pos[3], std::string* v, std::string* f):GameObject(bb,camera,shape,initial_pos,v,f){
    lightPos = glm::vec3(-1.5,1.2,1.2);
}

void MovingObject::Update(){
    float movSpeed = 5;
    if(m_input->ProcessInput(GLFW_KEY_KP_4,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(-movSpeed*m_time->delta_time,0,0));
    }else if(m_input->ProcessInput(GLFW_KEY_KP_6,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(movSpeed*m_time->delta_time,0,0));
    }

    if( m_input->ProcessInput(GLFW_KEY_KP_8,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,0,-movSpeed*m_time->delta_time));
    }else if(m_input->ProcessInput(GLFW_KEY_KP_2,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,0, movSpeed*m_time->delta_time));
    }

    if( m_input->ProcessInput(GLFW_KEY_KP_7,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,movSpeed*m_time->delta_time,0));
    }else if(m_input->ProcessInput(GLFW_KEY_KP_1,GLFW_PRESS)){
        model = glm::translate(model,glm::vec3(0,-movSpeed*m_time->delta_time,0)); 
    }

    if(m_input->ProcessInput(GLFW_KEY_KP_3,GLFW_PRESS)){
        model = glm::rotate(model,glm::radians((float)((movSpeed+50)*m_time->delta_time)),glm::vec3(0.5f,0.0f,0.5f));
    }else if(m_input->ProcessInput(GLFW_KEY_KP_9,GLFW_PRESS)){
        model = glm::rotate(model,glm::radians((float)(-(movSpeed+50)*m_time->delta_time)),glm::vec3(0.5f,0.0f,0.5f));
    }

}

