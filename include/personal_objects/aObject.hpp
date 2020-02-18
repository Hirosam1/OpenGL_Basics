#pragma once
#include<iostream>
#include "game_object/GameObject.hpp"
#include "personal_objects/bObject.hpp"

class aObject : public GameObject{
    public:   
        aObject(BasicsBlock* bc,Camera* m_camera,float initial_pos[3]);      
    private:
        glm::vec3 camera_front;
        bObject* GUIObject;
        float lastX, lastY;
        double pitch = 0;
        double yaw;
        float sensitivity;
        float fov;

        bool didExit;
        bool firstMouse = true;
        long long CurrentPhysMem;
        void Update() override;
        void Ready() override;
        void CalculateCam();
        unsigned int test_speed = 3;

};
