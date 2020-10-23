#include "personal_objects/InstancingObjects.hpp"

InstancingObjects::InstancingObjects(BasicsBlock* basic_block,Camera* m_camera,Model* model,float initial_pos[3],Shader* m_shader): GameObject(basic_block,m_camera,model,initial_pos,m_shader){
                                    
}

void InstancingObjects::Ready(){
    amount_per_d = 50;
    int index = 0;
    float offset = 2.3;
    translations = new glm::vec2[amount_per_d * amount_per_d];
    for(int y = 0; y < amount_per_d; y += 1)
    {
        for(int x = 0; x < amount_per_d; x += 1)
        {
            glm::vec2 traslation;
            traslation.x = (float)x * offset;
            traslation.y = (float)y * offset;
            translations[index++] = traslation;
        }
    }

    this->MakeInstaced((float*)translations,amount_per_d * amount_per_d,2);
}

InstancingObjects::~InstancingObjects(){
    delete[] translations;
}

void InstancingObjects::Update(){
    m_shader->SetUniform1i(&amount_str,amount_per_d * amount_per_d);
}