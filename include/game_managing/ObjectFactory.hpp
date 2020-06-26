#pragma once
#include <map>
#include "game_managing/BasicsBlock.hpp"
#include "game_object/Model.hpp"
#include "game_object/GameObject.hpp"
#include "graphics/Texture.hpp"

namespace ObjectsManager{
    void InitializeAllObjects();
}

namespace GameObjectFactory{
    GameObject* GetObjectFromID(unsigned int id, BasicsBlock* basic_block, Camera* m_camera,Model* m_model,float initial_pos[3], Shader* m_shader);
};

namespace TextureFactory{
    Texture* GetObjectFromID(unsigned id, std::string texture_path);
}