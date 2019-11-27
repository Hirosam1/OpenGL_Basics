#include "game_object/aObject.hpp"

//That is not supposed to be a game engine class
aObject::aObject(Window* aWindow,InputManager* m_input, Time* m_time, 
Shape* m_shape,Camera* m_camera ,float initial_pos[3], std::string* vert_shader_path,std::string* frag_shader_path):GameObject
(aWindow,m_input,m_time,m_camera,m_shape,initial_pos,vert_shader_path,frag_shader_path){

}
void aObject::Update(){
    


}
