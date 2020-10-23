#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include <regex>

#include "game_tools/FileManagementTools.hpp"
#include "game_managing/ObjectFactory.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/Light.hpp"
#include "game_object/Camera.hpp"
#include "game_object/Model.hpp"
#include "game_managing/BasicsBlock.hpp"
#include "graphics/CubeMap.hpp"


namespace SceneLoader {
    bool LoadSceneFromFile(std::string scene_path, BasicsBlock* basic_block,SceneData* scene_data, SceneData* old_scene_data);
};


