#include"personal_objects/all_personal.hpp"

GameObject* GameObjectFactory::GetObjectFromID(unsigned int id, BasicsBlock* basic_block, Camera* m_camera,Model* m_model,float initial_pos[3], Shader* m_shader){
    GameObject* go = nullptr;
    switch(id){
        default:
            std::cout<<"Can't find object with this id!\n";
            break;
        case 0:
            std::cout<<"Can't load game object with id 0, that is the default id\n";
        case aObject::go_id:
            go = new aObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case bObject::go_id:
            go = new bObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case cObject::go_id:
            go = new cObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case NoBahaviorObject::go_id:
            go = new NoBahaviorObject(basic_block,m_camera,m_model,initial_pos,m_shader);
        case PulsingLight::go_id:
            go = new PulsingLight(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
    }

    return go;
}