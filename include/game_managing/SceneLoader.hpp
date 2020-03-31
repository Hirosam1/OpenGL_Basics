#pragma once
#include<iostream>
#include<vector>
#include<fstream>

#include "game_tools/FileManagementTools.hpp"
#include "personal_objects/all_personal.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/Light.hpp"

struct SceneData{
    std::vector<GameObject*> AllObjects;
    std::vector<Light*> AllLights;
    std::vector<GameObject*> AllOpaques;
};

namespace SceneLoader {
    void LoadSceneFromFile(std::string scene_path, SceneData* scene_data);
};


