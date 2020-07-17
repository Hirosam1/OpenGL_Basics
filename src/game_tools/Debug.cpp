#include "game_tools/Debug.hpp"

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

int Debug::GetMemoryUsage(){
    #ifdef __unix__
    return getValueKB();
    #else 
    return -1;
    #endif
}

void Debug::SetPoly2Line(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}

void Debug::SetPoly2Fill(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void Debug::SetPoly2Points(){
    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
}

void Debug::SetPointsSize(int size){
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(size);
}

void Debug::Log(glm::mat4 model){
    std::cout<<"<mat4>==============\n";
    for(unsigned int i = 0; i < 4; i++){
        std::cout<<"\n";
        for(unsigned int j = 0; j < 4; j++){
            std::cout<<model[i][j] << ", ";
        }
    }
    std::cout<<"\n====================\n";
}

void Debug::WriteErrorLog(std::string line){
    std::ofstream outfile;
    outfile.open("ErrorLog.log", std::ofstream::out | std::ofstream::app);
    outfile << line << "\n";
    outfile.close();
}

void Debug::CleanErrorLog(){
    std::ofstream outfile;
    outfile.open("ErrorLog.log", std::ofstream::out | std::ofstream::trunc);
    outfile.close();
}