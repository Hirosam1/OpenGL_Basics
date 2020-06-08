#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include<deque>


class VAO{
    public:
        VAO(GLenum vertex_type = GL_FLOAT);
        void UnloadVAO();
        //Sets the parameters for the overloading function, the order that those are called is the number of the Vertex 
        /*Will set one type of data that will be sent to the GPU, each call from this will register in the layout at the order of call 0, 1 2
        vertex_att_num -> the number of attributes on each stride
        element_stride -> leave it as -1 (default) to be always adjacent to the last attribute, you can set it yourself, by defining the number of attributes it needs to "jump" NOT including the number of att of this own data */
        void SetAttribPoint(unsigned int vertex_att_num, int element_stride = -1);
        //When ready, sets all att points
        void SetUpObject();
        //Buffer the Data
        template<typename T> 
        void BufferData(T* data,GLenum array_or_element,GLenum type,unsigned int count, GLenum draw_type = GL_STATIC_DRAW);
        //Bind the VAO
        void UseVAO();

        GLenum vertex_type;

        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_EBO;

    private:
        //Uses the data stored in this object to Set Att point to an indivdual att
        void SetAttribPoint(unsigned int index,unsigned int vertex_att_num, GLenum type);
        //Get the sum of datasize before a point (att), this point is EXCLUSIVE
        int SumSizesToAtt(unsigned int att_to_stop);

        unsigned int indv_ready;

        unsigned int stride;
        std::deque<unsigned int>* indv_sizes;
        //std::deque<unsigned int>* indv_types_sizes;
        //std::deque<GLenum>* indv_data_types;
        std::deque<int>* elements_stride;

        //Calculates the stride of the data
        unsigned int GetStride();
};