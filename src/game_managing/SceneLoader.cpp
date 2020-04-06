#include "game_managing/SceneLoader.hpp"

enum SceneReaderState : char{
    waiting = 0,
    addingGO,
    addingLight,
    addingOpaque,
    addingCamera,
    addingShader,
    addingModel,
    addingTexture,
    addingCubeMap
};


char waitingState(char current_state, std::string line, std::string* output);
char addingGOState(char current_state, std::string line, unsigned int object_id, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data);
char addingLightState(char current_state, std::string line);
char addingOpaqueState(char current_state, std::string line);
char addingCameraState(char current_state, std::string line);
char addingShaderState(char current_state, std::string line);
char addingModelState(char current_state, std::string line);

GameObjectElements goElements;

void SceneLoader::LoadSceneFromFile(std::string scene_path, BasicsBlock* basic_block,SceneData* scene_data){
    int current_state = SceneReaderState::waiting;
    std::ifstream infile(scene_path);
    std::string line;
    std::string output;
    Model* box = new Model("models/box/Box.obj");
    scene_data->loaded_models["box"] = box;

    while(std::getline(infile,line)){
        int e = line.find("#");
        if(e != std::string::npos){
            line.erase(e,line.length());
        }
        std::cout<<"current state -> " << current_state << "\n";
        switch(current_state){
            case SceneReaderState::waiting:
                current_state = waitingState(current_state,line,&output);
                break;
            case SceneReaderState::addingGO:
                GameObject* go;
                current_state = addingGOState(current_state,line,std::stoi(output),go,basic_block,scene_data);
                break;
        }

    }
}

void SceneLoader::Testetemplates(BasicsBlock* bb ,Camera* main_camera){
    GameObjectFactory::GetObjectFromID(4,bb,main_camera,nullptr,new float[3]{0,0,0},nullptr);
}

char waitingState(char current_state, std::string line, std::string* output){
    if (line.find("+") != std::string::npos){
        std::vector<std::string> tokens = FileManagementTools::ParseLine(line," ");
            if(tokens[1] == "GO"){
                if(tokens.size()>1){
                    *output = tokens[2];
                    goElements.initial_pos =nullptr;
                    goElements.m_camera = nullptr;
                    goElements.m_shader = nullptr;
                    goElements.model =  nullptr;
                    return SceneReaderState::addingGO;
                }else{
                    return current_state;
                }
            }
        }
    return current_state;
}


char addingGOState(char current_state, std::string line, unsigned int object_id, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data){
    int e;
    
    std::string parameters= "";
    char aux[2] = {'\t','\n'};
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    if((e = line.find(">")) != std::string::npos){
        line.erase(0,e+1);
        std::vector<std::string> tokens = FileManagementTools::ParseLine(line," ");
        parameters = line.substr(line.find(tokens[0]),line.length());
        if(tokens.size() >1){
           if(tokens[0] == "camera"){
               if(parameters == "main_camera"){
                   goElements.m_camera = basic_block->global_data.main_camera;
               }
           }else if(tokens[0] == "model"){
                std::regex_search(parameters,matches,reg);
                if (matches.ready()){
                    if(scene_data->loaded_models.count(matches.str(1))){

                        goElements.model = scene_data->loaded_models[matches.str(1)];
                    }else{
                        std::cout<<"FILE::INTEPRETER:ERROR -> Cannot find loaded model \""<<matches.str(1)<<"\"\n";
                    }
                    
                }
                else{
                    std::cout<<"FILE::INTEPRETER:ERROR -> Cant match \"name of model\"\n";
                }
           }else if(tokens[0] == "position"){
               if(tokens.size() > 3){
                   float* position = new float[3];
                   position[0] = std::stof(tokens[1]);
                   position[1] = std::stof(tokens[2]);
                   position[2] = std::stof(tokens[3]);
                   goElements.initial_pos = position;
               }
           }else if(tokens[0] == "shader"){
               std::regex_search(parameters,matches,reg);
                if(basic_block->global_data.all_shaders.count(matches.str(1))){
                    goElements.m_shader = basic_block->global_data.all_shaders[matches.str(1)];
                }else{
                    std::cout<<"FILE::INTEPRETER:ERROR -> Cannot find loaded shader \""<<matches.str(1)<<"\"\n";
                }
           }
        }
        
    }else if( (e = line.find("|")) != std::string::npos){
            parameters = line.substr(e,line.length());
            gameObject_output = GameObjectFactory::GetObjectFromID(object_id,basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader);
            std::regex_search(parameters,matches,reg);
            if(matches.ready()){
            gameObject_output->object_name = matches.str(1);
            }
            scene_data->AllObjects.push_back(gameObject_output);
            return SceneReaderState::waiting;
        }
    return current_state;
}