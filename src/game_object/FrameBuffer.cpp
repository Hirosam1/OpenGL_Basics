#include "game_object/FrameBuffer.hpp"

FrameBuffer::FrameBuffer(unsigned int width, unsigned height){
    glGenFramebuffers(1,&frame_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER,frame_buffer); 
    //Creates an "empty"  texture used by the frame buffer
    texture_color = new ScreenTexture();
    texture_color->CreateTexture(false,width,height);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texture_color->GetTexture(),0);  
    texture_color->tex_type = "texture_screen";
    //plane.meshes[0].textures.push_back(texColorBuffer);
    //Creates render buffer object
    glGenRenderbuffers(1, &render_buffer);
    glBindRenderbuffer(GL_RENDERBUFFER,render_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,width,height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    //Attach render buffer to  frame buffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,render_buffer);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << "\n";
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void FrameBuffer::UseFrameBuffer(){
     glBindFramebuffer(GL_FRAMEBUFFER,frame_buffer);
}

void FrameBuffer::ResetBuffers(unsigned int width, unsigned int height){
    texture_color->CreateTexture(false,width,height);
    glBindRenderbuffer(GL_RENDERBUFFER,render_buffer);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,width,height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}