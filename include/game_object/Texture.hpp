#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game_tools/stb_image.h"
#include "game_object/Shader.hpp"

class Texture{
    public:
        Texture(Shader* m_shader, std::string texture_path);
        void CreateTexture(std::string texture_name);
        void UseTexture();
        
    private:
        unsigned int m_texture;
        Shader* m_shader;

};