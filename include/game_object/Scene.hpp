#pragma once
#include<iostream>
#include<vector>

/*Have all objects of a scene separated on ALL, LiGHT and OPAQUE
    You can tell it to create any object
    It will load from text files (It could load on a sperate thread?)
    */
class Scene{
    public:
        Scene(std::string scene_path);
    
    private:
        std::string scene_path;
        void LoadSceneFromFile();
};