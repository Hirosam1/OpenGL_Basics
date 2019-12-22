#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include"game_tools/FileManagementTools.hpp"

class Texture;

class Shader{
    public:
        Shader();
        unsigned int LoadShader(std::string* shader_path, GLenum shder_type);
        int LinkShaders();
        //Uses shader before rendering
        void UseShader(bool use_texture = true);
        //Sets the uniform of 1 int
        void SetUniform1i(std::string* uniform_name,int i);
        //Sets the uniform of a mat 4
        void SetUniformMat4f(std::string* uniform_name,glm::mat4 m_mat4);
        //Sets the uniform of a float
        void SetUniform1f(std::string* shader_name, float i);
        void SetUniformVec3f(std::string* uniform_name,glm::vec3 vec3);
        //Creates a texture object and uses the path name to apply it
        void SetTexture(std::string* texture_name,std::string* uniform_name,GLenum type = GL_RGB);
    protected:
        unsigned int shader_comp;
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        unsigned int shader_program;
        unsigned int CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
        Texture* m_texture;
        std::list<Texture*>* m_textures;
};