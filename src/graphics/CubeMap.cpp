#include "graphics/CubeMap.hpp"

CubeMap::CubeMap(std::string path_to_cubemap_folder, Model* m_model, Shader* m_shader): cube_map_path(path_to_cubemap_folder) , m_model(m_model), m_shader(m_shader){
    this->LoadTextures();
}

void CubeMap::LoadTextures(){
    for(int i = 0; i < this->faces.size() ; i++){
        faces[i] = cube_map_path + "/" + faces[i];
    }
    this->cube_map_texture = new CubeMapTexture(faces);
}

void CubeMap::UseCubeTexture(Shader* a_shader,Camera* a_camera){
    if(a_shader != nullptr){
        a_shader->UseShader();
        std::string name;
        a_shader->UseShader();
        name = "view";
        a_shader->SetUniformMat4f(&name,glm::mat4(glm::mat3(a_camera->GetView())));
        name  = "projection";
        a_shader->SetUniformMat4f(&name,a_camera->GetProjection());
        name = "skybox";
        a_shader->SetUniform1i(&name,0);
        cube_map_texture->UseTexture();
        m_model->Draw();
    }
}