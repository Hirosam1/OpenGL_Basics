#pragma once
#include "game_object/GameObject.hpp"

class InstancingObjects : public GameObject{
    public:
        std::string amount_str = "amount";
        glm::vec2 *translations;
        unsigned int amount_per_d = 0;
        InstancingObjects(BasicsBlock* bb, Camera* camera, Model* model, float initial_pos[3],Shader* m_shader);

        ~InstancingObjects() override;
        void Update() override;
        void Ready() override;
};