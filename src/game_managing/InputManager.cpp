#include "game_managing/InputManager.hpp"

InputManager::InputManager(GLFWwindow* window):window(window){

}

bool InputManager::ProcessInput(int key, int action) const{
    if(glfwGetKey(this->window,key) == action){
        return true;
    }

    return false;
}