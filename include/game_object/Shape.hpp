#include<iostream>


class Shape{
    public:
        float* vertex;
        unsigned int* indices;
        unsigned int vertex_count;
        unsigned int indices_count;
        Shape(unsigned int vertex_count, unsigned int indices_count);
};

class Cube : public Shape{
    public:
        Cube();
};

class Triangle : public Shape{
    public:
        Triangle();
};