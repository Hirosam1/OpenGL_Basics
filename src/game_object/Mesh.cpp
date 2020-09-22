#include "game_object/Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures, Material m_material, bool has_texDiff, bool has_texSpec): 
    vertices(vertices), indices(indices), textures(textures), m_material(m_material), has_texDiff(has_texDiff), has_texSpec(has_texSpec){
    this->SetUpMesh();
}

void Mesh::UnloadMeshData(){
    this->vao->UnloadVAO();
}

void Mesh::SetUpMesh(){
    vao = new VAO();
    glBindVertexArray(vao->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,vao->m_VBO);

    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(Vertex), &vertices[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vao->m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //Vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)0);
    //Vertex normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,Normal));
    //Vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader* shader){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    std::string name;

    for(unsigned int i = 0; i < textures.size() ; i++){
        textures[i]->UseTexture(i, shader);
        
    }
    /*name = "material.diffuse";
    shader->SetUniformVec3f(&name, m_material.main_color);
    name = "material.ambient";
    shader->SetUniformVec3f(&name, m_material.ambient_color);*/
    shader->BufferShader(&m_material);
    vao->UseVAO();
    glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
}

void Mesh::Draw(){
    vao->UseVAO();
    glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0); 
}