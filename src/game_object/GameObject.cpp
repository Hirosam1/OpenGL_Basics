#include "game_object/GameObject.hpp"

GameObject::GameObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader):
                        m_window(basic_block->m_window) ,m_input(basic_block->m_input), m_camera(m_camera),
                        m_model(model),m_shader(m_shader),initial_pos(initial_pos){
   this->SetInitialMVP();
   model_mat = glm::translate(model_mat,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
   this->m_material = nullptr;
   this->basic_block = basic_block;
}

GameObject::~GameObject(){
   delete initial_pos;
}

//Updates the data and send it to GPU
 void GameObject::BufferAndDraw(){
   if(this->m_shader != nullptr && m_model != nullptr){
      if(isSelected){
         glEnable(GL_STENCIL_TEST);
         glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
         glStencilFunc(GL_ALWAYS,1,0xff);
         glStencilMask(0xff);
      }
      
      this->m_shader->BufferShader(model_mat);
      if(this->instancing_info.IsInstanced()){
         this->m_model->InstancedDraw(this->m_shader,this->instancing_info);
      }
      else{
         this->m_model->Draw(this->m_shader);
      }

      if(isSelected){
         glStencilFunc(GL_NOTEQUAL,1,0xff); //Set rule for each pixel that wasnt draw
         glStencilMask(0x00);//Disable stencil write
         basic_block->outline_shader.UseShader();
         basic_block->outline_shader.BufferShader(glm::scale(this->model_mat,glm::vec3(1.03)));
         this->m_model->Draw(this->m_shader);
         isSelected = false;
         glStencilMask(0xFF);
         glStencilFunc(GL_ALWAYS, 1, 0xFF);//Clear stencil
         glDisable(GL_STENCIL_TEST);

      }

      glBindTexture(GL_TEXTURE_2D,0);
      glBindVertexArray(0);  
   }
 }

 void GameObject::UseShader(){
    this->m_shader->UseShader();
 }

 void GameObject::SetInitialMVP(){
   //This is the world space matrix
   this->model_mat = glm::mat4(1.0f);
 }

void GameObject::ReadyObject(){
   this->Ready();
}

 void GameObject::Ready(){
 }

 void GameObject::MakeInstaced(float* data,unsigned int amount,float elements_per_vertex,unsigned int vertex_indice ){
    if(this->m_model != nullptr){
      glGenBuffers(1,&instancing_info.instace_vbo);
      glBindBuffer(GL_ARRAY_BUFFER, instancing_info.instace_vbo);
      glBufferData(GL_ARRAY_BUFFER,sizeof(float) * amount * elements_per_vertex, data,GL_STATIC_DRAW);
      
      this->instancing_info.amount = amount;
      this->instancing_info.vertex_index = vertex_indice;
      this->instancing_info.element_per_vertex = elements_per_vertex;
      this->instancing_info.game_object = this;
    }

 }