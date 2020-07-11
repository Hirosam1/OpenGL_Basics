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
        void AddGameObject();
        void AddLightObject();
        static bool ChangeScene(std::string scene_path, BasicsBlock* basic_block);
        bool isReady;
    private:
        std::string scene_path;
        //void LoadSceneFromFile(std::string scene_path, BasicsBlock* basic_block);
};