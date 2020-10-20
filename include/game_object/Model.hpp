#pragma once
#include <iostream>
#include <vector>

#include "graphics/Shader.hpp"
#include "game_object/Mesh.hpp"
#include "graphics/Material.hpp"
#include "game_object/InstacingInformation.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

class Model{
    public:
        Model(std::string path, bool use_texture = true,bool texture_repeat = true):repeat(texture_repeat), use_texture(use_texture){
            LoadModel(path);
        }
        ~Model();
        //Draw Model
        void Draw(Shader* shader);
        void Draw();
        //Draw the Model instanced by the maount
        void InstancedDraw(unsigned int amount);
        void InstancedDraw(Shader* shder, InstacingInformation inst_info);
        bool repeat;
        bool use_texture;
        std::vector<Texture*> textures_loaded;
        std::vector<Mesh> meshes;
        aiScene m_scene;
    private:
        /*Model data*/
        //std::vector<Mesh> meshes;
        std::string directory;
        /*Functions*/
        void LoadModel(std::string path);
        void ProcessNode(aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
        std::vector<Texture*> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
        Material LoadMaterial(aiMaterial* mat);
};