#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game_object/GameObject.hpp"

//That is not supposed to be a game engine class
class CameraController : GameObject{
    public:
        CameraController(Window* m_window,InputManager* m_input,Time* m_time, Camera* m_camera);
        void Update() override;
}; 