#pragma once
#include <map>
#include "game_managing/BasicsBlock.hpp"
#include "game_object/Model.hpp"
#include "game_object/GameObject.hpp"

namespace GameObjectFactory{
    GameObject* GetObjectFromID(unsigned int id, BasicsBlock* basic_block, Camera* m_camera,Model* m_model,float initial_pos[3], Shader* m_shader);
};