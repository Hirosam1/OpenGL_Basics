#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>


class Window{
    public:
        Window(unsigned int width, unsigned int height, std::string w_name);
        unsigned int GetWidth();
        unsigned int GetHeight();
        void SetWidthHeight(unsigned int width, unsigned int height);
        GLFWwindow* GetWindow();
    private:
        unsigned int width;
        unsigned int height;
        std::string window_name;
        GLFWwindow* m_window;
};