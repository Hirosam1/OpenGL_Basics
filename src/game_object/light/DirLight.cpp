#include "game_object/Light.hpp"

DirLight::DirLight(BasicsBlock* basic_block, Camera* m_camera,Model* model,float initial_pos[3], Shader* m_shader, float direction[3]): 
                    Light(basic_block,m_camera,model,initial_pos,m_shader), direction(direction){

    this->light_ambient = this->light_color * 0.05f;
}

DirLight::DirLight(BasicsBlock* basic_block, Camera* m_camera,Model* model,float direction[3], Shader* m_shader): 
                    Light(basic_block,m_camera,model,direction,m_shader), direction(this->light_pos){
     this->light_ambient = this->light_color * 0.05f;
}

DirLight::DirLight(BasicsBlock* basic_block, Camera* m_camera, float direction[3]) : Light(basic_block,m_camera,direction), direction(this->light_pos){
     this->light_ambient = this->light_color * 0.05f;
}

void DirLight::LightBuffering(){
    glBindBuffer(GL_UNIFORM_BUFFER,basic_block->uniform_buffer_light);
    basic_block->global_data.active_scene->scene_data.main_camera->GetView();
    //Sets light direction
    glBufferSubData(GL_UNIFORM_BUFFER,160+0,16,glm::value_ptr(glm::vec3(basic_block->global_data.active_scene->scene_data.main_camera->GetView() * glm::vec4(glm::make_vec3(this->direction),0))));
    //Sets light ambient
    glBufferSubData(GL_UNIFORM_BUFFER,160+16,16,glm::value_ptr(this->light_ambient));
    //Sets light Diffuse
    glBufferSubData(GL_UNIFORM_BUFFER,160+32,16,glm::value_ptr(this->light_color * this->light_intensity));
    //Sets light specular
    glBufferSubData(GL_UNIFORM_BUFFER,160+48,16,glm::value_ptr(this->light_specular * this->light_intensity));
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}