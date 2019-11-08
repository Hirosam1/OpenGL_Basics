#include "geometry/Shape.hpp"


Triangle::Triangle() : Shape(24,3){
    vertex = new float[24]{

     0.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,     //Top      
    -1.0f, -1.0f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,    //Left         
     1.0f,  -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,     //Right
    };
    indices = new unsigned int[3]{
    0,1,2
    };    
}