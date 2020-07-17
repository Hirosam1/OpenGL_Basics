#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include <cstring>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include"game_tools/FileManagementTools.hpp"

class Shader{
    public:
        Shader();
        Shader(std::string vertex_shader_path, std::string fragment_shader_path);
        Shader(std::string vertex_shader_path, std::string geometry_shader_path,std::string fragment_shader_path);
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
    private:
        void SetUpUniformBuffers();
    protected:
        std::string vertex_path, fragment_path;
        unsigned int shader_comp;
        //unsigned int vertex_shader;
        //unsigned int fragment_shader;
        std::vector<unsigned int> shader_programs;
        unsigned int shader_program;
        unsigned int CreateShaderProgram();
};