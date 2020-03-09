#include "game_object/GameObject.hpp"

class cObject : public GameObject{
    public:
        cObject(BasicsBlock* b, Camera* c,Model *m ,float ip[3],Shader* m_shader, float size=0.25);
        void Update() override;
};