#include "game_managing/InputManager.hpp"


InputManager::InputManager(Window* window):window(window){
    glfwSetInputMode(window->GetWindow(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->GetWindow(),MouseCallback);
}

bool InputManager::ProcessInput(int key, int action) const{
    if(glfwGetKey(this->window->GetWindow(),key) == action){
        return true;
    }

    return false;
}

void InputManager::MouseCallback(GLFWwindow* window, double xpos, double ypos){
    BasicsBlock* here = static_cast<BasicsBlock*>(glfwGetWindowUserPointer(window));
    if(!here->m_input->isMouseReady){
        here->m_input->isMouseReady = true;
    }
    here->m_input->mouse_Xpos = xpos;
    here->m_input->mouse_Ypos = ypos;
}

double InputManager::GetMouseX(){
    return this->mouse_Xpos;
}

double InputManager::GetMouseY(){
    return this->mouse_Ypos;
}