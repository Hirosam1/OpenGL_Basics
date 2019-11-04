#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

class Debugging{
    public:
        static void SetPoly2Line();
        static void SetPoly2Fill();
        static void SetPoly2Points();
        static void SetPointsSize(const int size);
};