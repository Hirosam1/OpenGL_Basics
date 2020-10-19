#include "personal_objects/InstancingObjects.hpp"

InstancingObjects::InstancingObjects(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader): GameObject(basic_block,m_camera,model,initial_pos,m_shader){
                                    
}

void InstancingObjects::Ready(){
    int amount = 100;
    int index = 0;
    float offset = 0.5;
    for(int y = 0; y < 10; y += 1)
    {
        for(int x = 0; x < 10; x += 1)
        {
            glm::vec2 traslation;
            traslation.x = (float)x * offset;
            traslation.y = (float)y * offset;
            translations[index++] = traslation;
        }
    }

    this->MakeInstaced((float*)&translations[0],100,2);
}

void InstancingObjects::Update(){
    
}