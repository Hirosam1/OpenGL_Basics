#pragma once
#include<iostream>
#include<vector>
#include"game_object/GameObject.hpp"

/*Have all objects of a scene separated on ALL, LiGHT and OPAQUE
    You can tell it to create any object
    It will load from text files (It could load on a separate thread?)
*/
class Scene{
    public:
        Scene(std::string scene_path);
        void AddGameObject();
        void AddLightObject();
    private:
        std::string scene_path;
        void LoadSceneFromFile();
};