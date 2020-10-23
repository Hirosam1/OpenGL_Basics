#pragma once
#include<iostream>
#include<vector>
#include<mutex>
#include"game_object/GameObject.hpp"
#include "game_managing/BasicsBlock.hpp"
#include "game_managing/SceneLoader.hpp"
#include "game_object/Camera.hpp"

/*Have all objects of a scene separated on ALL, LiGHT and OPAQUE
    You can tell it to create any object
    It will load from text files (It could load on a separate thread?)
*/
class Scene{
    public:
        Scene(std::string scene_path, BasicsBlock* basic_block);
        ~Scene();
        SceneData scene_data;
        GameObject* AddGameObject(unsigned int GO_id, Camera* camera,Model* model,float initial_pos[3], Shader* shader,bool opaque = false ,glm::vec3 scale = glm::vec3(1));
        GameObject* AddGameObject(std::string GO_name, unsigned int GO_id, Camera* camera,Model* model,float initial_pos[3], Shader* shader,bool is_opaque = false ,glm::vec3 scale = glm::vec3(1));
        void AddLightObject();
        static bool ChangeScene(std::string scene_path, BasicsBlock* basic_block);
        bool isReady;
    private:
        BasicsBlock* basic_block;
        std::string scene_path;
};