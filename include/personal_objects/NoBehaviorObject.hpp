#include "game_object/GameObject.hpp"

class NoBahaviorObject : public GameObject{
    public:
        NoBahaviorObject(BasicsBlock* bb, Camera* camera, Mesh* shape, float initial_pos[3],std::string* v, std::string* f);
        void Update() override;

};
