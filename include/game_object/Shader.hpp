#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"game_tools/FileManagementTools.hpp"

class Texture;

class Shader{
    public:
        Shader();
        unsigned int LoadShader(std::string shader_path, GLenum shder_type);
        int LinkShaders();
        void UseShader(bool use_texture = true);
        void SetUniform1i(std::string uniform_name,int i);
        void SetUniformMat4fv(std::string uniform_name,glm::mat4 m_mat4);
        void SetFloat(std::string shader_name, float i);
        void SetTexture(std::string texture_name);
    protected:
        unsigned int shader_comp;
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        unsigned int shader_program;
        unsigned int CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
        Texture* m_texture;
};