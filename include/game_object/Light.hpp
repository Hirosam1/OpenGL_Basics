#pragma once
#include <glm/glm.hpp>
#include "game_object/GameObject.hpp"
#include "game_object/Scene.hpp"

class GameManager;

struct LightElements{
    float* light_direction;
    bool light_direction_is_position = false;
    glm::vec3 light_color;
    float light_intensity = 1.0;
};


/*It is a light object
    It works with a default shader, it updates uniforms of each game object
    it uses phong lighting*/
class Light : public GameObject{
    public:
        friend GameManager;
        Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3],Shader* m_shader ,float light_color[3],float light_intensity = 1.0);
        Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3],Shader* m_shader ,float light_intensity = 1.0);
        Light(BasicsBlock* bb, Camera* m_camera,Model* model, float initial_pos[3] ,float light_intensity = 1.0);
        Light(BasicsBlock* bb, Camera* m_camera, float initial_pos[3],float light_intensity = 1.0);
        glm::vec3 light_color;
        float* light_pos;
        float light_intensity;
        glm::vec3 light_ambient;
        glm::vec3 light_specular;
    protected:
        //Handles buffering of shader of given GameObject
        virtual void LightBuffering() = 0;
        //Buffer of the lamp game object, this will render the light game object, so it can appear on the scene
        void LampColorBuffering();
        void Update() override;
};

class PointLight : public Light{
    public:
        PointLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader, float direction[3] = nullptr);
        PointLight(BasicsBlock* bb, Camera* m_camera, Model* model,float initial_pos[3], Shader* m_shader, int index,float linear = 0.12f, float quadratic = 0.04f, float constant = 1.0f);
        float constant;
        float linear;
        float quadratic;
        //Index of the n point lights
        int index;
    private:
        void LightBuffering() override;
        std::string LightPrefix;
};

class DirLight : public Light{
    public:
        DirLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader, float direction[3]);
        DirLight(BasicsBlock* bb, Camera* m_camera,Model* model,float direction[3], Shader* m_shader);
        DirLight(BasicsBlock* bb, Camera* m_camera, float direction[3]);
        float* direction;
    private:
        void LightBuffering() override;
};

class SpotLight : public Light{
    public:
        SpotLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader, float direction[3]);
        SpotLight(BasicsBlock* bb, Camera* m_camera, Model* model, float initial_pos[3], Shader* m_shader);
        SpotLight(BasicsBlock* bb, Camera* m_camera, float initial_pos[3], float direction[3]);
        float* direction;
        float constant = 1;
        float linear = 0.12;
        float quadratic = 0.09;
        float cutoff;
        float outer_cutoff;
    private:
        void LightBuffering() override;
};

