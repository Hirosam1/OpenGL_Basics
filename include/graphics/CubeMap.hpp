#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "graphics/Texture.hpp"
#include "graphics/Shader.hpp"
#include "game_object/Model.hpp"
#include "game_object/Camera.hpp"

class CubeMap {
    public:
        CubeMap(std::string path_to_cubemap_folder, Model* m_model);
        CubeMap(std::string path_to_cubemap_folder, Model* m_model, Shader* m_shader);
        std::string cube_map_path = "textures/skybox/";
        std::vector<std::string> faces
        {
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
        };
        CubeMapTexture* cube_map_texture;
        Shader* m_shader = nullptr;
        Model* m_model;
        void UseCubeTexture(Shader* a_shader, Camera* a_camera);
    private:
        void LoadTextures();
};