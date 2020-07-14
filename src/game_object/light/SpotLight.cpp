#include "game_object/Light.hpp"

SpotLight::SpotLight(BasicsBlock* basic_block, Camera* m_camera, Model* model, float initial_pos[3],Shader* m_shader, float direction[3]):
                        Light(basic_block,m_camera,model,initial_pos,m_shader), direction(direction){
        cutoff = glm::cos(glm::radians(25.5f));
        outer_cutoff =glm::cos(glm::radians(30.5f));
}

SpotLight::SpotLight(BasicsBlock* basic_block, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader):
                        Light(basic_block,m_camera,model,initial_pos,m_shader), direction(this->light_pos){

}

SpotLight::SpotLight(BasicsBlock* basic_block, Camera* m_camera, float initial_pos[3], float direction[3]) : Light(basic_block,m_camera, initial_pos), direction(direction){

}

void SpotLight::LightBuffering(){
    int offset = 224;
    int flag = 1;
    glBindBuffer(GL_UNIFORM_BUFFER, basic_block->uniform_buffer_light);
    //Light position
    glBufferSubData(GL_UNIFORM_BUFFER,0+offset,16,glm::value_ptr(glm::vec3(basic_block->global_data.active_scene->scene_data.main_camera->GetView() * glm::vec4(glm::make_vec3(this->light_pos),1))));
    //Light direction
    glBufferSubData(GL_UNIFORM_BUFFER,16+offset,16, glm::value_ptr(glm::vec3(basic_block->global_data.active_scene->scene_data.main_camera->GetView() * glm::vec4(glm::make_vec3(this->direction),0))));
    //Light diffuse
    glBufferSubData(GL_UNIFORM_BUFFER,32+offset,16,glm::value_ptr(this->light_color * this->light_intensity));
    //Light Specular
    glBufferSubData(GL_UNIFORM_BUFFER,48+offset,16,glm::value_ptr(this->light_specular * this->light_intensity));
    //Light constant (why leap of only 12??? souldn't be 16)
    glBufferSubData(GL_UNIFORM_BUFFER,60+offset,4,&this->constant);
    //Light Linear
    glBufferSubData(GL_UNIFORM_BUFFER,64+offset,4,&this->linear);
    //Light quadratic
    glBufferSubData(GL_UNIFORM_BUFFER,68+offset,4,&this->quadratic);
    //Light cutoff
    glBufferSubData(GL_UNIFORM_BUFFER,72+offset,4,&this->cutoff);
    //Light outer cutoff
    glBufferSubData(GL_UNIFORM_BUFFER,76+offset,4,&this->outer_cutoff);
    //has spotlight
    glBufferSubData(GL_UNIFORM_BUFFER,304,4,&flag);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    

}