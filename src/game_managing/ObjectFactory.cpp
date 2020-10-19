#include"game_managing/ObjectFactory.hpp"
#include "personal_objects/aObject.hpp"
#include "personal_objects/bObject.hpp"
#include "personal_objects/cObject.hpp"
#include "personal_objects/NoBehaviorObject.hpp"
#include "personal_objects/PulsingLight.hpp"
#include "personal_objects/InstancingObjects.hpp"
//This file should be generated procedually 
enum GameObjectsID : unsigned int{
    aOgjectID = 1,
    bObjectID,
    cObjectID,
    NoBahaviorObjectID,
    PulsingLightID,
    InstancingObjectsID

};

enum TextureID : unsigned int{
    DiffuseID = 1,
    SpecularID,
    ScreenID,
    CubeMapID,
    ToonTextureID
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
        case GameObjectsID::InstancingObjectsID:
            go = new InstancingObjects(basic_block,m_camera,m_model,initial_pos,m_shader);
            break;

    }

    return go;
}

Texture* TextureFactory::GetObjectFromID(unsigned id, std::string texture_path){
    Texture* tex = nullptr;
    switch (id)    {
        default:
            std::cout<<"Can't load texture object with this id! -->" << id<< "\n";
            break;
        case 0:
            std::cout<<"Can't load texture object with ID 0, that is the default ID\n";
            break;
        case TextureID::DiffuseID:
            tex = new DiffuseTexture(texture_path);
            break;
        case TextureID::SpecularID:
            tex = new SpecularTexture(texture_path);
            break;
        case TextureID::ScreenID:
            tex = new ScreenTexture();
            break;
        case TextureID::CubeMapID:
            tex = new CubeMapTexture(texture_path);
            break;
        case TextureID::ToonTextureID:
            tex =  new ToonTexture(texture_path);
            break;

    }

    return tex;
}