#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Shape{
    public:
        float* vertex = nullptr;
        unsigned int* indices = nullptr;
        unsigned int att_count;
        unsigned int vertex_count;
        unsigned int indices_count;
        unsigned int triag_count;
        Shape(unsigned int att_count,unsigned int vertex_count = 3 ,unsigned int indices_count = 0);
};

class Cube : public Shape{
    public:
        Cube();
};

class CubeTex: public Shape{
    public:
        CubeTex();
};

class Triangle : public Shape{
    public:
        Triangle();
};

class Plane : public Shape{
    public:
        Plane();
};