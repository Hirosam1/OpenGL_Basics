#include "game_object/GameObject.hpp"

class NoBahaviorObject : public GameObject{
    public:
        //static constexpr unsigned int go_id = 4;
        NoBahaviorObject(BasicsBlock* bb, Camera* camera, Model* model, float initial_pos[3],Shader* m_shader);
        void Update() override;

};
