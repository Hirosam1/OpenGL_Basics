#include "game_object/Model.hpp"

void Model::Draw(Shader* shader){   
    for(unsigned int i = 0; i < meshes.size() ; i++){
        meshes[i].Draw(shader);
    }
}

void Model::Draw(){
    for(unsigned int i = 0; i < meshes.size() ; i++){
        meshes[i].Draw();
    }
}

void Model::InstancedDraw(unsigned int amount){
}

void Model::TestThing(InstacingInformation inst_info, float* data){
    for(unsigned int i = 0; i < meshes.size() ; i++){
        meshes[i].TestThing(inst_info,data);
    }
}

void Model::InstancedDraw(Shader* shader,InstacingInformation inst_info){     
    for(unsigned int i = 0; i < meshes.size() ; i++){
        meshes[i].InstacedDraw(shader,inst_info);
    }
}

Model::~Model(){
    for(unsigned int i = 0 ; i < this->textures_loaded.size(); i++){
        if(this->textures_loaded[i] != nullptr){
            this->textures_loaded[i]->UnloadTexture();
            delete this->textures_loaded[i];
        }
    }
    for(unsigned int i = 0; i < this->meshes.size(); i++){
        this->meshes[i].UnloadMeshData();
    }

    this->textures_loaded.clear();
    this->meshes.clear();
}

void Model::LoadModel(std::string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path,aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<<"ERROR::ASSIMP::" << import.GetErrorString() << "\n";
        return;
    }
    std::cout<<"Loading model -> " << path <<"\n";
    directory = path.substr(0, path.find_last_of("/"));
    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene){
    //Process all nodes's meshes
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh,scene));
    }
    //Then repeat for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        //Process vertices positions, normals and texture coordinates
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if(mesh->mTextureCoords[0]){
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else{
            vertex.TexCoords = glm::vec2(0.0,0.0);
        }

        vertices.push_back(vertex);
    }

    //Process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    //process naterial
    Material m_material;
    bool has_texDiff = false;
    bool has_texSpec = false;
    if(use_texture && mesh->mMaterialIndex >= 0){
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture*> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        if(diffuseMaps.size() > 0){
            has_texDiff = true;
        }
        textures.insert(textures.end(),diffuseMaps.begin(),diffuseMaps.end());

        std::vector<Texture*> specularMaps = LoadMaterialTextures(material,aiTextureType_SPECULAR, "texture_specular");
        if(specularMaps.size() > 0){
            has_texSpec = true;
        }
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        m_material = LoadMaterial(material);
    }
    return Mesh(vertices,indices,textures, m_material,has_texDiff,has_texSpec);

}

std::vector<Texture*> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name){
    std::vector<Texture*> textures;

    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type,i,&str);
        bool skip = false;
        //Checks if texture was already loaded
        for(unsigned int j = 0; j < textures_loaded.size(); j++){
            if(std::strcmp(textures_loaded[j]->path.data(), str.C_Str())== 0){
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        //If it wasn't loads it 
        if(!skip){
            Texture* new_texture = nullptr;
            if(type_name == "texture_diffuse"){
                 new_texture = new DiffuseTexture(directory + "/" + std::string(str.C_Str()),repeat);
            }else if(type_name == "texture_specular"){
                new_texture = new SpecularTexture(directory + "/" + std::string(str.C_Str()),repeat);
            }
            new_texture->tex_type = type_name;
            new_texture->path = str.C_Str();
            textures.push_back(new_texture);
            textures_loaded.push_back(new_texture); // Add the loaded texture to textures_loaded
            
        }
    }

    return textures;
}


Material Model::LoadMaterial(aiMaterial* mat){
    
    aiColor4D color (0,0,0,1);
    aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color);
    Material m_material = Material(glm::vec3(color.r,color.g,color.b));
    color = aiColor4D(0,0,0,1);
    aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color);
    m_material.specular_color = glm::vec3(color.r,color.g,color.b);
    return m_material;
}