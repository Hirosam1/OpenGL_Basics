#include "game_object/Light.hpp"

SpotLight::SpotLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3],Shader* m_shader, float direction[3]):
                        Light(bb,m_camera,model,initial_pos,m_shader), direction(direction){

}

SpotLight::SpotLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader):
                        Light(bb,m_camera,model,initial_pos,m_shader), direction(this->light_pos){

}

SpotLight::SpotLight(BasicsBlock* bb, Camera* m_camera, float initial_pos[3], float direction[3]) : Light(bb,m_camera, initial_pos), direction(direction){

}

void SpotLight::LightBuffering(GameObject* go){
    if(go->m_shader != nullptr){
        std::string uniform_name = bb->SpotLight_prefix + bb->Light_diffuse;
        go->m_shader->SetUniformVec3f(&uniform_name,this->light_color * this->light_intensity);
        uniform_name = bb->SpotLight_prefix + bb->Light_specular;
        go->m_shader->SetUniformVec3f(&uniform_name,this->light_specular * this->light_intensity);
        uniform_name = bb->SpotLight_prefix + bb->Light_pos;
        go->m_shader->SetUniformVec3f(&uniform_name,glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->m_camera->camera_pos),1)));

        uniform_name = bb->SpotLight_prefix + bb->Light_direction;
        go->m_shader->SetUniformVec3f(&uniform_name, glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->direction),0)));

        uniform_name = bb->SpotLight_prefix + bb->Light_CutOff;
        go->m_shader->SetUniform1f(&uniform_name, glm::cos(glm::radians(7.0)));
        uniform_name = bb->SpotLight_prefix + bb->Light_OutCutoff;
        go->m_shader->SetUniform1f(&uniform_name, glm::cos(glm::radians(12.0)));

        uniform_name = bb->SpotLight_prefix + bb->Light_constant;
        go->m_shader->SetUniform1f(&uniform_name,1.0);
        uniform_name = bb->SpotLight_prefix + bb->Light_linear;
        go->m_shader->SetUniform1f(&uniform_name,0.12);
        uniform_name = bb->SpotLight_prefix + bb->Light_quadratic;
        go->m_shader->SetUniform1f(&uniform_name,0.09);

        uniform_name = "hasSpotLight";

        go->m_shader->SetUniform1i(&uniform_name,1);

    }
}