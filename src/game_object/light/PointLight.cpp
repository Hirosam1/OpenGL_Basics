#include "game_object/Light.hpp"

PointLight::PointLight(BasicsBlock* bb, Camera* m_camera,Model* model,float initial_pos[3],std::string vert, std::string frag , int index,float linear, float quadratic, float constant) : 
Light(bb,m_camera,model,initial_pos,vert,frag), constant(constant),linear(linear),quadratic(quadratic),index(index){
    char buffer[50];
    snprintf(buffer,sizeof(buffer),bb->PointLights_prefix.data(),this->index);
    this->LightPrefix = std::string(buffer);

}

void PointLight::LightBuffering(GameObject* go){
    if(go->m_shader != nullptr){
        go->m_shader->UseShader();

        go->m_shader->SetUniform1i(&bb->n_point_lights_string,bb->n_point_lights);
        std::string uniform_name = this->LightPrefix + bb->Light_ambient;

        go->m_shader->SetUniformVec3f(&uniform_name,this->light_ambient);
        uniform_name = this->LightPrefix + bb->Light_diffuse;

        go->m_shader->SetUniformVec3f(&uniform_name,this->light_color * this->light_intensity);
        uniform_name = this->LightPrefix+ bb->Light_specular;

        go->m_shader->SetUniformVec3f(&uniform_name,this->light_specular * this->light_intensity);
        uniform_name = this->LightPrefix + bb->Light_pos;

        go->m_shader->SetUniformVec3f(&uniform_name,glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->light_pos),1)));

        uniform_name = this->LightPrefix + bb->Light_constant;
        go->m_shader->SetUniform1f(&uniform_name,this->constant);

        uniform_name = this->LightPrefix + bb->Light_linear;
        go->m_shader->SetUniform1f(&uniform_name,this->linear);
        uniform_name = this->LightPrefix+ bb->Light_quadratic;
        go->m_shader->SetUniform1f(&uniform_name,this->quadratic);
    }
}