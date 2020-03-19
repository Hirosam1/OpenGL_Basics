#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "graphics/Texture.hpp"
#include "game_object/VAO.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Material.hpp"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh{
    public:
        /* Mesh Data */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        /* Methods */
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material m_material, bool has_texDiff = false, bool has_texSpec = false);
        //Draw object using given shader
        void Draw(Shader* shader);
        //Draw object not using any shader you have to set ip up yourself
        void Draw();
        Material m_material;
        bool has_texDiff;
        bool has_texSpec;
        //void SetUpVertex(VAO* mVao);
    private:
        /* Render  data */
        VAO* vao;
        /* Methods*/
        void SetUpMesh();

        unsigned int mVAO, mVBO, mEBO;
};

