#include "game_object/GameObject.hpp"

class bObject : public GameObject{
    public:
     bObject(Window* aWindow,InputManager* m_input, Time* m_time, Camera* m_camera ,float initial_pos[3]);
    void Update() override;
    private:
        int test_speed =3;
};
