#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include"game_object/Shader.hpp"
#include "game_tools/stb_image.h"
#include "game_managing/InputManager.hpp"
#include "game_tools/Debugging.hpp"
#include "game_managing/Time.hpp"
#include "game_object/Window.hpp"



class GameObject{
    public:
        //Constructors
        GameObject(Window* aWindow,InputManager* m_imput, Time* m_time);
        GameObject(Window* aWindow,InputManager* m_input, Time* m_time, float* vertex, unsigned int vertex_count,unsigned int* indices, unsigned int indices_count);
        GameObject(Window* aWindow,InputManager* m_input, Time* m_time, float* vertex, unsigned int vertex_count,unsigned int* indices, unsigned int indices_count, float initial_pos[3]);

        //Public Updates
        void UpdateAndBuffer();

        //Shaders Management
        //Creates the shader object, ready to use
        void CreateShaderObject(std::string vertex_shader,std::string fragment_shader);

        //Sets up the object to be ready to update/render
        void SetUpObject();

        bool test = false;
    private:
        //The transformation matrixes
        glm::mat4 model; 
        glm::mat4 view;
        glm::mat4 projection;
        //Window size for the projection
        unsigned int width;
        unsigned int height;

        //Vertices of a triangle along with their indices and numberof points and indices
        float* vertex;
        unsigned int* indices;
        unsigned int vertex_count;
        unsigned int indices_count;

        //Vertex Buffer Object
        unsigned int VBO;
        //Element Buffer Objects
        unsigned int EBO;
        //Vertex Array Object
        unsigned int VAO;

        //Window where the object will get inputs
        InputManager* m_input;
        //Shader Object
        Shader* shader;
        //Texture Object
        //Texture* m_texture;
        //Time object
        Time* m_time;
    protected:
        Window* m_window;
        //Children of GameObject class will inherit this method. This is where you update the data within GameObject
        void Update(); //Supposed to be virtual, in the future

        
};