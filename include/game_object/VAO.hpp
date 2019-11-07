#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include<deque>


class VAO{
    public:
        VAO();
        //Sets the parameters for the overloading function, the order that those are called is the number of the Vertex 
        //Attribute Array wich it will be stored the data
        void SetAttribPoint(unsigned int vertex_att_num, GLenum type, GLenum target = GL_INVALID_VALUE);
        //When ready, sets all att points
        void SetUpObject();
        //Buffer the Data
        template<typename T> 
        void BufferData(T* data,GLenum array_or_element,GLenum type,unsigned int count, GLenum draw_type = GL_STATIC_DRAW);
        //Bind the VAO
        void UseVAO();
    private:
        //Uses the data stored in this object to Set Att point to an indivdual att
        void SetAttribPoint(unsigned int index,unsigned int vertex_att_num, GLenum type, GLenum target);
        //Get the sum of datasize before a point (att), this point is EXCLUSIVE
        int SumSizesToAtt(unsigned int att_to_stop);
        unsigned int indv_ready;
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_EBO;
        unsigned int stride;
        std::deque<unsigned int>* indv_sizes;
        //std::deque<unsigned int>* indv_types_sizes;
        std::deque<GLenum>* indv_data_types;
        std::deque<GLenum>* indv_array_types;

        //Calculates the stride of the data
        unsigned int GetStride();
};