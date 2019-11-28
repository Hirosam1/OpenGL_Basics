#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include "graphics/Window.hpp"
#include "game_managing/BasicsBlock.hpp"

class InputManager{
    public:
        friend InputManager;
        InputManager(Window* window);
        bool ProcessInput(int key, int action) const;
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
        bool isMouseReady = false;
        double GetMouseX();
        double GetMouseY();
    private:
        double mouse_Xpos;
        double mouse_Ypos;
        Window* window;
};