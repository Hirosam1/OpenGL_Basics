#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<string.h>
#include<string>

class Projection{
    public:
        Projection(float fov, float aspect_ratio,float close = 0.1f, float far = 100.0f);
        void MakePerspective(float fov, float aspect_ratio,float close = 0.1f, float far = 100.0f);
        glm::mat4 GetProjection();
    private:
        glm::mat4 projection;
};