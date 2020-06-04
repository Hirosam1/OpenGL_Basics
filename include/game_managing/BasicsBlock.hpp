#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <mutex>
#include <map>
#include "graphics/Shader.hpp"

class Window;
class InputManager;
class Time;
class GameObject;
class Texture;
class Camera;
class Scene;
class Light;
class Model;

struct SceneData{
    std::vector<GameObject*> AllObjects;
    std::vector<Light*> AllLights;
    std::vector<GameObject*> AllOpaques;
    std::map<std::string, Model*> loaded_models;
    std::map<std::string, Camera*> all_cameras;
    Camera* main_camera;
    int n_point_lights = 0;
};

struct GlobalData{
   GLenum fill_type = GL_FILL;
   std::string game_name;
   std::map<std::string,std::string> models_path;
   std::map<std::string, Shader*> all_shaders;
   std::map<std::string, Texture*> all_textures;
   
   Scene *active_scene;
};
/*
This class contain critical and default information of the engine, such as:
> Scene information
> Global Data
> Window Data
> Input Data
> Time data
> Strings for the basic shaders
> Window resize behaviour
*/
class BasicsBlock{
    public:
        BasicsBlock(Window* window, InputManager* input, Time* time);
        bool was_resized = false;
        void WindowResized();
        
        Window* m_window;
        InputManager* m_input;
        Time* m_time;

        //Threading
        std::mutex global_mutex;
        //Global information
        GlobalData global_data;
        //Shader responsible for drawing the outline of objects
        Shader outline_shader;
        //I probably should put those strings on a file?
        std::string Model_string;
        std::string View_string;
        std::string Projection_string;

        std::string Mat_ambient;
        std::string Mat_diffuse;
        std::string Mat_specular;
        std::string Mat_shininess;

        std::string DirLight_prefix;
        std::string PointLights_prefix;
        std::string SpotLight_prefix;

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
        std::string Light_OutCutoff;

        std::string LampColor;
        
        std::string n_point_lights_string;

};