#include "game_object/GameObject.hpp"
 GameObject::GameObject(Window* aWindow,InputManager* m_input, Time* m_time): 
    m_input(m_input),m_time(m_time),m_window(aWindow){
    this->vertex = new float[32]{
            // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    this->indices = new unsigned int[6]{
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    this->vertex_count = 32;  this->indices_count = 6;

    this->width = this->m_window->GetWidth();
    this->height = this->m_window->GetHeight();
    //This is the world space matrix
    model = glm::mat4(1.0f); model = glm::rotate(model,glm::radians(-10.0f),glm::vec3(1.0f,0.0f,0.0));
    //How our comera is positioned in the world, it is inverted. If we want to move the camera backward, we move the whole scene forward
    view = glm::mat4(1.0f); view = glm::translate(view,glm::vec3(0.0f,2.0f,-5.0f));
    //The prjection matrix
    projection = glm::mat4(1.0f); projection = glm::perspective(glm::radians(45.0f),(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.1f,100.0f);

}
GameObject::GameObject(Window* aWindow,InputManager* m_input, Time* m_time, float* vertex, unsigned int vertex_count,unsigned int* indices, unsigned int indices_count):
m_input(m_input),m_time(m_time),vertex(vertex),indices(indices),vertex_count(vertex_count),indices_count(indices_count),m_window(aWindow){


    this->width = this->m_window->GetWidth();
    this->height = this->m_window->GetHeight();
   //This is the world space matrix
    model = glm::mat4(1.0f); model = glm::rotate(model,glm::radians(-10.0f),glm::vec3(1.0f,0.0f,0.0));
    //How our comera is positioned in the world, it is inverted. If we want to move the camera backward, we move the whole scene forward
    view = glm::mat4(1.0f); view = glm::translate(view,glm::vec3(0.0f,2.0f,-5.0f));
    //The prjection matrix
    projection = glm::mat4(1.0f); projection = glm::perspective(glm::radians(45.0f),(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.1f,100.0f);
    
}


GameObject::GameObject(Window* aWindow,InputManager* m_input, Time* m_time, 
float* vertex, unsigned int vertex_count,unsigned int* indices, unsigned int indices_count, float initial_pos[3]):
m_input(m_input),m_time(m_time),vertex(vertex),indices(indices),vertex_count(vertex_count),indices_count(indices_count),m_window(aWindow){


    this->width = this->m_window->GetWidth();
    this->height = this->m_window->GetHeight();
   //This is the world space matrix
    model = glm::mat4(1.0f); model = glm::rotate(model,glm::radians(-10.0f),glm::vec3(1.0f,0.0f,0.0));
    model = glm::translate(model,glm::vec3(initial_pos[0],initial_pos[1],initial_pos[2]));
    //How our comera is positioned in the world, it is inverted. If we want to move the camera backward, we move the whole scene forward
    view = glm::mat4(1.0f); view = glm::translate(view,glm::vec3(0.0f,2.0f,-5.0f));
    //The prjection matrix
    projection = glm::mat4(1.0f); projection = glm::perspective(glm::radians(45.0f),(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.1f,100.0f);
    

}

//Updates the data and send it to GPU
 void GameObject::UpdateAndBuffer(){
        ///Updaets the vertex data
        this->Update();

        //Tells OpenGl how to intepret the data(?????)
        glBindVertexArray(this->VAO);
        

        //Pass position parameters to shader
        this->shader->SetUniformMat4fv("MVP",projection*view*model);

        this->shader->UseShader();

        //Checks foe changes in the aspect ratio given a threshold
        if(this->width > (this->m_window->GetWidth() + 40) || this->height > (this->m_window->GetHeight() + 40) ||
                        this->width < (this->m_window->GetWidth() - 40) || this->height < (this->m_window->GetHeight() - 40)){
            projection = glm::mat4(1.0f); projection = glm::perspective(glm::radians(45.0f),(float)this->m_window->GetWidth()/this->m_window->GetHeight(),0.1f,100.0f);
            this->width = this->m_window->GetWidth();
            this->height = this->m_window->GetHeight();
        }

        //Draws the cube
        glDrawElements(GL_TRIANGLES,this->indices_count,GL_UNSIGNED_INT,0);

 }

 void GameObject::SetUpObject(){
     
    //Creates VAO
    glGenVertexArrays(1,&this->VAO);
    //Creates and sets the Buffers
    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);
    //Binds the VAO -----------------------------------------------------------------------
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER,this->VBO);
        //This buffer data is saved on VAO
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*this->vertex_count,this->vertex,GL_DYNAMIC_DRAW);     
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBO);
        //As well the indices Buffer data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*this->indices_count,this->indices,GL_DYNAMIC_DRAW);
    //Defines how openGL should intepret vertex buffer data using the binded VBO
        //This is also saved on VAO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2); 
    //Unbids VAO ----------------------------------------------------------------------------
    glBindVertexArray(0);
    

    this->CreateShaderObject("shaders/vertex_shaders/MVP_vertex.vert","shaders/fragment_shaders/texture_fragment.frag");
    //this->m_texture = new Texture(this->shader,"Arrow.png","texture1",0);

 }

 void GameObject::CreateShaderObject(std::string vertex_shader, std::string fragment_shader){
    this->shader = new Shader();
    this->shader->LoadShader(vertex_shader,GL_VERTEX_SHADER);
    this->shader->LoadShader(fragment_shader,GL_FRAGMENT_SHADER);
    this->shader->LinkShaders();
    this->shader->SetTexture("Arrow.png");
 }


void GameObject::Update(){
    //if(test) return;

    if(this->m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS)){

        model = glm::rotate(model,3.0f * (float)m_time->delta_time, glm::vec3(0,1,0));
    }else if(this->m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS)){
        //anticlock-wise
        model = glm::rotate(model,-3.0f * (float)m_time->delta_time,glm::vec3(0,1,0));
    }

    if(this->m_input->ProcessInput(GLFW_KEY_UP,GLFW_PRESS)){
        //Down
        model = glm::translate(model,glm::vec3(0,3.0f*m_time->delta_time,0));
    }else if(this->m_input->ProcessInput(GLFW_KEY_DOWN,GLFW_PRESS)){
        //Up
        model = glm::translate(model,glm::vec3(0,-3.0f*m_time->delta_time,0));
    }


    else if(this->m_input->ProcessInput(GLFW_KEY_1,GLFW_PRESS)){
        Debugging::SetPoly2Fill();
    }else if(this->m_input->ProcessInput(GLFW_KEY_2,GLFW_PRESS)){
        Debugging::SetPoly2Line();
    }
    else if(this->m_input->ProcessInput(GLFW_KEY_3,GLFW_PRESS)){
        Debugging::SetPoly2Points();
    }

}