#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

class InputManager{
    public:
        InputManager();
        static void ProcessInput(GLFWwindow* window);
};