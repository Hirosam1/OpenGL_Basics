#include "game_object/GameObject.hpp"

 GameObject::GameObject(BasicsBlock* basic_block, Camera* m_camera,float initial_pos[3]): 
    m_input(basic_block->m_input),m_time(basic_block->m_time),m_window(basic_block->m_window), m_camera(m_camera){
   this->shader = nullptr;this->m_vao = nullptr;
   //this->MVP_string = new std::string("MVP");
   this->m_material = nullptr;
   model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
   this->SetInitialMVP();
   this->m_light = nullptr;

   this->Model_string = basic_block->Model_string;
   this->View_string = basic_block->View_string;
   this->Projection_string = basic_block->Projection_string;

   this->Mat_ambient = basic_block->Mat_ambient;
   this->Mat_diffuse = basic_block->Mat_diffuse;
   this->Mat_specular = basic_block->Mat_specular;
   this->Mat_shininess = basic_block->Mat_shininess;

   this->Light_ambient = basic_block->Light_ambient;
   this->Light_diffuse = basic_block->Light_diffuse;
   this->Light_specular = basic_block->Light_specular;
   this->Light_pos = basic_block->Light_pos;

   this->bb = basic_block;

}

GameObject::GameObject(BasicsBlock* basic_block, Camera* m_camera,Shape* m_shape,float initial_pos[3], 
std::string* vert_shader_path,std::string* frag_shader_path):
m_window(basic_block->m_window) ,m_input(basic_block->m_input),m_time(basic_block->m_time), m_camera(m_camera),
vertex_shader_path(vert_shader_path), fragment_shader_path(frag_shader_path),m_shape(m_shape){
   this->shader = nullptr; this->m_vao = nullptr;
   this->SetInitialMVP();
   model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
   this->m_light = nullptr;
   this->m_material = nullptr;
   
   this->Model_string = basic_block->Model_string;
   this->View_string = basic_block->View_string;
   this->Projection_string = basic_block->Projection_string;

   this->Mat_ambient = basic_block->Mat_ambient;
   this->Mat_diffuse = basic_block->Mat_diffuse;
   this->Mat_specular = basic_block->Mat_specular;
   this->Mat_shininess = basic_block->Mat_shininess;

   this->Light_ambient = basic_block->Light_ambient;
   this->Light_diffuse = basic_block->Light_diffuse;
   this->Light_specular = basic_block->Light_specular;
   this->Light_pos = basic_block->Light_pos;

   this->bb = basic_block;
    
}

//Updates the data and send it to GPU
 void GameObject::UpdateAndBuffer(){
    if(isLight){
       this->m_light->light_pos = glm::vec3(model[3][0],model[3][1],model[3][2]);
    }
    if(this->m_vao != nullptr && this->shader != nullptr && this->m_camera != nullptr){this->shader->UseShader();}
    //Updaets the vertex data
    this->Update();
    if(this->m_vao != nullptr && this->shader != nullptr && this->m_camera != nullptr){
      //Pass uniforms
      //Binds VAO
      this->m_vao->UseVAO();
      if(this->m_material != nullptr){
      //Applies color to the object
      this->shader->SetUniformVec3f(this->Mat_ambient,this->m_material->ambient_color);
      this->shader->SetUniformVec3f(this->Mat_diffuse,this->m_material->diffuse_color);
      this->shader->SetUniformVec3f(this->Mat_specular,this->m_material->specular_color);
      this->shader->SetUniform1f(this->Mat_shininess,this->m_material->shininess);
      }
      if(this->m_light != nullptr){
         shader->SetUniformVec3f(this->Light_ambient,this->m_light->light_ambient);
         shader->SetUniformVec3f(this->Light_diffuse,this->m_light->light_color * this->m_light->light_intensity);
         shader->SetUniformVec3f(this->Light_specular,this->m_light->light_specular);
         shader->SetUniformVec3f(this->Light_pos,this->m_light->light_pos);
      }
      this->shader->SetUniformMat4f(this->Model_string,this->model);
      this->shader->SetUniformMat4f(this->View_string,this->m_camera->GetView());
      this->shader->SetUniformMat4f(this->Projection_string,this->m_camera->GetProjection());
      if(this->m_shape->indices_count > 1){
         glDrawElements(GL_TRIANGLES,this->m_shape->indices_count,GL_UNSIGNED_INT,0);
      }else{
         glDrawArrays(GL_TRIANGLES,0,this->m_shape->vertex_count);
      }
    }
   glBindTexture(GL_TEXTURE_2D,0);
   glBindVertexArray(0);
   glUseProgram(0);
 }

 void GameObject::SetUpVertex(){
   if (this->m_shape != nullptr){
      //Creates the VAO object
      this->m_vao = new VAO(GL_FLOAT);
         //Sets how the atrtibutes should be read, ORDER MATTERS
         this->m_vao->SetAttribPoint(3);
         this->m_vao->SetAttribPoint(3);
      //Finishes the opbject
      this->m_vao->SetUpObject();
      //Buffer data into it
      this->m_vao->BufferData<GLfloat>(this->m_shape->vertex,GL_ARRAY_BUFFER,this->m_vao->vertex_type,this->m_shape->att_count);
      if(this->m_shape->indices_count > 1){
         this->m_vao->BufferData<GLuint>(this->m_shape->indices,GL_ELEMENT_ARRAY_BUFFER,GL_UNSIGNED_INT,this->m_shape->indices_count);
      }
   
      this->CreateShaderObject(this->vertex_shader_path,this->fragment_shader_path);
   }
 }

 void GameObject::SetUpVertex(VAO* aVAO){
   this->m_vao = aVAO;
   this->m_vao->UseVAO();
   this->m_vao->BufferData<GLfloat>(this->m_shape->vertex,GL_ARRAY_BUFFER,this->m_vao->vertex_type,this->m_shape->att_count);
   if(this->m_shape->indices_count > 1){
      this->m_vao->BufferData<GLuint>(this->m_shape->indices,GL_ELEMENT_ARRAY_BUFFER,GL_UNSIGNED_INT,this->m_shape->indices_count);
   }
   this->CreateShaderObject(this->vertex_shader_path,this->fragment_shader_path);
 }

 void GameObject::CreateShaderObject(std::string* vertex_shader, std::string* fragment_shader){
   this->shader = new Shader();
   this->shader->LoadShader(vertex_shader,GL_VERTEX_SHADER);
   this->shader->LoadShader(fragment_shader,GL_FRAGMENT_SHADER);
   this->shader->LinkShaders();
    
 }

void GameObject::AddTexture(std::string* tex_path, GLenum type, std::string* uniform_name){
   if(this->shader != nullptr){
      uniform_name = uniform_name != nullptr ? uniform_name : bb->Basic_tex;
      this->shader->AddTexture(tex_path,uniform_name,type);
   }
}

void GameObject::AddTexture(Texture* texture, std::string* uniform_name){
   if(this->shader != nullptr){
      uniform_name = uniform_name != nullptr ? uniform_name : bb->Basic_tex;
      this->shader->AddTexture(texture, uniform_name);
   }
}

 void GameObject::SetInitialMVP(){
   //This is the world space matrix
   this->model = glm::mat4(1.0f);
 }

void GameObject::MakeLight(){
   if(this->m_light){
      isLight = true;
   }
}

void GameObject::GiveLight(Light* light){
    this->m_light = light;
 }


void GameObject::ReadyObject(){
   this->Ready();
}

 void GameObject::Ready(){
 }