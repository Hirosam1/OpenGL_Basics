#include "personal_objects/PulsingLight.hpp"

PulsingLight::PulsingLight(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader) : GameObject(basic_block,m_camera,model,initial_pos,m_shader){

}

void PulsingLight::Ready(){
    pointLight = nullptr;
    for(int i = 0; i < bb->all_objs->size(); i++){
        if(PointLight* light = dynamic_cast<PointLight*>(bb->all_objs->at(i))){
            pointLight = light;
            break;
        }
    }
}

void PulsingLight::Update(){
    if(pointLight != nullptr){
        float intensity = (sin(m_time->GetTime())+1)/2.0;
        pointLight->light_intensity = intensity;

        float x,y,z;
        x = sin(m_time->GetTime()*1)*3;
        y = sin(m_time->GetTime()*2)*1.3;
        z = cos(m_time->GetTime()*1)*3;


        x += this->model_mat[3][0];
        y += this->model_mat[3][1];
        z += this->model_mat[3][2];

        pointLight->light_pos[0] = x;
        pointLight->light_pos[1] = y;
        pointLight->light_pos[2] = z;
    }

}