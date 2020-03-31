#include "game_object/GameObject.hpp"

class cObject : public GameObject{
    public:
        const unsigned int go_id = 3;
        cObject(BasicsBlock* b, Camera* c,Model *m ,float ip[3],Shader* m_shader, float size=0.25);
        void Update() override;
        
};