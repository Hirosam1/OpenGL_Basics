#pragma once
#include "game_object/GameObject.hpp"
#include "game_object/Light.hpp"

class PulsingLight : public GameObject{
    public:
        static constexpr unsigned int go_id = 5;
        PulsingLight(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader);

        void Update() override;
        void Ready() override;

        PointLight* pointLight;

};