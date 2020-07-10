#pragma once
#include "game_object/GameObject.hpp"
#include "game_object/Light.hpp"
#include "deque"
#include <vector>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "game_object/Scene.hpp"

//Temporaly class that controlls the camera
class bObject : public GameObject{
    public:
    //static constexpr unsigned int go_id = 2;
    bObject(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader);
    bool didExit;
    bool firstMouse = true;
    long long CurrentPhysMem;
    
    bool f1KeyRealeased = true;
    bool enterReleased = false;
    GLenum show_cursor = GLFW_CURSOR_DISABLED;
    bool show_another_window = false;
    std::string scene_path = "scenes/scene_boxes.snsc";
    float timeElpased = 0;
    float FPS;
    void Update() override;
    void Ready() override;
    private:
        
        std::vector<GameObject*>::iterator obj_iterator;
        std::deque<char*> *m_deque_test;

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        void CalculateCam();
        void RenderGUI();
};
