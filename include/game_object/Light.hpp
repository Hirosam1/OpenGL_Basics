#pragma once
#include <glm/glm.hpp>
#include "game_object/GameObject.hpp"

class GameManager;

class Light : public GameObject{
    public:
        friend GameManager;
        Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3],std::string vert, std::string frag ,float light_color[3],float light_intensity = 1.0);
        Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3],std::string vert, std::string frag ,float light_intensity = 1.0);
        Light(BasicsBlock* bb, Camera* m_camera, float initial_pos[3],float light_intensity = 1.0);
        glm::vec3 light_color;
        float* light_pos;
        float light_intensity;
        glm::vec3 light_ambient;
        glm::vec3 light_specular;
    protected:
        //Handles buffering of shader of given GameObject
        virtual void LightBuffering(GameObject* go) = 0;
        //Buffer of the lamp game object, this will render the light game object, so it can appear on the scene
        void LampColorBuffering();
        void Update() override;
};

class PointLight : public Light{
    public:
        PointLight(BasicsBlock* bb, Camera* m_camera,Model* model,float initial_pos[3], std::string vert, std::string frag, int index,float linear = 0.45f, float quadratic = 0.23f, float constant = 1.0f);
        float constant;
        float linear;
        float quadratic;
        //Index of the n point lights
        int index;
        
    private:
        void LightBuffering(GameObject *go) override;
        std::string LightPrefix;
};

class DirLight : public Light{
    public:
        DirLight(BasicsBlock* bb, Camera* m_camera,Model* model,float initial_pos[3], std::string vert, std::string frag, float direction[3]);
        DirLight(BasicsBlock* bb, Camera* m_camera,Model* model,float initial_pos[3], std::string vert, std::string frag);
        float* direction;
    private:
        void LightBuffering(GameObject *go) override;
};

class SpotLight : public Light{
    public:
        SpotLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], std::string vert, std::string frag, float direction[3]);
        SpotLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], std::string vert, std::string frag);
        SpotLight(BasicsBlock* bb, Camera* m_camera, float initial_pos[3], float direction[3]);
        float* direction;
    private:
        void LightBuffering(GameObject* go) override;
};