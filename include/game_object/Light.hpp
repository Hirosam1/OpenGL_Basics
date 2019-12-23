#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light{
    public:
        Light(float light_intensity = 0.5f, glm::vec3 light_color = glm::vec3(1,1,1) , glm::vec3 light_pos = glm::vec3(0,0,0));
        glm::vec3 light_pos;
        float light_intensity;
        glm::vec3 light_color;
        glm::vec3 light_ambient;
        glm::vec3 light_specular;
};