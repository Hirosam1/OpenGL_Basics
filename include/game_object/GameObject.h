#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include"game_object/Shader.h"
#include "game_tools/stb_image.h"
#include "game_managing/InputManager.h"
#include "game_tools/Debugging.h"
#include "game_managing/Time.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class GameObject{
    public:
        //Constructors
        GameObject(InputManager* m_imput, Time* m_time);
        GameObject(InputManager* m_input, Time* m_time, float* vertex, unsigned int vertex_count,unsigned int* indices, unsigned int indices_count);

        //Public Updates
        void UpdateAndBuffer();

        //Shaders Management
        //Creates the shader object, ready to use
        void CreateShaderObject(std::string vertex_shader,std::string fragment_shader);

        //Sets up the object to be ready to update/render
        void SetUpObject();
        //Create the texture object
        void CreateTexture(std::string texture_path);

        bool test = false;
    private:
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        glm::mat4 trans;
        float rot =0;
        //Vertices of a triangle along with their indices and numberof points and indices
        float* vertex;
        unsigned int* indices;
        unsigned int vertex_count;
        unsigned int indices_count;
        //Window where the object will get inputs
        InputManager* m_input;
        //Vertex Buffer Object
        unsigned int VBO;
        //Element Buffer Objects
        unsigned int EBO;
        //Vertex Array Object
        unsigned int VAO;
        Shader* shader;
        //Texture ID
        unsigned int texture;
        Time* m_time;
    protected:
        //Children of GameObject class will inherit this method. This is where you update the data within GameObject
        void Update(); //Supposed to be virtual, in the future

        
};