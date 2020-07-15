#include "game_managing/BasicsBlock.hpp"
#include "personal_objects/bObject.hpp"

BasicsBlock::BasicsBlock(Window* window, InputManager* input, Time* time):
m_window(window),m_input(input),m_time(time){
    
    this->outline_shader = Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/Outline.frag");
    this->Model_string = std::string("Model");

    this->Mat_ambient = std::string("material.ambient");
    this->Mat_diffuse = std::string("material.diffuse");
    this->Mat_specular = std::string("material.specular");
    this->Mat_shininess = std::string("material.shininess");

    this->LampColor = std::string("LampColor");

    //Create the uniform buffer for light rendering, maybe change the location(??)
    glGenBuffers(1,&uniform_buffer_light);
    glBindBuffer(GL_UNIFORM_BUFFER,uniform_buffer_light);
    glBufferData(GL_UNIFORM_BUFFER,316,NULL,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
    glBindBufferBase(GL_UNIFORM_BUFFER,1,uniform_buffer_light);

    
}

void BasicsBlock::WindowResized(){
    was_resized = true;
}