#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"

Texture::Texture(){
    glGenTextures(1,&this->m_texture);
}

Texture::Texture(std::string texture_path,GLenum img_type, bool repeat):tex_type(tex_type){
    //Creates and binds the Texture object
    glGenTextures(1, &this->m_texture);
    CreateTexture(texture_path,img_type, repeat);
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

 void Texture::UseTexture(unsigned int texture_num,bool activate_tex){
     if(activate_tex)
        glActiveTexture(GL_TEXTURE0+texture_num); 
     glBindTexture(GL_TEXTURE_2D,this->m_texture);
 }

 unsigned int Texture::GetTexture(){
     return this->m_texture;
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
 }

 void CubeMapTexture::UseTexture(unsigned int tex_num){
    glActiveTexture(GL_TEXTURE0+tex_num); 
    glBindTexture(GL_TEXTURE_CUBE_MAP,this->m_texture);
 }