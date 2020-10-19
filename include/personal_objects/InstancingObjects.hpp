#include "game_object/GameObject.hpp"

class InstancingObjects : public GameObject{
    public:
        int  amount = 100;
        glm::vec2 translations[100];
        InstancingObjects(BasicsBlock* bb, Camera* camera, Model* model, float initial_pos[3],Shader* m_shader);
        void Update() override;
        void Ready() override;
};