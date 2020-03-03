#pragma once
#include <iostream>
#include <vector>

#include "graphics/Shader.hpp"
#include "game_object/Mesh.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model{
    public:
        Model(std::string path){
            LoadModel(path);
        }
        void Draw(Shader* shader);

        std::vector<Texture> textures_loaded;
    private:
        /*Model data*/
        std::vector<Mesh> meshes;
        std::string directory;
        /*Functions*/
        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
};