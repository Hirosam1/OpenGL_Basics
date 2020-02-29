#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Window.hpp"
#include "game_object/Projection.hpp"

class Camera{
    public:
        glm::vec3 camera_pos;
        glm::vec3 camera_front;
        glm::vec3 camera_up;
        Camera(Window* aWindow, float initial_pos[3] = new float[3]{0,0,0});
        const glm::mat4 GetView();
        const glm::mat4 GetProjection();
        void MakeProjection(float fov, float aspect_ratio = -1.0f,float close = 0.1f, float far = 100.0f);
        void LookAt(float target[3]); 
        void LookAt(glm::vec3 target);
        void UpdateView();
        
    private:
        float projection_fov;
        Window* m_window;
        float width;
        float height;
        glm::mat4 m_view;
        Projection* m_projection;

};