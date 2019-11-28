#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

#include "game_managing/BasicsBlock.hpp"

class Window{
    public:
        Window(unsigned int width, unsigned int height, std::string w_name);
        unsigned int GetWidth();
        unsigned int GetHeight();
        void SetWidthHeight(unsigned int width, unsigned int height);
        GLFWwindow* GetWindow();
        void static FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
    private:
        unsigned int width;
        unsigned int height;
        std::string window_name;
        GLFWwindow* m_window;
};