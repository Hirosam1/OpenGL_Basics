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
        bool ProcessInput(int key, int action = GLFW_PRESS) const;
        //bool ProcessMouseInput(int key) const;
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
        static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        static void CursorEnterCallback(GLFWwindow* window, int enter);
        static void KeyboardCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
        void ResetValues();
        bool isMouseReady = false;
        double mouse_Xpos;
        double mouse_Ypos;

        double GetScrollY();
        double scroll_x;
        double scroll_y;
        bool is_cursor_in;
    private:
        Window* window;
};