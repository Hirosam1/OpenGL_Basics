#pragma once
#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "graphics/Texture.hpp"
#include "game_object/VAO.hpp"
#include "graphics/Shader.hpp"

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
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader* shader);

        //void SetUpVertex(VAO* mVao);
    private:
        /* Render  data */
        //unsigned int VAO, VBO, EBO;
        VAO* vao;
        /* Methods*/
        void SetUpMesh();
};

