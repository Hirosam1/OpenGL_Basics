#include "game_object/Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures): vertices(vertices), indices(indices), textures(textures){
    this->SetUpMesh();
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
    for(unsigned int i = 0; i < textures.size() ; i++){
        glActiveTexture(GL_TEXTURE0+i);
        std::string number;
        std::string name = textures[i].tex_type;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++);
        name = ("material." + name + number);
        shader->SetUniform1f(&name,i);
        textures[i].UseTexture(0,false);
    }
    vao->UseVAO();
    glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}