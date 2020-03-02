
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
        Texture(std::string texture_path, GLenum img_type = GL_RGB, std::string tex_type = std::string("Default"));
        Texture();
        void CreateTexture(std::string texture_path,GLenum img_type = GL_RGB);
        void UseTexture(unsigned int texture_num = 0, bool activate_tex = true);
        std::string tex_type;
        std::string path;
        
    private:
        unsigned int m_texture;
};