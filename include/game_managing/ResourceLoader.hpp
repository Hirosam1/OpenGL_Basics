#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<map>
#include <regex>

#include "game_tools/Debug.hpp"
#include "game_object/Model.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"
#include "game_managing/BasicsBlock.hpp"
#include "game_tools/FileManagementTools.hpp"

namespace ResourceLoader{
    void LoadResourceFromFile(std::string file_path,BasicsBlock* basic_block);
};