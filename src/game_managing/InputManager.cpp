#include "game_managing/InputManager.hpp"


InputManager::InputManager(Window* window):window(window){
    glfwSetInputMode(window->GetWindow(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->GetWindow(),MouseCallback);
    glfwSetScrollCallback(window->GetWindow(),ScrollCallback);
    glfwSetCursorEnterCallback(window->GetWindow(),CursorEnterCallback);
    scroll_y = 0;
    scroll_x = 0;
}

bool InputManager::ProcessInput(int key, int action) const{
    if(glfwGetKey(this->window->GetWindow(),key) == action){
        return true;
    }
    return false;
}
/*
bool InputManager::ProcessMouseInput(int key) const{
    if(glfwGetMouseButton(this->window->GetWindow(),key)){
        return true;
    }
    return false;
}*/


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

void InputManager::CursorEnterCallback(GLFWwindow* window, int enter){
    BasicsBlock* here = static_cast<BasicsBlock*>(glfwGetWindowUserPointer(window));
    if(enter == GL_TRUE){
        here->m_input->is_cursor_in =true;
    }else{
        here->m_input->is_cursor_in =false;
    }
}

void InputManager::ResetValues(){
    this->scroll_x = 0;
    this->scroll_y = 0;
}