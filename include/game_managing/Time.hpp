#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>

class Time{
    public:
        Time();
        double GetTime(bool last_frame = false);
        void UpdateDelta();
        double delta_time;
    private:
        double last_value;
};