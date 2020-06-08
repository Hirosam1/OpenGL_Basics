#include "game_object/VAO.hpp"


VAO::VAO(GLenum vertex_type):vertex_type(vertex_type = GL_FLOAT){
    this->m_VAO = 0;
    this->m_EBO = 0;
    this->indv_sizes = new std::deque<unsigned int>();
    this->elements_stride = new std::deque<int>();
    //this->indv_array_types = new std::deque<GLenum>();
    //this->indv_data_types = new std::deque<GLenum>();
    this->indv_ready = 0;
    glGenVertexArrays(1,&this->m_VAO);
    glGenBuffers(1,&this->m_VBO);
    glGenBuffers(1,&this->m_EBO);


}

void VAO::UnloadVAO(){
    glDeleteBuffers(1, &this->m_VBO);
    glDeleteBuffers(1, &this->m_EBO);

    glDeleteVertexArrays(1, &this->m_VAO);
}

void VAO::SetAttribPoint(unsigned int index,unsigned int vertex_att_num, GLenum type){
    stride = this->elements_stride->at(index) < 1 ?this->GetStride() : this->elements_stride->at(index) * sizeof(this->vertex_type);
    glVertexAttribPointer(index,vertex_att_num,type,GL_FALSE, stride, (void *)(uintptr_t)this->SumSizesToAtt(index));
    glEnableVertexAttribArray(index);
}

void VAO::SetAttribPoint(unsigned int vertex_att_num,int element_stride){
    this->indv_sizes->push_back(vertex_att_num);
    this->elements_stride->push_back(element_stride);
}

void VAO::SetUpObject(){
    glBindVertexArray(this->m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,this->m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->m_EBO);
    
    for(auto a = 0; a < this->indv_sizes->size(); a++){
        SetAttribPoint(a,this->indv_sizes->at(a),this->vertex_type);
    }
}


int VAO::SumSizesToAtt(unsigned int att_to_stop){
    int sum = 0;
    for(auto a = 0; a < this->indv_sizes->size() && a != att_to_stop; a++){
        sum += this->indv_sizes->at(a) * sizeof(this->vertex_type);
        
    }

    return sum;
}


unsigned int VAO::GetStride(){
    int stride = 0;
    for(auto a = 0; a < this->indv_sizes->size(); a++){
        stride += this->indv_sizes->at(a) * sizeof(this->vertex_type);
    }
    return stride;
}

void VAO::UseVAO(){
    glBindVertexArray(this->m_VAO);
}

template<typename T> 
void VAO::BufferData(T* data,GLenum array_or_element,GLenum type,unsigned int count, GLenum draw_type){
    glBindVertexArray(this->m_VAO); 
    glBufferData(array_or_element,sizeof(type)*count,data,draw_type);
    glBindVertexArray(0); 
}

template void VAO::BufferData<GLfloat>(GLfloat* data,GLenum array_or_element,GLenum type,unsigned int count, GLenum draw_type);
template void VAO::BufferData<GLdouble>(GLdouble* data,GLenum array_or_element,GLenum type,unsigned int count, GLenum draw_type);
template void VAO::BufferData<GLuint>(GLuint* data,GLenum array_or_element,GLenum type,unsigned int count, GLenum draw_type);
