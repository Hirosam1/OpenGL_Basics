#include "game_object/GameObject.hpp"

//Temporaly class that controlls the camera
class bObject : public GameObject{
    public:
     bObject(Window* aWindow,InputManager* m_input, Time* m_time, Camera* m_camera ,float initial_pos[3]);
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
