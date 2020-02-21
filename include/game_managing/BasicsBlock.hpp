#pragma once
#include <string>
#include <iostream>
#include <vector>

class Window;
class InputManager;
class Time;
class GameObject;

class BasicsBlock{
    public:
        BasicsBlock(Window* window, InputManager* input, Time* time,std::vector<GameObject*>* all_objs);
        Window* m_window;
        InputManager* m_input;
        Time* m_time;
        std::vector<GameObject*>* all_objs;

        //I probably should put those strings on a file?
        std::string Model_string;
        std::string View_string;
        std::string Projection_string;

        std::string Mat_ambient;
        std::string Mat_diffuse;
        std::string Mat_specular;
        std::string Mat_shininess;

        std::string Light_ambient;
        std::string Light_diffuse;
        std::string Light_specular;

        std::string Light_pos;

        std::string Light_direction;

        std::string Basic_tex;

        std::string Light_constant;
        std::string Light_linear;
        std::string Light_quadratic;

        std::string Light_CutOff;
};