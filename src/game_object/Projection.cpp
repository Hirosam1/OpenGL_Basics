#include "game_object/Projection.hpp"

Projection::Projection(float fov, float aspect_ratio,float close, float far){
    this->projection = glm::perspective(fov,aspect_ratio,close,far);
    close_plane = close;
    far_plane = far;
}

void Projection::MakePerspective(float fov, float aspect_ratio,float close, float far){
    this->projection = glm::perspective(fov,aspect_ratio,close,far);
    close_plane = close;
    far_plane = far;
}

glm::mat4 Projection::GetProjection(){
    return this->projection;
}