#include "game_object/GameObject.h"
 GameObject::GameObject(InputManager* m_input, Time* m_time)
    :vertices{
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        },
    indices{    
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    },
    m_input(m_input),
    m_time(m_time)
{

}

//Updates the data and send it to GPU
 void GameObject::UpdateAndBuffer(){
        ///Updaets the vertex data
        this->Update();

        //Updaets saves data on buffers
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,this->texture);
        this->shader->UseShader();
        //Puts data into GPU and uses VAO
        glBindVertexArray(this->VAO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(this->vertices),this->vertices,GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(this->indices),this->indices,GL_STATIC_DRAW);

 }

 void GameObject::SetUpObject(){
    //Creates VAO
    glGenVertexArrays(1,&this->VAO);
    //Creates and sets the Buffers
    glGenBuffers(1,&this->VBO);
    glGenBuffers(1,&this->EBO);
    //Binds the VAO -----------------------------------------------------------------------
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->EBO);

    //Defines how openGL should intepret vertex buffer data using the binded VBO
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8 * sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  
    //Unbids VAO ----------------------------------------------------------------------------
    glBindVertexArray(0);

    this->CreateShaderObject("shaders/vertex_shaders/texture_vertex.vert","shaders/fragment_shaders/texture_fragment.frag");
    this->CreateTexture("container.jpg");
 }

 void GameObject::CreateTexture(std::string texture_path){

    //Creates and binds the Texture object
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D,this->texture);

    //Sets the parameters for warapping and filtering
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    //stbi_set_flip_vertically_on_load(true);  
    int width, height, nrChannels;
    //Loads image
    unsigned char *data = stbi_load(texture_path.data(), &width, &height, &nrChannels, 0); 
    if(data){
    //Creats the texture image on the current bound texture object
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    //Genetates mip maps automatacly
    glGenerateMipmap(GL_TEXTURE_2D);
    //Free loaded image
    }else{
        std::cout<<"Failed to load texture\n";
        exit(-1);
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D,0);
    //Set the uninoform of texture of the shader to be 0
    this->shader->UseShader();
    this->shader->SetUniform1i("texture1",0);
 }

 void GameObject::CreateShaderObject(std::string vertex_shader, std::string fragment_shader){
    this->shader = new Shader();
    this->shader->LoadShader(vertex_shader,GL_VERTEX_SHADER);
    this->shader->LoadShader(fragment_shader,GL_FRAGMENT_SHADER);
    this->shader->LinkShaders();
 }


void GameObject::Update(){
    if(this->m_input->ProcessInput(GLFW_KEY_RIGHT,GLFW_PRESS)){
        this->vertices[0] = this->vertices[0] + 1.0f*m_time->delta_time;
    }
    else if(this->m_input->ProcessInput(GLFW_KEY_LEFT,GLFW_PRESS)){
        this->vertices[0] = this->vertices[0] - 1.0f*m_time->delta_time;
    }if(this->m_input->ProcessInput(GLFW_KEY_UP,GLFW_PRESS)){
        this->vertices[1] = this->vertices[1] + 1.0f*m_time->delta_time;
    }
    else if(this->m_input->ProcessInput(GLFW_KEY_DOWN,GLFW_PRESS)){
        this->vertices[1] = this->vertices[1] - 1.0f*m_time->delta_time;
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