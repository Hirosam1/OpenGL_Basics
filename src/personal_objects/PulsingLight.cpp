#include "personal_objects/PulsingLight.hpp"

PulsingLight::PulsingLight(BasicsBlock* bb, Camera* m_camera, float initial_pos[3]) : GameObject(bb,m_camera,initial_pos){

}

void PulsingLight::Ready(){
    for(int i = 0; i < bb->all_objs->size(); i++){
        if(PointLight* light = dynamic_cast<PointLight*>(bb->all_objs->at(i))){
            pointLight = light;
            break;
        }
    }
}

void PulsingLight::Update(){
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