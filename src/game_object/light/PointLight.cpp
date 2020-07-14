#include "game_object/Light.hpp"

PointLight::PointLight(BasicsBlock* basic_block, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader, float direction[3]):Light(basic_block,m_camera,model,initial_pos,m_shader),
        constant(1.0f),linear(0.12f),quadratic(0.04f){

}
PointLight::PointLight(BasicsBlock* basic_block, Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader , int index,float linear, float quadratic, float constant) : 
Light(basic_block,m_camera,model,initial_pos,m_shader), constant(constant),linear(linear),quadratic(quadratic),index(index){

}

void PointLight::LightBuffering(){
    glBindBuffer(GL_UNIFORM_BUFFER,basic_block->uniform_buffer_light);
    //Light direction
    glBufferSubData(GL_UNIFORM_BUFFER,0+(index*80),16,glm::value_ptr(glm::vec3(basic_block->global_data.active_scene->scene_data.main_camera->GetView() * glm::vec4(glm::make_vec3(this->light_pos),1))));
    //Light ambient
    glBufferSubData(GL_UNIFORM_BUFFER,16+(index*80),16,glm::value_ptr(this->light_ambient));
    //Light diffuse
    glBufferSubData(GL_UNIFORM_BUFFER,32+(index*80),16,glm::value_ptr(this->light_color * this->light_intensity));
    //Light specular
    glBufferSubData(GL_UNIFORM_BUFFER,48+(index*80),16,glm::value_ptr(this->light_specular * this->light_intensity));
    //Light constant
    glBufferSubData(GL_UNIFORM_BUFFER,64+(index*80),4,&this->constant);
    //Light linear
    glBufferSubData(GL_UNIFORM_BUFFER,68+(index*80),4,&this->linear);
    //Linear quadractic
    glBufferSubData(GL_UNIFORM_BUFFER,72+(index*80),4,&this->quadratic);
    //number of point lights (why it is 308??)
    //glBufferSubData(GL_UNIFORM_BUFFER,308,4,&basic_block->global_data.active_scene->scene_data.n_point_lights);
    glBindBuffer(GL_UNIFORM_BUFFER,0);
}