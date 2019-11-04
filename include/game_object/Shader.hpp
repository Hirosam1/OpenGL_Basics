#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include <cstring>
#include"game_tools/FileManagementTools.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    public:
        Shader();
        unsigned int LoadShader(std::string shader_path, GLenum shder_type);
        int LinkShaders();
        void UseShader();
        void SetUniform1i(std::string uniform_name,int i);
        void SetUniformMat4fv(std::string uniform_name,glm::mat4 m_mat4);
    protected:
        unsigned int shader_comp;
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        unsigned int shader_program;
        unsigned int CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
};