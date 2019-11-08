
#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include "game_tools/stb_image.h"

class Shader;

class Texture{
    
    public:
        Texture(Shader* m_shader, std::string* texture_path, std::string* uniform_name,unsigned int uniform_index);
        void CreateTexture(std::string* texture_name,std::string* uniform_name,unsigned int uniform_index);
        void UseTexture();
        
    private:
        unsigned int m_texture;
        Shader* m_shader;

};