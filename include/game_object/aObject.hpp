#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "game_object/GameObject.hpp"

class aObject : public GameObject{
    public:
        aObject(Window* aWindow,InputManager* m_input, Time* m_time, 
        GLfloat* vertex, unsigned int vertex_count,GLuint* indices, unsigned int indices_count, float initial_pos[3]);      
    private:
    void Update() override;
    unsigned int test_speed = 3;

};
