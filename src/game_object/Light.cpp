#include "game_object/Light.hpp"

Light::Light(BasicsBlock* bb, Camera* m_camera,Shape* shape, float initial_pos[3],
            std::string* vert, std::string* frag,float light_intensity, glm::vec3 light_color):
                GameObject(bb,m_camera,shape,initial_pos,vert,frag),
                light_intensity(light_intensity),light_color(light_color),
                light_ambient(light_color* 0.15f), light_specular(glm::vec3(1.0)){
    float* mat_model = glm::value_ptr(this->model);
    this->light_pos = &mat_model[12];

}

void Light::Update(){
}