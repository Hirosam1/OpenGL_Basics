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
class CubeMap;

struct SceneData{
    std::string scene_name;
    std::vector<GameObject*> AllObjects;
    std::vector<Light*> AllLights;
    std::vector<GameObject*> AllOpaques;
    std::map<std::string, Model*> loaded_models;
    std::map<std::string, Texture*> loaded_textures;
    std::map<std::string, Camera*> all_cameras;
    Camera* main_camera;
    CubeMap* cube_map = nullptr;
    unsigned int n_point_lights = 0;
    unsigned int n_spot_lights = 0;
};

struct GlobalData{
   GLenum fill_type = GL_FILL;
   std::string game_name;
   
   std::map<std::string,std::string> models_path;
   std::map<std::string, Shader*> all_shaders;
   std::map<std::string, std::string> textures_path;
   
   Scene *active_scene = nullptr;
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
        unsigned int uniform_buffer_light;
        bool should_close = false;
        Window* m_window;
        InputManager* m_input;
        Time* m_time;

        //GUI game object
        GameObject* GUI_gameObject;

        //Threading
        std::mutex global_mutex;
        std::mutex scene_mutex;
        //Global information
        GlobalData global_data;
        //Shader responsible for drawing the outline of objects
        Shader outline_shader;
        Shader wireframe_shader;
        //I probably should put those strings on a file?
        std::string Model_string;

        std::string Mat_ambient;
        std::string Mat_diffuse;
        std::string Mat_specular;
        std::string Mat_shininess;

        std::string LampColor;
        

};