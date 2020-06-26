#include"game_managing/ObjectFactory.hpp"
#include "personal_objects/aObject.hpp"
#include "personal_objects/bObject.hpp"
#include "personal_objects/cObject.hpp"
#include "personal_objects/NoBehaviorObject.hpp"
#include "personal_objects/PulsingLight.hpp"
//This file should be generated procedually 
enum GameObjectsID : unsigned int{
    aOgjectID = 1,
    bObjectID,
    cObjectID,
    NoBahaviorObjectID,
    PulsingLightID
};


void ObjectsManager::InitializeAllObjects(){

}

GameObject* GameObjectFactory::GetObjectFromID(unsigned int id, BasicsBlock* basic_block, Camera* m_camera,Model* m_model,float initial_pos[3], Shader* m_shader){
    GameObject* go = nullptr;
    switch(id){
        default:
            std::cout<<"Can't find object with this id! -->" << id<< "\n";
            break;
        case 0:
            std::cout<<"Can't load game object with id 0, that is the default id\n";
        case GameObjectsID::aOgjectID :
            go = new aObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case GameObjectsID::bObjectID:
            go = new bObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case GameObjectsID::cObjectID :
            go = new cObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case GameObjectsID::NoBahaviorObjectID:
            go = new NoBahaviorObject(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
        case GameObjectsID::PulsingLightID:
            go = new PulsingLight(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;
    }

    return go;
}

Texture* TextureFactory::GetObjectFromID(unsigned id, std::string texture_path){
    return nullptr;
}