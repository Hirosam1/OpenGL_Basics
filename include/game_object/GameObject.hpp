#pragma once
#include<iostream>
#include<glad/glad.h>
//#include<GLFW/glfw3.h>
#include<string.h>
#include<string>
#include<deque>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "game_tools/stb_image.h"
#include "game_object/Camera.hpp"
#include "game_tools/Debugging.hpp"
#include "game_managing/InputManager.hpp"
#include "geometry/Shape.hpp"
#include "graphics/Shader.hpp"
#include "game_managing/Time.hpp"
#include "game_object/VAO.hpp"
#include "graphics/Window.hpp"
#include "game_managing/BasicsBlock.hpp"
#include "game_object/Light.hpp"
#include "graphics/Material.hpp"
#include "graphics/Texture.hpp"


class GameManager;

class GameObject{
    public:
        std::string object_name = "Game Object";
        friend class GameManager;
        //Constructors
        GameObject(BasicsBlock* basic_block);
        GameObject(BasicsBlock* basic_block, Camera* m_camera,float initial_pos[3]);
        GameObject(BasicsBlock* basic_block,Camera* m_camera,Shape* m_shape,float initial_pos[3],
        std::string* vert_shader_path = new std::string("shaders/vertex_shaders/MVP_vertex.vert"),
        std::string* frag_shader_path = new std::string("shaders/fragment_shaders/basic_fragment.frag"));

        //Creates the shader object, ready to use
        void CreateShaderObject(std::string* vertex_shader,std::string* fragment_shader);
        //Sets up the object to be ready to update/render
        void SetUpVertex();
        //Sets up the object to be ready to update/render
        void SetUpVertex(VAO* aVAO);
        //Sets the texture to use
        void AddTexture(std::string* tex_path, GLenum type = GL_RGB, std::string* uniform_name = nullptr);
        void AddTexture(Texture* texture,std::string* uniform_name = nullptr);
        //Sets the Object as a light Source
        void MakeLight();
        //Gives a light object to the GameObject, so it can be iluminated or become a light source with MakeLight()
        void GiveLight(Light* light);

        //The camera containing the view matrix
        Camera* m_camera;
        //The model matrix
        glm::mat4 model; 
        //Shader Object
        Shader* shader;
        //Time object
        Time* m_time;
        //Light object
        Light* m_light;
        //The material of the object
        Material* m_material;

    private: 
        /*Updates entearly the game object
            -> Handles the binding and unbing of VAO, EBO and VBO
            -> Copile and use shaders
            -> Handles Textures */
        void UpdateAndBuffer();

        void ReadyObject();
        //Sets the MVP to its initial position
        void SetInitialMVP();

        //The shape of the model
        Shape* m_shape;

        //VAO game object
        VAO* m_vao;

        //path to the shaders
        std::string* vertex_shader_path;
        std::string* fragment_shader_path;
        //std::string* model_shader_path;
    protected:
        BasicsBlock* bb;
        bool isLight = false;
        //Window where the object will get inputs
        Window* m_window;
        InputManager* m_input;

        /*Individual Update function that should be overridern by each game Object,
        it will be updated each frame, there you can proccess inputs and alter game 
        logic and objects, e.g., Cameras, Models, Projections
        */
        virtual void Update()=0; //Pure virtual function, you need to create sub classes to implement it
        virtual void Ready();
  
};