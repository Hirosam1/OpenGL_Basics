#include "game_managing/BasicsBlock.hpp"
BasicsBlock::BasicsBlock(Window* window, InputManager* input, Time* time,std::vector<GameObject*>* all_objs):
m_window(window),m_input(input),m_time(time), all_objs(all_objs){
    
    this->Model_string = std::string("Model");
    this->View_string = std::string("View");
    this->Projection_string = std::string("Projection");

    this->Mat_ambient = std::string("material.ambient");
    this->Mat_diffuse = std::string("material.diffuse");
    this->Mat_specular = std::string("material.specular");
    this->Mat_shininess = std::string("material.shininess");

    this->Light_ambient =  std::string("light.ambient");
    this->Light_diffuse =  std::string("light.diffuse");
    this->Light_specular = std::string("light.specular");
    this->Light_pos = std::string("light.position");
    this->Basic_tex = std::string("material.texture1");

    this->Light_direction = std::string("light.direction");

    this->Light_constant = std::string("light.constant");
    this->Light_linear = std::string("light.linear");
    this->Light_quadratic = std::string("light.quadratic");

    this->Light_CutOff = std::string("light.cutOff");
    this->Light_OutCutoff = std::string("light.outerCutOff");
}