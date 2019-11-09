#pragma once
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game_managing/InputManager.hpp"
#include "game_managing/Time.hpp"
#include "game_object/VAO.hpp"
#include "game_tools/Debugging.hpp"
#include "game_tools/stb_image.h"
#include "geometry/Shape.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Window.hpp"

#include "game_object/Camera.hpp"




class GameObject{
    public:
        //Constructors
        GameObject(Window* aWindow,InputManager* m_imput, Time* m_time);
        GameObject(Window* aWindow,InputManager* m_input, Time* m_time,Shape* m_shape,Camera* m_camera ,float initial_pos[3],
        std::string* vert_shader_path,std::string* frag_shader_path);

        //Public Updates
        void UpdateAndBuffer();

        //Shaders Management
        //Creates the shader object, ready to use
        void CreateShaderObject(std::string* vertex_shader,std::string* fragment_shader);

        //Sets up the object to be ready to update/render
        void SetUpObject();

        //Sets the texture to use
        void SetTexture(std::string* tex_path);

    private:
        //Sets the MVP to its initial position
        void SetInitialMVP();
        std::string* MVP_string;

        //View (camera) and projection (perspective) matrixes
        glm::mat4 view;
        glm::mat4 projection;
        //Window size for the projection
        unsigned int width;
        unsigned int height;

        //Vertices of a triangle along with their indices and numberof points and indices
        GLfloat* vertex;
        GLuint* indices; 
        unsigned int vertex_count;
        unsigned int indices_count;

        //VAO game object
        VAO* m_vao;

        //path to the shaders
        std::string* vertex_shader_path;
        std::string* fragment_shader_path;

        //path to the texture

    protected:
        //The camera containing the view matrix
        Camera* m_camera;

        //The model matrix
        glm::mat4 model; 
        //Shader Object
        Shader* shader;
        InputManager* m_input;
        //Time object
        Time* m_time;
        //Window where the object will get inputs
        Window* m_window;
        //Children of GameObject class will inherit this method. This is where you update the data within GameObject
        virtual void Update()=0; //Pure virtual function, you need to create sub classes to implement it

        
};