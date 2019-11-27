#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<deque>


#include"game_managing/InputManager.hpp"
#include "game_managing/Time.hpp"
#include "game_object/aObject.hpp"
#include "game_object/bObject.hpp"
#include"game_object/GameObject.hpp"
#include "game_tools/Debugging.hpp"
#include "geometry/Shape.hpp"
#include "graphics/Window.hpp"

#include "game_object/Camera.hpp"


class GameManager{
    private:
        GLFWwindow* m_window;
        //------------------------------------- Variables ---------------------------------------------------------------
        Window* main_window;
        //default width and height of game window
        int width;
        int height;

        //the current width and height of game window
        int current_width;
        int current_height;

        //is game engine ready to star rendering?
        bool ready_to_start;

        //The input manager
        InputManager* main_input;

        //All the vertex to render
        float* vertices;
    
        //name of the game
        std::string game_name;

        //Game object to render (Will have multiple in the future)
        GameObject* go2;
        GameObject* go;

        std::deque<GameObject*>* all_objs;

        //Global time manager
        Time* main_time;

        //------------------------------------- Methods ----------------------------------------------------------------
        
        //Error handler of GLFW
        static void ErrorCallback(int error, const char* description);

        //Callback when Buffer size changes
        static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

    public:
        GameManager(std::string game_name,int width, int height);
        //Initiate the game engine, and become ready to start
        void EngineInit();
        //Starts the main loop of the game engine
        void EngnieStart();
};