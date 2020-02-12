#include "personal_objects/aObject.hpp"

//That is not supposed to be a game engine class
aObject::aObject(BasicsBlock* bc, 
Camera* m_camera,Shape* m_shape,float initial_pos[3], std::string* vert_shader_path,std::string* frag_shader_path):GameObject
(bc,m_camera,m_shape,initial_pos,vert_shader_path,frag_shader_path){
}
void aObject::Update(){
    std::cout<< this->object_name <<" -> " << 1/(float)(m_time->delta_time)<<"\n";
}
