#pragma once
#include "game_object/GameObject.hpp"
#include "game_object/Light.hpp"

class PulsingLight : public GameObject{
    public:
        const unsigned int go_id = 5;
        PulsingLight(BasicsBlock* bb, Camera* m_camera, float initial_pos[3]);

        void Update() override;
        void Ready() override;

        PointLight* pointLight;

};