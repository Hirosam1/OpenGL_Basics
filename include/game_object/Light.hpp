#pragma once
#include <glm/glm.hpp>
#include "game_object/GameObject.hpp"

class Light : public GameObject{
    public:
        Light(BasicsBlock* bb, Camera* m_camera,Shape* shape, float initial_pos[3],std::string* vert, std::string* frag ,float light_color[3],float light_intensity = 1.0);
        Light(BasicsBlock* bb, Camera* m_camera,Shape* shape, float initial_pos[3],std::string* vert, std::string* frag ,float light_intensity = 1.0);
        glm::vec3 light_color;
        float* light_pos;
        float light_intensity;
        glm::vec3 light_ambient;
        glm::vec3 light_specular;
        virtual void LightBuffering(GameObject* go) = 0;
        void Update() override;
};

class PointLight : public Light{
    public:
        PointLight(BasicsBlock* bb, Camera* m_camera,Shape* shape,float initial_pos[3], std::string* vert, std::string* frag, float liniar = 0.12, float quadratic = 0.03, float constant = 1.0);
        float constant;
        float linear;
        float quadratic;
    private:
        void LightBuffering(GameObject *go) override;
};

class DirLight : public Light{
    public:
        DirLight(BasicsBlock* bb, Camera* m_camera,Shape* shape,float initial_pos[3], std::string* vert, std::string* frag, float direction[3]);
        DirLight(BasicsBlock* bb, Camera* m_camera,Shape* shape,float initial_pos[3], std::string* vert, std::string* frag);
        glm::vec3 direction;
    private:
        void LightBuffering(GameObject *go) override;
};