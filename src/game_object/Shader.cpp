#include "game_object/Shader.hpp"
#include"game_object/Texture.hpp"

Shader::Shader(){
    this->m_texture = nullptr;
    this->shader_comp = 0;
}

unsigned int Shader::LoadShader(std::string shader_path, GLenum shader_type){
    unsigned int shader_id;
    //Create and compile shder
    shader_id = glCreateShader(shader_type);
    int size;
    const char* shader_source = FileManagementTools::GetFilesContents(shader_path.data(),&size);
    glShaderSource(shader_id,1,&shader_source,&size);
    glCompileShader(shader_id);

    int success;
    //Checks for success
    glGetShaderiv(shader_id,GL_COMPILE_STATUS,&success);
    if(!success){
        int logLength;
        glGetShaderiv(shader_id,GL_INFO_LOG_LENGTH,&logLength);
        auto errorLog = new char[logLength];
        glGetShaderInfoLog(shader_id,logLength,&logLength,errorLog);
        std::cout<<"Error at copiling the shader: " <<shader_path<<std::endl<<"INFO-> "<<errorLog<<std::endl;
        exit(-1);
    }
    if(shader_type == GL_VERTEX_SHADER){this->vertex_shader = shader_id;}
    if(shader_type == GL_FRAGMENT_SHADER){this->fragment_shader = shader_id;}

    delete shader_source;
    this->shader_comp++;
    return shader_id;
}

int Shader::LinkShaders(){
    if(shader_comp < 2){
        std::cout<<"Not enought compiled shaders!";
        throw "Not enought compiled shaders!";
        return -1;
    }
    CreateShaderProgram(this->vertex_shader,this->fragment_shader);
    return 1;
}

unsigned int Shader::CreateShaderProgram(unsigned int vertex_shader, unsigned int fragment_shader){
    unsigned int shader_program;
    int success;

    //Atacch and link the shaders
    this->shader_program = glCreateProgram();
    glAttachShader(this->shader_program,this->vertex_shader);
    glAttachShader(this->shader_program,this->fragment_shader);
    glLinkProgram(this->shader_program);

    glGetProgramiv(this->shader_program,GL_LINK_STATUS,&success);
    if(!success){
        int logLength;
        glGetProgramiv(shader_program,GL_INFO_LOG_LENGTH,&logLength);
        auto errorLog = new char[logLength];
        glGetProgramInfoLog(shader_program,logLength,&logLength,errorLog);
        std::cout<<"Error at linking the shaders: " <<shader_program<<std::endl<<"INFO-> "<<errorLog<<std::endl;
        throw "Error at linking the shaders:";
    }

    glDeleteShader(this->vertex_shader);
    glDeleteShader(this->fragment_shader);
    this->shader_comp = 0;
    return shader_program;
}

void Shader::SetTexture(std::string texture_name){
    this->m_texture = new Texture(this,texture_name,"texture1",0);
}

void Shader::UseShader(bool use_texture){
    if(this->m_texture != nullptr && use_texture){
        this->m_texture->UseTexture();
    }
    glUseProgram(this->shader_program);
}

void Shader::SetUniform1i(std::string uniform_name,int i){
    glUniform1f(glGetUniformLocation(this->shader_program,uniform_name.data()),i);
}

void Shader::SetUniformMat4fv(std::string uniform_name,glm::mat4 m_mat4){
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program,uniform_name.data()),1,GL_FALSE,glm::value_ptr(m_mat4));
}

void Shader::SetFloat(std::string uniform_name, float i ){
    glUniform1f(glGetUniformLocation(this->shader_program,uniform_name.data()),i);
}