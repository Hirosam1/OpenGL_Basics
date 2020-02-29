#include "game_object/Light.hpp"

SpotLight::SpotLight(BasicsBlock* bb, Camera* m_camera, Shape* shape, float initial_pos[3], std::string* vert, std::string* frag, float direction[3]):
                        Light(bb,m_camera,shape,initial_pos,vert,frag), direction(direction){

}

SpotLight::SpotLight(BasicsBlock* bb, Camera* m_camera, Shape* shape, float initial_pos[3], std::string* vert, std::string* frag):
                        Light(bb,m_camera,shape,initial_pos,vert,frag), direction(this->light_pos){

}

SpotLight::SpotLight(BasicsBlock* bb, Camera* m_camera, float initial_pos[3], float direction[3]) : Light(bb,m_camera, initial_pos), direction(direction){

}

void SpotLight::LightBuffering(GameObject* go){
    if(go->shader != nullptr){
        go->shader->UseShader();
        std::string uniform_name = bb->SpotLight_prefix + bb->Light_ambient;
        go->shader->SetUniformVec3f(&uniform_name,this->light_ambient);
        uniform_name = bb->SpotLight_prefix + bb->Light_diffuse;
        go->shader->SetUniformVec3f(&uniform_name,this->light_color * this->light_intensity);
        uniform_name = bb->SpotLight_prefix + bb->Light_specular;
        go->shader->SetUniformVec3f(&uniform_name,this->light_specular * this->light_intensity);
        uniform_name = bb->SpotLight_prefix + bb->Light_pos;
        go->shader->SetUniformVec3f(&uniform_name,glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->m_camera->camera_pos),1)));

        uniform_name = bb->SpotLight_prefix + bb->Light_direction;
        go->shader->SetUniformVec3f(&uniform_name, glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->direction),0)));

        uniform_name = bb->SpotLight_prefix + bb->Light_CutOff;
        go->shader->SetUniform1f(&uniform_name, glm::cos(glm::radians(7.0)));
        uniform_name = bb->SpotLight_prefix + bb->Light_OutCutoff;
        go->shader->SetUniform1f(&uniform_name, glm::cos(glm::radians(12.0)));

        uniform_name = bb->SpotLight_prefix + bb->Light_constant;
        go->shader->SetUniform1f(&uniform_name,1.0);
        uniform_name = bb->SpotLight_prefix + bb->Light_linear;
        go->shader->SetUniform1f(&uniform_name,0.12);
        uniform_name = bb->SpotLight_prefix + bb->Light_quadratic;
        go->shader->SetUniform1f(&uniform_name,0.09);

        uniform_name = "hasSpotLight";

        go->shader->SetUniform1i(&uniform_name,1);

    }
}