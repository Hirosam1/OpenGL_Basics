#include "game_object/GameObject.hpp"

class cObject : public GameObject{
    public:
        cObject(BasicsBlock* b, Camera* c,Model *m ,float ip[3],std::string vs, std::string fs, float size=0.25);
        void Update() override;
};