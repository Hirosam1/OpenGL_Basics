#include "game_object/Light.hpp"

PointLight::PointLight(BasicsBlock* basic_block, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader, float direction[3]):Light(basic_block,m_camera,model,initial_pos,m_shader),
        constant(1.0f),linear(0.12f),quadratic(0.04f){

}
PointLight::PointLight(BasicsBlock* basic_block, Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader , int index,float linear, float quadratic, float constant) : 
Light(basic_block,m_camera,model,initial_pos,m_shader), constant(constant),linear(linear),quadratic(quadratic),index(index){

}

void PointLight::LightBuffering(){
    /*
    if(go->m_shader != nullptr){
        //vvv Change the one to the numbers of light in the scene vvv
        go->m_shader->SetUniform1i(&basic_block->n_point_lights_string,1);
        //^^^ Change the one to the numbers of light in the scene ^^^
        std::string uniform_name = this->LightPrefix + basic_block->Light_ambient;

        go->m_shader->SetUniformVec3f(&uniform_name,this->light_ambient);
        uniform_name = this->LightPrefix + basic_block->Light_diffuse;

        go->m_shader->SetUniformVec3f(&uniform_name,this->light_color * this->light_intensity);
        uniform_name = this->LightPrefix+ basic_block->Light_specular;

        go->m_shader->SetUniformVec3f(&uniform_name,this->light_specular * this->light_intensity);
        uniform_name = this->LightPrefix + basic_block->Light_pos;

        go->m_shader->SetUniformVec3f(&uniform_name,glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->light_pos),1)));

        uniform_name = this->LightPrefix + basic_block->Light_constant;
        go->m_shader->SetUniform1f(&uniform_name,this->constant);

        uniform_name = this->LightPrefix + basic_block->Light_linear;
        go->m_shader->SetUniform1f(&uniform_name,this->linear);
        uniform_name = this->LightPrefix+ basic_block->Light_quadratic;
        go->m_shader->SetUniform1f(&uniform_name,this->quadratic);
    }
    */
}