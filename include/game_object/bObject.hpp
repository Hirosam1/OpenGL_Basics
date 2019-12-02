#include "game_object/GameObject.hpp"
#include "deque"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//Temporaly class that controlls the camera
class bObject : public GameObject{
    public:
     bObject(BasicsBlock* bc, Camera* m_camera ,float initial_pos[3]);
    void Update() override;
    private:
        std::deque<char*> *m_deque_test;
        glm::vec3 camera_front;
        float lastX, lastY;
        double pitch = 0;
        double yaw;
        int test_speed =3;
        float sensitivity;
        float fov;

        bool firstMouse = true;
        long long CurrentPhysMem;
        
};
