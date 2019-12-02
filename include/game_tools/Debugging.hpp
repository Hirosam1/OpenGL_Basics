#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <sys/resource.h>
#include <iomanip>  
class Debugging{
    public:
        static void SetPoly2Line();
        static void SetPoly2Fill();
        static void SetPoly2Points();
        static void SetPointsSize(const int size);
        static int GetMemoryUsage();
};