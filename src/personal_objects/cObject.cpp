#include"personal_objects/cObject.hpp"

cObject::cObject(BasicsBlock* bb, Camera* c, Model* m, float ip[3], std::string vs, std::string fs,float size):GameObject(bb,c,m,ip,vs,fs){
    model_mat  = glm::scale(model_mat,glm::vec3(size,size,size));
}
void cObject::Update(){


}