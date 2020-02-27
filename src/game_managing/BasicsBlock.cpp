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

    this->Basic_tex = std::string("material.texture1");

    this->DirLight_prefix = std::string("dirLight");
    this->PointLight_prefix = std::string("pointLight");
    this->SpotLight_prefix = std::string("spotLight");

    this->Light_ambient =  std::string(".ambient");
    this->Light_diffuse =  std::string(".diffuse");
    this->Light_specular = std::string(".specular");
    
    this->Light_pos = std::string(".positionVS");
    this->Light_direction = std::string(".directionVS");

    this->Light_constant = std::string(".constant");
    this->Light_linear = std::string(".linear");
    this->Light_quadratic = std::string(".quadratic");

    this->Light_CutOff = std::string(".cutOff");
    this->Light_OutCutoff = std::string(".outerCutOff");
}