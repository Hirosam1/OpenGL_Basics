#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

class InputManager{
    public:
        InputManager(GLFWwindow* window);
        bool ProcessInput(int key, int action) const;
    private:
        GLFWwindow* window;
};