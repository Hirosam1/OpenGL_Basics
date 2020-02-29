#include "game_object/Light.hpp"

Light::Light(BasicsBlock* bb, Camera* m_camera,Shape* shape, float initial_pos[3],
            std::string* vert, std::string* frag,float light_color[3],float light_intensit):
                GameObject(bb,m_camera,shape,initial_pos,vert,frag),
                light_intensity(light_intensity),light_color(glm::make_vec3(light_color)),
                light_ambient(this->light_color* 0.15f), light_specular(glm::vec3(1.0)){
    float* mat_model = glm::value_ptr(this->model);
    this->light_pos = &mat_model[12];

}

Light::Light(BasicsBlock* bb, Camera* m_camera,Shape* shape, float initial_pos[3],
            std::string* vert, std::string* frag,float light_intensity):
                GameObject(bb,m_camera,shape,initial_pos,vert,frag),
                light_intensity(light_intensity),light_color(glm::vec3(1,1,1)),
                light_ambient(this->light_color* 0.1f), light_specular(glm::vec3(1.0)){
    
    float* mat_model = glm::value_ptr(this->model);
    this->light_pos = &mat_model[12];

}

void Light::LampColorBuffering(){
    this->shader->UseShader();
    this->shader->SetUniformVec3f(&bb->LampColor,this->light_color);
}

void Light::Update(){
}