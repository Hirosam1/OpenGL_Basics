#include "personal_objects/InstancingObjects.hpp"

InstancingObjects::InstancingObjects(BasicsBlock* bb, Camera* camera, Model* model, float initial_pos[3],Shader* m_shader): GameObject(basic_block,m_camera,model,initial_pos,m_shader){

}

void InstancingObjects::Ready(){
    int index = 0;
    float offset = 0.1f;

    for(int y = -10; y < 10; y += 2){
        for(int x = -10; x < 10; x += 2){
                glm::vec2 translation;
                translation.x = (float)x /10.0f + offset;
                translation.y = (float)y /10.0f + offset;
                translations[index++] = translation;

        }
    }
    this->MakeInstaced((float*) &translations[0],100,2);
}

void InstancingObjects::Update(){
    
}