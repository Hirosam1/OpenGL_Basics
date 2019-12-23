#include "graphics/Material.hpp"

Material::Material(glm::vec3 main_color):main_color(main_color), ambient_color(main_color), diffuse_color(main_color), 
specular_color(glm::vec3(0.2,0.2,0.2)), shininess(8.0f){
    
}