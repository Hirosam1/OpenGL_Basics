#include "game_object/GameObject.hpp"

GameObject::GameObject(BasicsBlock* basic_block, Camera* m_camera, Mesh* m_mesh,float initial_pos[3], 
std::string* vert_shader_path,std::string* frag_shader_path):
m_window(basic_block->m_window) ,m_input(basic_block->m_input),m_time(basic_block->m_time), m_camera(m_camera),
m_mesh(m_mesh) ,vertex_shader_path(vert_shader_path), fragment_shader_path(frag_shader_path){
   this->m_shader = nullptr; this->m_vao = nullptr;
   this->SetInitialMVP();
   model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
   this->m_material = nullptr;
   this->bb = basic_block;
    
}

GameObject::GameObject(BasicsBlock* basic_block, Camera* m_camera,float initial_pos[3]): 
                        m_window(basic_block->m_window) ,m_input(basic_block->m_input),
                        m_time(basic_block->m_time), m_camera(m_camera),bb(basic_block){
   m_mesh = nullptr;
   this->m_shader = nullptr; this->m_vao = nullptr; this->m_material = nullptr; m_mesh = nullptr;
   this->SetInitialMVP();
   model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));

}

//Updates the data and send it to GPU
 void GameObject::UpdateAndBuffer(){

      m_mesh->Draw(this->m_shader);

      glBindTexture(GL_TEXTURE_2D,0);
      glBindVertexArray(0);
      glUseProgram(0);

 }

 void GameObject::CreateShaderObject(std::string* vertex_shader, std::string* fragment_shader){
   this->m_shader = new Shader();
   this->m_shader->LoadShader(vertex_shader,GL_VERTEX_SHADER);
   this->m_shader->LoadShader(fragment_shader,GL_FRAGMENT_SHADER);
   this->m_shader->LinkShaders();
    
 }

void GameObject::AddTexture(std::string* tex_path, GLenum type, std::string* uniform_name){
   if(this->m_shader != nullptr){
      uniform_name = uniform_name != nullptr ? uniform_name : &bb->Basic_tex;
      /*this->shader->AddTexture(tex_path,uniform_name,type);*/
   }
}

void GameObject::AddTexture(Texture* texture, std::string* uniform_name){
   if(this->m_shader != nullptr){
      uniform_name = uniform_name != nullptr ? uniform_name : &bb->Basic_tex;
      /*this->shader->AddTexture(texture, uniform_name);*/
   }
}

 void GameObject::SetInitialMVP(){
   //This is the world space matrix
   this->model = glm::mat4(1.0f);
 }

void GameObject::ReadyObject(){
   this->Ready();
}

 void GameObject::Ready(){
 }