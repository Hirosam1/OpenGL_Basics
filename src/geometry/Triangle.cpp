#include "geometry/Shape.hpp"


Triangle::Triangle() : Shape(18,3){
    vertex = new float[18]{

     0.0f,   1.0f, 0.0f,  0.0f,   0.0f, 1.0f,    //Top      
     1.0f, -1.0f, 0.0f,   0.0f,   0.0f, 1.0f,  //BLeft         
    - 1.0f,  -1.0f, 0.0f, 0.0f,   0.0f, 1.0f   //BRight
    };
    indices = new unsigned int[3]{
    0,1,2
    };    
}