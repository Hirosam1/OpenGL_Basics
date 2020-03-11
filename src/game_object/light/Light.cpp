#include "game_object/Light.hpp"

Light::Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3],
            Shader* m_shader,float light_color[3],float light_intensit):
                GameObject(bb,m_camera,model,initial_pos,m_shader),
                light_intensity(light_intensity),light_color(glm::make_vec3(light_color)),
                light_ambient(glm::vec3(0)), light_specular(glm::vec3(1.0)){
    float* mat_model = glm::value_ptr(this->model_mat);
    this->light_pos = &mat_model[12];

}

Light::Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3],
            Shader* m_shader,float light_intensity):
                GameObject(bb,m_camera,model,initial_pos,m_shader),
                light_intensity(light_intensity),light_color(glm::vec3(1,1,1)),
                light_ambient(glm::vec3(0)), light_specular(glm::vec3(1.0)){
    
    float* mat_model = glm::value_ptr(this->model_mat);
    this->light_pos = &mat_model[12];
}

Light::Light(BasicsBlock* bb, Camera* m_camera, float initial_pos[3], float light_intensity) : 
                GameObject(bb,m_camera,initial_pos), light_intensity(light_intensity),
                light_color(glm::vec3(1,1,1)),light_ambient(glm::vec3(0)), 
                light_specular(glm::vec3(1.0)){

    float* mat_model = glm::value_ptr(this->model_mat);
    this->light_pos = &mat_model[12];

}

void Light::LampColorBuffering(){
    if(this->m_shader != nullptr){
        this->m_shader->SetUniformVec3f(&bb->LampColor,this->light_color);
    }
}

void Light::Update(){
}