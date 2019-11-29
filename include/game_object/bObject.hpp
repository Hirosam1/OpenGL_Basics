#include "game_object/GameObject.hpp"

//Temporaly class that controlls the camera
class bObject : public GameObject{
    public:
     bObject(BasicsBlock* bc, Camera* m_camera ,float initial_pos[3]);
    void Update() override;
    private:
        glm::vec3 camera_front;
        float lastX, lastY;
        double pitch = 0;
        double yaw;
        int test_speed =3;
        float sensitivity;
        bool firstMouse = true;
};
