#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"

Texture::Texture(Shader* m_shader, std::string* texture_path, std::string* uniform_name,unsigned int uniform_index, GLenum type):
m_shader(m_shader){
    CreateTexture(texture_path, uniform_name, uniform_index,type);
}

void Texture::CreateTexture(std::string* texture_path,std::string* uniform_name,unsigned int uniform_index,GLenum type){

    //Creates and binds the Texture object
    glGenTextures(1, &this->m_texture);
    glBindTexture(GL_TEXTURE_2D,this->m_texture);

    //Sets the parameters for warapping and filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    //stbi_set_flip_vertically_on_load(true);  
    int width, height, nrChannels;
    //Loads image
    unsigned char *data = stbi_load(texture_path->data(), &width, &height, &nrChannels, 0); 
    if(data){
    //Creats the texture image on the current bound texture object
    glTexImage2D(GL_TEXTURE_2D,0,type,width,height,0,type,GL_UNSIGNED_BYTE,data);
    //Genetates mip maps automaticaly
    glGenerateMipmap(GL_TEXTURE_2D);
    //Free loaded image
    }else{
        std::cout<<"Failed to load image texture\n";
        exit(-1);
    }
    stbi_image_free(data);
    //glBindTexture(GL_TEXTURE_2D,0);
    this->m_shader->UseShader(false);
    this->m_shader->SetUniform1i(uniform_name,uniform_index);
    
 }
 
 void Texture::UseTexture(unsigned int texture_num){

     glActiveTexture(GL_TEXTURE0+texture_num); glBindTexture(GL_TEXTURE_2D,this->m_texture);
 }