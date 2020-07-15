#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include<string>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#ifdef __unix__
#include <sys/resource.h>
#include <iomanip>
#endif
class Debugging{
    public:
        static void SetPoly2Line();
        static void SetPoly2Fill();
        static void SetPoly2Points();
        static void SetPointsSize(const int size);
        static int GetMemoryUsage();
};

namespace Debug{
    void Log(glm::mat4 mat4);
}