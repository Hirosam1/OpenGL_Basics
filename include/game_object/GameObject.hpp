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
#include "graphics/Shader.hpp"
#include "game_managing/Time.hpp"
#include "graphics/Window.hpp"
#include "game_managing/BasicsBlock.hpp"
#include "graphics/Material.hpp"
#include "graphics/Texture.hpp"

#include "game_object/Model.hpp"


class GameManager;

class GameObject{
    public:
        std::string object_name = "Game Object";
        friend class GameManager;
        //Constructors
        GameObject(BasicsBlock* basic_block);
        GameObject(BasicsBlock* basic_block, Camera* m_camera,float initial_pos[3]);
        GameObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],
        std::string vert_shader_path =  std::string("shaders/vertex_shaders/MVP_vertex.vert"),
        std::string frag_shader_path =  std::string("shaders/fragment_shaders/basic_fragment.frag"));
        GameObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader);

        //Creates the shader object, ready to use
        void CreateShaderObject(std::string* vertex_shader,std::string* fragment_shader);
        //Sets the texture to use
        void AddTexture(std::string* tex_path, GLenum type = GL_RGB, std::string* uniform_name = nullptr);
        void AddTexture(Texture* texture,std::string* uniform_name = nullptr);

        /*Shared attributes*/
        //The camera containing the view matrix
        Camera* m_camera;
        //Time object
        Time* m_time;
        //The material of the object
        Material* m_material;
        //Shader Object
        Shader *m_shader = nullptr;
        //Model of the object
        Model* m_model = nullptr;

        /*Personal attributes*/
        //The model matrix
        glm::mat4 model_mat; 

        bool change = false;

        bool isSelected = false;

        bool isOpaque = false;

    private: 
        void UseShader();
        /*Updates entearly the game object
            -> Handles the binding and unbing of VAO, EBO and VBO
            -> Buffer MVP
            -> Draw model */
        void BufferAndDraw();

        void ReadyObject();
        //Sets the MVP to its initial position
        void SetInitialMVP();

        //Buffer data into shader 
        void BufferData();

        //path to the shaders
        std::string vertex_shader_path;
        std::string fragment_shader_path;

    protected:
        BasicsBlock* bb;
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