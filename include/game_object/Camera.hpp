#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
    public:
        glm::vec3 *camera_pos;
        //float* camera_pos;
        //float* camera_target;
        Camera(float initial_pos[3]);
        const glm::mat4 GetView();
        void LookAt(float target[3]); 
        void UpdateView();
    private:
        glm::mat4 m_view;

};