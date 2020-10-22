#include "personal_objects/ToonTexture.hpp"

ToonTexture::ToonTexture(std::string texture_path, bool repeat,  GLenum img_type): Texture(texture_path,repeat,img_type){
}

void ToonTexture::UseTexture(unsigned int texture_num, Shader* shader){
    std::string name = "toon_shader";
    shader->SetUniform1i(&name,texture_num);
    glActiveTexture(GL_TEXTURE0+texture_num); 
    glBindTexture(GL_TEXTURE_2D,this->m_texture);
}