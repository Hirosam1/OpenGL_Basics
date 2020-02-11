#include"personal_objects/cObject.hpp"

cObject::cObject(BasicsBlock* bb, Camera* c, Shape* s, float ip[3], std::string* vs, std::string* fs,float size):GameObject(bb,c,s,ip,vs,fs){
    model  = glm::scale(model,glm::vec3(size,size,size));
}

void cObject::Update(){


}