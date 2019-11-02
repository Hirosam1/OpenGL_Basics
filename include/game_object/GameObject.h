#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include"game_object/Shader.h"
#include "game_managing/stb_image.h"

class GameObject{
    public:
        //Vertices of a triangle
        float vertices[32];
        unsigned int indices[6];
        float texCoords[6];

        GameObject();
        void Update();
        void SetUpObject();
    private:
        //Vertex Buffer Object
        unsigned int VBO;
        //Element Buffer Objects
        unsigned int EBO;
        //Vertex Array Object
        unsigned int VAO;
        Shader* shader;
        //Load the textures
        void LoadTexture();
        unsigned int texture;

        
};