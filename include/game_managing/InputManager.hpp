#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include "graphics/Window.hpp"
#include "game_managing/BasicsBlock.hpp"

class InputManager{
    public:
        InputManager(Window* window);
        bool ProcessInput(int key, int action) const;
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        void ResetValues();
        bool isMouseReady = false;
        double mouse_Xpos;
        double mouse_Ypos;

        double GetScrollY();
        double scroll_x;
        double scroll_y;
        bool is_scroll_on;
    private:
        Window* window;
};