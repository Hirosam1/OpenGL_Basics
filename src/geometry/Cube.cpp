#include "geometry/Shape.hpp"


Cube::Cube():Shape(64,36){
    vertex = new float[48]{
    // positions          // colors                         //Front
    0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f, // top right    0
    0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f, // bottom right 1
    -0.5f,-0.5f, 0.5f,   0.0f, 0.0f, 1.0f, // bottom left  2
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f, // top left     3
                                                            //Back
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // top right    4                                      
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // bottom right 5
    -0.5f,-0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // bottom left  6
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f  // top left     7
    };

    indices = new unsigned int[36]{
        0, 1, 3,    // front 1 triangle
        1, 2, 3,    // front 2 triangle
        0, 4, 5,    // right 1 triangle
        0, 1, 5,    // right 2 triangle
        2, 3, 7,    // left  1 triangle
        2, 7, 6,    // left  2 triangle
        4, 7, 5,    // back  1 triangle
        7, 6, 5,    // back  2 triangle
        0, 4, 3,    // top   1 triangle
        3, 7, 4,    // top   2 triangle
        1, 5, 2,    //buttom 1 triangle
        2, 6, 5     //buttom 2 reiangle    
 
    };
}

