#include "game_managing/BasicsBlock.hpp"
BasicsBlock::BasicsBlock(Window* window, InputManager* input, Time* time):
m_window(window),m_input(input),m_time(time){
    
    this->Model_string = new std::string("Model");
    this->View_string = new std::string("View");
    this->Projection_string = new std::string("Projection");

    this->Mat_ambient = new std::string("material.ambient");
    this->Mat_diffuse = new std::string("material.diffuse");
    this->Mat_specular = new std::string("material.specular");
    this->Mat_shininess = new std::string("material.shininess");

    this->Light_ambient = new std::string("light.ambient");
    this->Light_diffuse = new std::string("light.diffuse");
    this->Light_specular = new std::string("light.specular");
    this->Light_pos = new std::string("light.position");
    this->Basic_tex = new std::string("material.texture1");
}