#include "graphics/Window.hpp"

Window::Window(unsigned int width, unsigned int height,std::string w_name):
width(width), height(height), window_name(w_name) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->m_window = glfwCreateWindow(width,height,this->window_name.data(),NULL,NULL);
    if(!this->m_window){
        std::cout<<"Error at creating windown!\n";
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(this->m_window);
    glfwSetFramebufferSizeCallback(this->m_window,this->FrameBufferSizeCallback);
}
GLFWwindow* Window::GetWindow(){
    return this->m_window;
}

void Window::SetWidthHeight(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
}

unsigned int Window::GetWidth(){
    return this->width;
}

unsigned int Window::GetHeight(){
    return this->height;
}

void Window::FrameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
    BasicsBlock* here = static_cast<BasicsBlock*>(glfwGetWindowUserPointer(window));
    here->m_window->SetWidthHeight(width,height);
}