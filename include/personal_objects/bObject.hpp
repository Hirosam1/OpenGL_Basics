#pragma once
#include "game_object/GameObject.hpp"
#include "deque"
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


//Temporaly class that controlls the camera
class bObject : public GameObject{
    public:
     bObject(BasicsBlock* bc, Camera* m_camera ,float initial_pos[3]);

    glm::vec3 camera_front;
    float lastX, lastY;
    double pitch = 0;
    double yaw;
    int test_speed =3;
    float sensitivity;
    float fov;

    bool didExit;
    bool firstMouse = true;
    long long CurrentPhysMem;
    
    bool f1KeyRealeased = true;
    GLenum show_cursor = GLFW_CURSOR_DISABLED;
    bool show_another_window = false;

    void Update() override;
    void Ready() override;
    private:
        std::vector<GameObject*>::iterator obj_iterator;
        std::deque<char*> *m_deque_test;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        void CalculateCam();
        void RenderGUI();
};
