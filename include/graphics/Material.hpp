#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Material{
    public:
    Material(glm::vec3 main_color);
    int use_main_color = 1;
    glm::vec3 main_color;
    glm::vec3 ambient_color;
    glm::vec3 diffuse_color;
    glm::vec3 specular_color;
    float shininess;
    private:
    
};