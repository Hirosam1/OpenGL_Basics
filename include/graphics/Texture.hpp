
#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include<vector>
#include "game_tools/stb_image.h"

class Texture{
    
    public:
        Texture(std::string texture_path, GLenum img_type = GL_RGBA, bool repeat = false);
        Texture();
        void CreateTexture(std::string texture_path,bool repeat,GLenum img_type = GL_RGBA);
        void CreateTexture(bool repeat,  unsigned int width, unsigned int height,GLenum img_type = GL_RGBA);
        void UseTexture(unsigned int texture_num = 0, bool activate_tex = true);
        unsigned int GetTexture();
        std::string tex_type;
        std::string path;
        
    private:
        void CreateTexture(std::string* texture_path,bool repeat,GLenum img_type, unsigned int width = 1, unsigned int height = 1);
    protected:
        unsigned int m_texture;
};

class CubeMapTexture : public Texture{
    public:
        CubeMapTexture(std::vector<std::string> paths);
        void CreateTexture(std::vector<std::string> paths);
        void UseTexture(unsigned int texture_num = 0); 
};