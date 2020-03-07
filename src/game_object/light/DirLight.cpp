#include "game_object/Light.hpp"

DirLight::DirLight(BasicsBlock* bb, Camera* m_camera,Mesh* shape,float initial_pos[3], std::string* vert, std::string* frag, float direction[3]): 
                    Light(bb,m_camera,shape,initial_pos,vert,frag), direction(direction){
}

DirLight::DirLight(BasicsBlock* bb, Camera* m_camera,Mesh* shape,float initial_pos[3], std::string* vert, std::string* frag): 
                    Light(bb,m_camera,shape,initial_pos,vert,frag), direction(this->light_pos){
                    
}

void DirLight::LightBuffering(GameObject* go){
    if(go->m_shader != nullptr){
        go->m_shader->UseShader();
        std::string uniform_name = bb->DirLight_prefix + bb->Light_ambient;
        go->m_shader->SetUniformVec3f(&uniform_name,this->light_ambient);
        uniform_name = bb->DirLight_prefix + bb->Light_diffuse;
        go->m_shader->SetUniformVec3f(&uniform_name,this->light_color * this->light_intensity);
        uniform_name = bb->DirLight_prefix + bb->Light_specular;
        go->m_shader->SetUniformVec3f(&uniform_name,this->light_specular * this->light_intensity);
        uniform_name = bb->DirLight_prefix + bb->Light_pos;
        go->m_shader->SetUniformVec3f(&uniform_name,glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->light_pos),1)));

        uniform_name = bb->DirLight_prefix + bb->Light_direction;
        go->m_shader->SetUniformVec3f(&uniform_name, glm::vec3(go->m_camera->GetView() * glm::vec4(glm::make_vec3(this->direction),0)));
    }
}