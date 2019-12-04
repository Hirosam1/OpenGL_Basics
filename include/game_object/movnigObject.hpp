#include "game_object/GameObject.hpp"

class MovingObject : public GameObject{
    public:
        MovingObject(BasicsBlock* bb, Camera* camera, Shape* shape, float initial_pos[3],std::string* v, std::string* f);
        void Update() override;
        float test_speed = 3;
        std::string* shaderUniform;
        float light = 1;
};
