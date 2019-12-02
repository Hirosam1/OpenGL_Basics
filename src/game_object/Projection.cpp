#include "game_object/Projection.hpp"

Projection::Projection(float fov, float aspect_ratio,float close, float far){
    this->projection = glm::perspective(fov,aspect_ratio,close,far);
}

void Projection::MakePerspective(float fov, float aspect_ratio,float close, float far){
    this->projection = glm::perspective(fov,aspect_ratio,close,far);
}

glm::mat4 Projection::GetProjection(){
    return this->projection;
}