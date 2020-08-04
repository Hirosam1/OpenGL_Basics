#include "graphics/Shader.hpp"
#include"graphics/Texture.hpp"

Shader::Shader(){
    this->shader_comp = 0;
    this->shader_program = 0;
}

void Shader::UnLoadShader(){
    glDeleteShader(this->shader_program);
}

Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path): vertex_path(vertex_shader_path), fragment_path(fragment_shader_path){
    LoadShader(&vertex_shader_path, GL_VERTEX_SHADER);
    LoadShader(&fragment_shader_path, GL_FRAGMENT_SHADER);
    LinkShaders();
    SetUpUniformBuffers();
}

Shader::Shader(std::string vertex_shader_path, std::string geometry_shader_path,std::string fragment_shader_path): vertex_path(vertex_shader_path), fragment_path(fragment_shader_path){
    LoadShader(&vertex_shader_path, GL_VERTEX_SHADER);
    LoadShader(&geometry_shader_path, GL_GEOMETRY_SHADER);
    LoadShader(&fragment_shader_path, GL_FRAGMENT_SHADER);
    LinkShaders();
    SetUpUniformBuffers();
}

void Shader::SetUpUniformBuffers(){
    unsigned int camera_index = glGetUniformBlockIndex(this->shader_program,"Camera");
    if(camera_index == GL_INVALID_INDEX){
    }
    glUniformBlockBinding(this->shader_program,camera_index,0);
    unsigned int lights_index = glGetUniformBlockIndex(this->shader_program,"Lights");
    glUniformBlockBinding(this->shader_program,lights_index,1);
}

unsigned int Shader::LoadShader(std::string* shader_path, GLenum shader_type){
    unsigned int shader_id;
    //Create and compile shder
    shader_id = glCreateShader(shader_type);
    int size;
    const char* shader_source = FileManagementTools::GetFilesContents(shader_path->data(),&size);
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
        std::string shader_tpye_str = shader_type == GL_VERTEX_SHADER? "vertex shader" : shader_type == GL_GEOMETRY_SHADER? "geometry shader" : "fragment shader";
        std::cout<<"Error at copiling the " << shader_tpye_str << " : " <<*shader_path<<std::endl<<"INFO-> "<<errorLog<<std::endl;
        throw std::runtime_error("Error at copiling the -"+ shader_tpye_str + "-: " + *shader_path + "||INFO-> " + errorLog);
    }
    this->shader_programs.push_back(shader_id);

    delete shader_source;
    this->shader_comp++;
    return shader_id;
}

int Shader::LinkShaders(){
    if(this->shader_programs.size() < 2){
        std::cout<<"Not enought compiled shaders!";
        throw std::runtime_error("Not enought compiled shaders!");
        return -1;
    }
    CreateShaderProgram();
    return 1;
}

unsigned int Shader::CreateShaderProgram(){
    int success;

    //Atacch and link the shaders
    this->shader_program = glCreateProgram();
    for(int i = 0; i < this->shader_programs.size(); i++){
        glAttachShader(this->shader_program,this->shader_programs[i]);
    }
    glLinkProgram(this->shader_program);

    glGetProgramiv(this->shader_program,GL_LINK_STATUS,&success);
    if(!success){
        int logLength;
        glGetProgramiv(shader_program,GL_INFO_LOG_LENGTH,&logLength);
        auto errorLog = new char[logLength];
        glGetProgramInfoLog(shader_program,logLength,&logLength,errorLog);
        std::cout<<"Error at linking the shaders: " <<vertex_path << " and " <<fragment_path <<std::endl<<"\t INFO-> "<<errorLog<<std::endl;
        throw std::runtime_error("Error at linking the shaders: " + vertex_path + " and " + fragment_path + " ||INFO-> " + errorLog);
    }
    for(int i = 0; i < this->shader_programs.size(); i++){
        glDeleteShader(this->shader_programs[i]);
    }
    this->shader_comp = 0;
    return shader_program;
}

void Shader::UseShader(bool use_texture){
    glUseProgram(this->shader_program);
}

void Shader::SetUniform1i(std::string* uniform_name,int i){
    glUniform1i(glGetUniformLocation(this->shader_program,uniform_name->data()),i);
}

void Shader::SetUniformMat4f(std::string* uniform_name,glm::mat4 m_mat4){
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program,uniform_name->data()),1,GL_FALSE,glm::value_ptr(m_mat4));
}

void Shader::SetUniform1f(std::string* uniform_name, float i ){
    glUniform1f(glGetUniformLocation(this->shader_program,uniform_name->data()),i);
}

void Shader::SetUniformVec3f(std::string* uniform_name, glm::vec3 vec3 ){
    glUniform3f(glGetUniformLocation(this->shader_program,uniform_name->data()),vec3.x,vec3.y,vec3.z);
}
