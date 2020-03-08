#include"personal_objects/cObject.hpp"

cObject::cObject(BasicsBlock* bb, Camera* c, Model* m, float ip[3], Shader* m_shader,float size):GameObject(bb,c,m,ip,m_shader){
    model_mat  = glm::scale(model_mat,glm::vec3(size,size,size));
}
void cObject::Update(){


}