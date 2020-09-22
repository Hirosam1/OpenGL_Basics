#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

namespace Time{
    double GetTime();
    void UpdateDelta();
    extern double delta_time;
    extern double last_value;
};