#include "game_object/movnigObject.hpp"

MovingObject::MovingObject(BasicsBlock* bb, Camera* camera, Shape* shape, float initial_pos[3]):GameObject(bb,camera,shape,initial_pos){

}

void MovingObject::Update(){
    int direction = m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS) ? -1 : m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS) ? 1: 0;
    model = glm::translate(model,glm::vec3(direction*m_time->delta_time*test_speed,0,0));
}

