#include "game_tools/Debugging.hpp"

void Debugging::SetPoly2Line(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void Debugging::SetPoly2Fill(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void Debugging::SetPoly2Points(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
}

void Debugging::SetPointsSize(int size){
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(size);
}
