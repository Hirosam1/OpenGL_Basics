#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<string>
#include <fstream>

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#ifdef __unix__
#include <sys/resource.h>
#include <iomanip>
#endif
namespace Debug{
    void SetPoly2Line();
    void SetPoly2Fill();
    void SetPoly2Points();
    void SetPointsSize(int size);
    int GetMemoryUsage();
    void CleanErrorLog();
    void WriteErrorLog(std::string line);
    void Log(glm::mat4 mat4);
}