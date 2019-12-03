#include "game_object/GameObject.hpp"

 GameObject::GameObject(BasicsBlock* basic_block, Camera* m_camera,float initial_pos[3]): 
    m_input(basic_block->m_input),m_time(basic_block->m_time),m_window(basic_block->m_window), m_camera(m_camera){

   this->shader = nullptr;this->m_vao = nullptr;
   //this->MVP_string = new std::string("MVP");
   model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
   this->SetInitialMVP();

}



GameObject::GameObject(BasicsBlock* basic_block, Camera* m_camera,Shape* m_shape,float initial_pos[3], 
std::string* vert_shader_path,std::string* frag_shader_path):
m_window(basic_block->m_window) ,m_input(basic_block->m_input),m_time(basic_block->m_time), m_camera(m_camera),
vertex_shader_path(vert_shader_path), fragment_shader_path(frag_shader_path),m_shape(m_shape){
   this->shader = nullptr; this->m_vao = nullptr;
   this->SetInitialMVP();
   
   model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
   this->MVP_string = new std::string("MVP");
    
}

//Updates the data and send it to GPU
 void GameObject::UpdateAndBuffer(){
    //Updaets the vertex data
    this->Update();
    if(this->m_vao != nullptr && this->shader != nullptr && this->m_camera != nullptr){
         
         //Binds VAO
         this->m_vao->UseVAO();
         this->shader->UseShader();
        //Pass position parameters to shader
        this->shader->SetUniformMat4fv(this->MVP_string,this->m_camera->GetProjection() *this->m_camera->GetView()*model);
        //Draws the cube
        glDrawElements(GL_TRIANGLES,this->m_shape->indices_count,GL_UNSIGNED_INT,0);
    }

 }

 void GameObject::SetUpVertex(){
   if (this->m_shape != nullptr){
      //Creates the VAO object
      this->m_vao = new VAO();
         //Sets how the atrtibutes should be read, ORDER MATTERS
         this->m_vao->SetAttribPoint(3,GL_FLOAT,GL_ARRAY_BUFFER);
         this->m_vao->SetAttribPoint(3,GL_FLOAT,GL_ARRAY_BUFFER);
         this->m_vao->SetAttribPoint(2,GL_FLOAT,GL_ARRAY_BUFFER);
      //Finishes the opbject
      this->m_vao->SetUpObject();
      //Buffer data into it
      this->m_vao->BufferData<GLfloat>(this->m_shape->vertex,GL_ARRAY_BUFFER,GL_FLOAT,this->m_shape->vertex_count);
      this->m_vao->BufferData<GLuint>(this->m_shape->indices,GL_ELEMENT_ARRAY_BUFFER,GL_FLOAT,this->m_shape->indices_count);
   
      this->CreateShaderObject(this->vertex_shader_path,this->fragment_shader_path);
   }
 }

 void GameObject::SetUpVertex(VAO* aVAO){
    this->m_vao = aVAO;
 }

 void GameObject::CreateShaderObject(std::string* vertex_shader, std::string* fragment_shader){
   this->shader = new Shader();
   this->shader->LoadShader(vertex_shader,GL_VERTEX_SHADER);
   this->shader->LoadShader(fragment_shader,GL_FRAGMENT_SHADER);
   this->shader->LinkShaders();
    
 }

void GameObject::SetTexture(std::string* tex_path){
   if(this->shader != nullptr){
      this->shader->SetTexture(tex_path);
   }
}

 void GameObject::SetInitialMVP(){
   //This is the world space matrix
   this->model = glm::mat4(1.0f); //model = glm::rotate(model,glm::radians(-10.0f),glm::vec3(1.0f,0.0f,0.0));
 }