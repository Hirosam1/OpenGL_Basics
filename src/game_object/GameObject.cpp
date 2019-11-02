#include "game_object/GameObject.h"
 GameObject::GameObject()
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
    }
{

}

//Updates the data and send it to GPU
 void GameObject::Update(){

        //Updaets the vertex data
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
    this->shader = new Shader();
    this->shader->LoadShader("shaders/vertex_shaders/texture_vertex.vert",GL_VERTEX_SHADER);
    this->shader->LoadShader("shaders/fragment_shaders/texture_fragment.frag",GL_FRAGMENT_SHADER);
    this->shader->LinkShaders();
    this->LoadTexture();

 }

 void GameObject::LoadTexture(){

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
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0); 
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
    this->shader->UseShader();
    this->shader->SetUniform1i("texture1",0);
 }