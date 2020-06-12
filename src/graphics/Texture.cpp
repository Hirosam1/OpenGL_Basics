#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"

Texture::Texture(){
    glGenTextures(1, &this->m_texture);
}

void Texture::UnloadTexture(){
    glDeleteTextures(1, &this->m_texture);
}
//texture_path,repeat,img_type
Texture::Texture(std::string texture_path, bool repeat, GLenum img_type){
    //Creates and binds the Texture object
    glGenTextures(1, &this->m_texture);
    CreateTexture(texture_path,repeat, img_type);
}

void Texture::CreateTexture(std::string texture_path,bool repeat,GLenum type){
    std::cout<<"Loading texture ->" << texture_path << "\n";
    this->CreateTexture(&texture_path,repeat,type);
    
 }

void Texture:: CreateTexture(bool repeat,  unsigned int width, unsigned int height,GLenum img_type){
    this->CreateTexture(nullptr,repeat,img_type,width,height);
} 

void Texture::CreateTexture(std::string* texture_path,bool repeat,GLenum type, unsigned int width, unsigned int height){
    GLenum warraping_method = 0;
    if(repeat){
        warraping_method = GL_REPEAT;
    }else{
        warraping_method = GL_CLAMP_TO_EDGE;
    }

    glBindTexture(GL_TEXTURE_2D,this->m_texture);

    //Sets the parameters for warapping and filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,warraping_method);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,warraping_method);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    //stbi_set_flip_vertically_on_load(true);  

    if(texture_path != nullptr){
        int img_width, img_height, nrChannels;
        //Loads image
        unsigned char *data = stbi_load(texture_path->data(), &img_width, &img_height, &nrChannels, 0); 
        if(data){
        //Creats the texture image on the current bound texture object
        glTexImage2D(GL_TEXTURE_2D,0,type,img_width,img_height,0,type,GL_UNSIGNED_BYTE,data);
        //Genetates mip maps automaticaly
        glGenerateMipmap(GL_TEXTURE_2D);
        //Free loaded image
        }else{
            std::cout<<"Failed to load image texture\n";
            exit(-1);

        }
        stbi_image_free(data);
    }else{
        glTexImage2D(GL_TEXTURE_2D,0,type,width,height,0,type,GL_UNSIGNED_BYTE,NULL);
    }
    glBindTexture(GL_TEXTURE_2D,0);
}

 unsigned int Texture::GetTexture(){
     return this->m_texture;
 }

 CubeMapTexture::CubeMapTexture (std::string path) : Texture(){
    std::vector<std::string> faces
    {
    "right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"
    };
    for(int i = 0; i < faces.size() ; i++){
    faces[i] = path + "/" + faces[i];
    }
    std::cout<<"Loading Cube Tex images...\n";
    tex_type = "skybox";
    CreateTexture(faces);
 }

 CubeMapTexture::CubeMapTexture(std::vector<std::string> paths):Texture(){
    std::cout<<"Loading Cube Tex images...\n";
    tex_type = "skybox";
    CreateTexture(paths);
 }

 void CubeMapTexture::CreateTexture(std::vector<std::string> paths){
    int width, height, nrChannels;
    glBindTexture(GL_TEXTURE_CUBE_MAP,this->m_texture);
    
    for (int i = 0; i < paths.size(); i++){
        unsigned char *data = stbi_load(paths[i].data(), &width, &height, &nrChannels,0);
        if (data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
            stbi_image_free(data);
        }else{
            std::cout<<"Failed to load cube image texture\n";
            exit(-1);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
 }

 void CubeMapTexture::UseTexture(unsigned int tex_num, Shader* shader){
    std::string name = "skybox";
    shader->SetUniform1i(&tex_type,tex_num);
    glActiveTexture(GL_TEXTURE0+tex_num); 
    glBindTexture(GL_TEXTURE_CUBE_MAP,this->m_texture);
}

 DiffuseTexture::DiffuseTexture(unsigned int uniform_num, std::string texture_path, bool repeat, GLenum img_type) : Texture(texture_path,repeat,img_type), m_uniform_num(uniform_num){
     //CreateTexture(texture_path,repeat,img_type);
 }

 void DiffuseTexture::UseTexture(unsigned int texture_num, Shader* shader){
    std::string hastype = "material.has_TexDiffuse";
    shader->SetUniform1i(&hastype,1);
    std::string name = ("material.texture_diffuse"  + std::to_string(m_uniform_num));
    shader->SetUniform1i(&name,texture_num);
    glActiveTexture(GL_TEXTURE0+texture_num); 
    glBindTexture(GL_TEXTURE_2D,this->m_texture);


 }

 SpecularTexture::SpecularTexture(unsigned int uniform_num, std::string texture_path, bool repeat, GLenum img_type) : Texture(texture_path,repeat,img_type), m_uniform_num(uniform_num){
     //CreateTexture(texture_path,repeat,img_type);
 }

 void SpecularTexture::UseTexture(unsigned int texture_num, Shader* shader){
    std::string hastype = "material.has_TexSpecular";
    shader->SetUniform1i(&hastype,1);
    std::string name = ("material.texture_specular" + std::to_string(m_uniform_num));
    shader->SetUniform1i(&name,texture_num);
    glActiveTexture(GL_TEXTURE0+texture_num); 
    glBindTexture(GL_TEXTURE_2D,this->m_texture);


 }

 ScreenTexture::ScreenTexture() : Texture(){

 }

 void ScreenTexture::UseTexture(unsigned int texture_num, Shader* shader){
    std::string name = "screenTex";
    shader->SetUniform1i(&name,0);
    glActiveTexture(GL_TEXTURE0+texture_num); 
    glBindTexture(GL_TEXTURE_2D,this->m_texture);

 }