#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include <cstring>
#include"game_managing/FileManagementTools.h"

class Shader{
    public:
        Shader();
        unsigned int LoadShader(std::string shader_path, GLenum shder_type);
        int LinkShaders();
        void UseShader();
        void SetUniform1i(std::string uniform_name,int i);
    protected:
        unsigned int shader_comp;
        unsigned int vertex_shader;
        unsigned int fragment_shader;
        unsigned int shader_program;
        unsigned int CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader);
};