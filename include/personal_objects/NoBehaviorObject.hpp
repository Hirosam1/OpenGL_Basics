#include "game_object/GameObject.hpp"

class NoBahaviorObject : public GameObject{
    public:
        NoBahaviorObject(BasicsBlock* bb, Camera* camera, Model* model, float initial_pos[3],Shader* m_shader);
        void Update() override;

};
