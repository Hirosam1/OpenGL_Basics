#include "game_object/Light.hpp"

PointLight::PointLight(BasicsBlock* bb, Camera* m_camera,Shape* shape,float initial_pos[3],std::string* vert, std::string* frag ,float liniar, float quadratic, float constant) : 
Light(bb,m_camera,shape,initial_pos,vert,frag), constant(constant),linear(linear),quadratic(quadratic){

}

void PointLight::LightBuffering(GameObject* go){
    if(go->shader != nullptr){
        go->shader->UseShader();
        std::string uniform_name = bb->PointLight_prefix + bb->Light_ambient;
        go->shader->SetUniformVec3f(&uniform_name,this->light_ambient);
        uniform_name = bb->PointLight_prefix + bb->Light_diffuse;
        go->shader->SetUniformVec3f(&uniform_name,this->light_color * this->light_intensity);
        uniform_name = bb->PointLight_prefix + bb->Light_specular;
        go->shader->SetUniformVec3f(&uniform_name,this->light_specular * this->light_intensity);
        uniform_name = bb->PointLight_prefix + bb->Light_pos;
        go->shader->SetUniformVec3f(&uniform_name,glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->light_pos),1)));
        uniform_name = bb->PointLight_prefix + bb->Light_constant;
        go->shader->SetUniform1f(&uniform_name,this->constant);
        uniform_name = bb->PointLight_prefix + bb->Light_linear;
        go->shader->SetUniform1f(&uniform_name,this->linear);
        uniform_name = bb->PointLight_prefix + bb->Light_quadratic;
        go->shader->SetUniform1f(&uniform_name,this->quadratic);

        //We already calculate the cosine here since we will compare it to the dot product of the fragment angle
         /*shader->SetUniform1f(&this->bb->Light_CutOff, glm::cos(glm::radians(12.5)));
         shader->SetUniform1f(&this->bb->Light_OutCutoff, glm::cos(glm::radians(18.0)));*/
    }
}