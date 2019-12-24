#include "game_object/Light.hpp"

Light::Light(float light_intensity, glm::vec3 light_color, glm::vec3 light_pos):light_pos(light_pos), light_intensity(light_intensity),light_color(light_color),
light_ambient(light_color* 0.15f), light_specular(glm::vec3(1.0)){

}