#include "game_object/Projection.hpp"

Projection::Projection(float fov, float aspect_ratio,float close, float far){
    this->projection = glm::perspective(glm::radians(45.0f),aspect_ratio,0.1f,100.0f);
}

void Projection::MakePerspective(float fov, float aspect_ratio,float close, float far){
   this->projection = glm::perspective(glm::radians(45.0f),aspect_ratio,0.1f,100.0f);
}

glm::mat4 Projection::GetProjection(){
    return this->projection;
}