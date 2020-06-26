#include "game_object/GameObject.hpp"

class cObject : public GameObject{
    public:
        //static constexpr unsigned int go_id = 3;
        cObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader);
        void Update() override;
        
};