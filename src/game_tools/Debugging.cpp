#include "game_tools/Debugging.hpp"

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValueKB(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}

int Debugging::GetMemoryUsage(){
    #ifdef __unix__
    return getValueKB();
    #else 
    return -1;
    #endif
}

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
