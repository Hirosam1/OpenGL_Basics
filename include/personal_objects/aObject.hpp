#pragma once
#include<iostream>
#include "game_object/GameObject.hpp"
#include "personal_objects/bObject.hpp"
#include "game_object/GameObject.hpp"
#include "personal_objects/all_personal.hpp"

class aObject : public GameObject{
    public:   
        aObject(BasicsBlock* bc,Camera* m_camera,float initial_pos[3]);
        const unsigned int go_id = 1; 
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
