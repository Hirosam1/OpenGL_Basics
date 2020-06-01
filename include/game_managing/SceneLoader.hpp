#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include <regex>

#include "game_tools/FileManagementTools.hpp"
#include "personal_objects/all_personal.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/Light.hpp"
#include "game_object/Camera.hpp"
#include "game_object/Model.hpp"
#include "game_managing/BasicsBlock.hpp"



namespace SceneLoader {
    void LoadSceneFromFile(std::string scene_path, BasicsBlock* basic_block,SceneData* scene_data);
    void Testetemplates(BasicsBlock* bb ,Camera* main_camera);
};


