
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
        Texture(std::string texture_path, bool repeat = false, GLenum img_type = GL_RGBA);
        Texture();
        void CreateTexture(std::string texture_path,bool repeat,GLenum img_type = GL_RGBA);
        void CreateTexture(bool repeat,  unsigned int width, unsigned int height,GLenum img_type = GL_RGBA);
        virtual void UseTexture(unsigned int texture_num, Shader* shader) = 0;
        //virtual void FinishTexture() = 0;
        unsigned int GetTexture();
        std::string tex_type;
        std::string path;
        void UnloadTexture();
    private:
        void CreateTexture(std::string* texture_path,bool repeat,GLenum img_type, unsigned int width = 1, unsigned int height = 1);
    protected:
        unsigned int m_texture;
};


class DiffuseTexture : public Texture{
    public:
        DiffuseTexture(unsigned int uniform_num, std::string texture_path, bool repeat = false,  GLenum img_type = GL_RGBA);
        unsigned int m_uniform_num;
        void UseTexture(unsigned int texture_num, Shader* shader) override;
        //void FinishTexture() override;
};

class SpecularTexture : public Texture{
    public:
        SpecularTexture(unsigned int uniform_num, std::string texture_path, bool repeat = false,  GLenum img_type = GL_RGBA);
        unsigned int m_uniform_num;
        void UseTexture(unsigned int texture_num, Shader* shader) override;
        //void FinishTexture() override;
};

class ScreenTexture : public Texture{
    public:
        ScreenTexture();
        void UseTexture(unsigned int texture_num, Shader* shader) override; 
};

class CubeMapTexture : public Texture{
    public:
        CubeMapTexture(std::vector<std::string> paths);
        CubeMapTexture(std::string path);
        void CreateTexture(std::vector<std::string> paths);
        void UseTexture(unsigned int texture_num, Shader* shader) override; 
};