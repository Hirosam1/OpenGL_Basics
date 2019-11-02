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

class GameObject{
    public:
        //Vertices of a triangle
        float vertices[32];
        unsigned int indices[6];
        float texCoords[6];

        GameObject(InputManager* m_imput, Time* m_time);
        void UpdateAndBuffer();
        void CreateShaderObject(std::string vertex_shader,std::string fragment_shader);
        void SetUpObject();
        //Create the texture object
        void CreateTexture(std::string texture_path);
    private:
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