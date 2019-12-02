#include "game_managing/InputManager.hpp"


InputManager::InputManager(Window* window):window(window){
    glfwSetInputMode(window->GetWindow(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->GetWindow(),MouseCallback);
    glfwSetScrollCallback(window->GetWindow(),ScrollCallback);
    scroll_y = 0;
    scroll_x = 0;
    is_scroll_on = false;
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

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    BasicsBlock* here = static_cast<BasicsBlock*>(glfwGetWindowUserPointer(window));
    here->m_input->scroll_x = xoffset;
    here->m_input->scroll_y = yoffset;
}

void InputManager::ResetValues(){
    this->scroll_x = 0;
    this->scroll_y = 0;
}