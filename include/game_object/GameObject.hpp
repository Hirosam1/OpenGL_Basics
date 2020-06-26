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

struct GameObjectElements{
    BasicsBlock* basic_block = nullptr;
    Camera* m_camera = nullptr;
    Model* model = nullptr;
    float* initial_pos;
    Shader* m_shader = nullptr;
    glm::vec3 size = glm::vec3(1.0);
};

/*Basic game object
    You need to inherit this class to use this class
    You can create "empty" object, that has no Mesh or shaders, you can use this to only get input, or only manipulate other objects
    If you want to render a object, you need to pass a Mesh and a Shader
    It higly depends of a camera to make position calculations
    You can use the same Mesh, Shader to render you ocject, in order to save resorces
*/
class GameObject{
    public:
        std::string object_name = "Game Object";
        friend class GameManager;
        friend class Scene;
        //Constructors
        /*GameObject(BasicsBlock* basic_block);
        GameObject(BasicsBlock* basic_block, Camera* m_camera,float initial_pos[3]);
        GameObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3], std::string vert_shader_path, std::string frag_shader_path);*/
        GameObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader);
        ~GameObject();
        //Creates the shader object, ready to use
        void CreateShaderObject(std::string* vertex_shader,std::string* fragment_shader);
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

        float* initial_pos;
    private:
        bool use_main_camera = false;
        //static constexpr unsigned int go_id = 0;
        
        void UseShader();
        /*Updates entearly the game object
            -> Handles the binding and unbing of VAO, EBO and VBO
            -> Buffer MVP
            -> Draw model */
        

        void ReadyObject();
        //Sets the MVP to its initial position
        void SetInitialMVP();

        //Buffer data into shader 
        void BufferData();

        //path to the shaders
        std::string vertex_shader_path;
        std::string fragment_shader_path;

    protected:
        
        BasicsBlock* basic_block;
        void BufferAndDraw();
        
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