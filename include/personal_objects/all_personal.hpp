#pragma once
#include <map>
#include "game_managing/BasicsBlock.hpp"
#include "game_object/Model.hpp"
#include "game_object/GameObject.hpp"
#include "personal_objects/aObject.hpp"
#include "personal_objects/bObject.hpp"
#include "personal_objects/cObject.hpp"
#include "personal_objects/NoBehaviorObject.hpp"
#include "personal_objects/PulsingLight.hpp"

namespace GameObjectFactory{
    GameObject* GetObjectFromID(unsigned int id, BasicsBlock* basic_block, Camera* m_camera,Model* m_model,float initial_pos[3], Shader* m_shader);
};