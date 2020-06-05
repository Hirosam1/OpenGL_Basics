#include "game_managing/SceneLoader.hpp"

enum SceneReaderState : char{
    waiting = 0,
    addingGO,
    addingLight,
    addingOpaque,
    addingCamera,
};


char waitingState(char current_state, std::string line, std::string* output);
char addingGOState(char current_state, std::string line, unsigned int object_id, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data);
char addingLightState(char current_state, std::string line, std::string light_type, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data);
char addingOpaqueState(char current_state, std::string line);
char addingCameraState(char current_state, std::string line);
char addingShaderState(char current_state, std::string line);
char addingModelState(char current_state, std::string line);

void ClearGoELemetns();

//Elements to be used on the game Object creation
GameObjectElements goElements;
LightElements light_elemtents;
int line_number = 0;
void SceneLoader::LoadSceneFromFile(std::string scene_path, BasicsBlock* basic_block,SceneData* scene_data){
    int current_state = SceneReaderState::waiting;
    std::ifstream infile(scene_path);
    std::string line;
    std::string output;
    GameObject* go;
    //This is only for test ============================
    //Shader* shader = new Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/BasicLight.frag");
    //Shader* lamp_shader = new Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/lamp.frag");
    //Shader* shader_refrag = new Shader("shaders/vertex_shaders/MVP_texture_vertex.vert","shaders/fragment_shaders/Refraction.frag");
    //basic_block->global_data.all_shaders["lamp shader"] = lamp_shader;
    //basic_block->global_data.all_shaders["refraction"] = shader_refrag;
    //basic_block->global_data.all_shaders["basic light"] = shader;
    //End test =========================================

    while(std::getline(infile,line)){
        line_number++;
        int e = line.find("#");
        if(e != std::string::npos){
            line.erase(e,line.length());
        }
        //this switch controls the Scene loader state machine
        switch(current_state){
            //Waiting state, waits for a new order, like adding game Object, Light, CubeMap, etc...
            case SceneReaderState::waiting:
                current_state = waitingState(current_state,line,&output);
                break;
            //This states creates a normal game object it needs multiple lines read
            case SceneReaderState::addingGO:
                current_state = addingGOState(current_state,line,std::stoi(output),go,basic_block,scene_data);
                break;
            case SceneReaderState::addingLight:
                current_state = addingLightState(current_state,line,output,go,basic_block,scene_data);
                break;
        }

    }
}

void SceneLoader::Testetemplates(BasicsBlock* bb ,Camera* main_camera){
    GameObjectFactory::GetObjectFromID(4,bb,main_camera,nullptr,new float[3]{0,0,0},nullptr);
}

char waitingState(char current_state, std::string line, std::string* output){
    //Resets the elements from goElemnts
    ClearGoELemetns();
    //If it finds a "+" sign it will check what type of addtion is to be executed
    if (line.find("+") != std::string::npos){
        std::vector<std::string> tokens = FileManagementTools::ParseLine(line," ");
            //If it is GO, that means we need to create a game object
            if(tokens[1] == "GO"){
                if(tokens.size()>1){
                    //It register the id of the game object
                    *output = tokens[2];
                    return SceneReaderState::addingGO;
                }else{
                    return current_state;
                }
            }else if(tokens[1] == "light"){
                if(tokens[2] == "directional"){
                    *output = "directional";
                    return SceneReaderState::addingLight;
                }else if(tokens[2] == "point"){
                    *output = "point";
                    return SceneReaderState::addingLight;
                }else if(tokens[2] == "spot"){
                    *output = "spot";
                    return SceneReaderState::addingLight;
                }else{
                     std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cant match \""<< tokens[2] <<"\"\n";
                }
            }
        }
    return current_state;
}


char addingGOState(char current_state, std::string line, unsigned int object_id, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data){
    int e;
    
    std::string parameters= "";
    //Regex to catch elements in between ""
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    //Searches for > element, that is a addition of a game object propirty, that wil be added to goElements
    if((e = line.find(">")) != std::string::npos){
        line.erase(0,e+1);
        //Parse the line by the whitespace char
        std::vector<std::string> tokens = FileManagementTools::ParseLine(line," ");
        //It also gets the parameters as one string, in case we need string handling
        parameters = line.substr(line.find(tokens[1]),line.length());
        if(tokens.size() >1){
            //NECESSARY sets what camera to use
           if(tokens[0] == "camera"){
               // sets the camera as the main one, setted on global settings (maybe should be scene NOT global)
               if(parameters == "main_camera"){
                   goElements.m_camera = scene_data->main_camera;
               }
               //defines the model to be used
           }else if(tokens[0] == "model"){
               //Apply the regex rule
                std::regex_search(parameters,matches,reg);
                if (matches.ready()){
                    //Searches if it is in loaded models
                    if(scene_data->loaded_models.count(matches.str(1))){
                        //If it is give it to goElements
                        goElements.model = scene_data->loaded_models[matches.str(1)];
                    }else{
                        if(basic_block->global_data.models_path.count(matches.str(1))){
                            Model* loaded_model = new Model(basic_block->global_data.models_path[matches.str(1)]);
                            scene_data->loaded_models[matches.str(1)] = loaded_model;
                            goElements.model = loaded_model;
                        }else{
                            std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find loaded model \""<<matches.str(1)<<"\"\n";
                        }
                    }
                    
                }
                else{
                    std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cant match \"name of model\"\n";
                }
            //NECESSARY (Should it be?) sets the initial position
           }else if(tokens[0] == "position"){
               if(tokens.size() > 3){
                   float* position = new float[3];
                   position[0] = std::stof(tokens[1]);
                   position[1] = std::stof(tokens[2]);
                   position[2] = std::stof(tokens[3]);
                   goElements.initial_pos = position;
               }
               
            //Sets shader to be used in this model, similarly to model, it searches if the shader metioned exists
           }else if(tokens[0] == "shader"){
               std::regex_search(parameters,matches,reg);
                if(basic_block->global_data.all_shaders.count(matches.str(1))){
                    goElements.m_shader = basic_block->global_data.all_shaders[matches.str(1)];
                }else{
                    std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find loaded shader \""<<matches.str(1)<<"\"\n";
                }
           }else if(tokens[0] == "size"){
                if(tokens.size() > 3){
                   float* size = new float[3];
                   size[0] = std::stof(tokens[1]);
                   size[1] = std::stof(tokens[2]);
                   size[2] = std::stof(tokens[3]);
                   goElements.size = glm::vec3(glm::make_vec3(size));
               }else if (tokens.size() > 1){
                    float size;
                    size = std::stof(tokens[1]);
                    goElements.size = glm::vec3(size);
               }
           }
        }
        //In the LAST line, it searchrs for a | the very next element is the name of given object using ""
    }else if( (e = line.find("|")) != std::string::npos){
            parameters = line.substr(e,line.length());
            if(goElements.initial_pos != nullptr){
                if(goElements.m_camera == nullptr){
                    goElements.m_camera =  scene_data->main_camera;
                }
                gameObject_output = GameObjectFactory::GetObjectFromID(object_id,basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader);
                //ClearGoELemetns();
                if(gameObject_output != nullptr){
                    std::regex_search(parameters,matches,reg);
                    //Apply scaling operation
                    gameObject_output->model_mat = glm::scale(gameObject_output->model_mat,goElements.size);
                    if(matches.ready()){
                    gameObject_output->object_name = matches.str(1);
                    }
                    scene_data->AllObjects.push_back(gameObject_output);
                }
                return SceneReaderState::waiting;
            }else{
                std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Missing Game Object Argumetns, did select a initial position? \n";
            }
        }
    return current_state;
}

char addingLightState(char current_state, std::string line, std::string light_type, GameObject* gameObject_output, BasicsBlock* basic_block, 
    SceneData* scene_data){
    int e;
    std::string parameters= "";
    //Regex to catch elements in between ""
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    //Searches for > element, that is a addition of a game object propirty, that wil be added to goElements
    if((e = line.find(">")) != std::string::npos){
        line.erase(0,e+1);
        //Parse the line by the whitespace char
        std::vector<std::string> tokens = FileManagementTools::ParseLine(line," ");
        //It also gets the parameters as one string, in case we need string handling
        parameters = line.substr(line.find(tokens[1]),line.length());
        if(tokens.size() >1){
            //NECESSARY sets what camera to use
           if(tokens[0] == "camera"){
               // sets the camera as the main one, setted on global settings (maybe should be scene NOT global)
               if(parameters == "main_camera"){
                   goElements.m_camera = scene_data->main_camera;
               }
               //defines the model to be used
           }else if(tokens[0] == "model"){
               //Apply the regex rule
                std::regex_search(parameters,matches,reg);
                if (matches.ready()){
                    //Searches if it is in loaded models
                    if(scene_data->loaded_models.count(matches.str(1))){
                        //If it is give it to goElements
                        goElements.model = scene_data->loaded_models[matches.str(1)];
                    }else{
                        if(basic_block->global_data.models_path.count(matches.str(1))){
                            Model* loaded_model = new Model(basic_block->global_data.models_path[matches.str(1)]);
                            scene_data->loaded_models[matches.str(1)] = loaded_model;
                            goElements.model = loaded_model;
                        }else{
                            std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find loaded model \""<<matches.str(1)<<"\"\n";
                        }
                    }
                    
                }
                else{
                    std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cant match \"name of model\"\n";
                }
            //NECESSARY (Should it be?) sets the initial position
           }else if(tokens[0] == "position"){
               if(tokens.size() > 3){
                   float* position = new float[3];
                   position[0] = std::stof(tokens[1]);
                   position[1] = std::stof(tokens[2]);
                   position[2] = std::stof(tokens[3]);
                   goElements.initial_pos = position;
               }
               
            //Sets shader to be used in this model, similarly to model, it searches if the shader metioned exists
           }else if(tokens[0] == "size"){
                if(tokens.size() > 3){
                   float* size = new float[3];
                   size[0] = std::stof(tokens[1]);
                   size[1] = std::stof(tokens[2]);
                   size[2] = std::stof(tokens[3]);
                   goElements.size = glm::vec3(glm::make_vec3(size));
               }else if (tokens.size() > 1){
                    float size;
                    size = std::stof(tokens[1]);
                    goElements.size = glm::vec3(size);
               }
           }else if(tokens[0] == "shader"){
               std::regex_search(parameters,matches,reg);
                if(basic_block->global_data.all_shaders.count(matches.str(1))){
                    goElements.m_shader = basic_block->global_data.all_shaders[matches.str(1)];
                }else{
                    std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find loaded shader \""<<matches.str(1)<<"\"\n";
                }
           }else if(tokens[0] == "direction"){
               if(tokens.size() > 3){
                   std::string to_remove = " ";
                   FileManagementTools::RemoveFromString(parameters,to_remove.data());
                   float* direction = new float[3];
                   direction[0] = std::stof(tokens[1]);
                   direction[1] = std::stof(tokens[2]);
                   direction[2] = std::stof(tokens[3]);
                   light_elemtents.light_direction = direction;
            }else if(parameters == "this_position"){
                light_elemtents.light_direction_is_position = true;
            }
        //In the LAST line, it searchrs for a | the very next element is the name of given object using ""
        }else if(tokens[0] == "color"){
            if(tokens.size() > 3){
                float* color = new float[3];
                color[0] = std::stof(tokens[1]);
                color[1] = std::stof(tokens[2]);
                color[2] = std::stof(tokens[3]);
                light_elemtents.light_color = glm::vec3(glm::make_vec3(color));
            }
        }else if(tokens[0] == "intensity"){
            if(tokens.size() > 1){
                float intensity;
                intensity = std::stof(tokens[1]);
                light_elemtents.light_intensity = intensity;
            }
        }
        }
    }else if( (e = line.find("|")) != std::string::npos){
            parameters = line.substr(e,line.length());
            if(goElements.initial_pos != nullptr){
                if(goElements.m_camera == nullptr){
                    goElements.m_camera =  scene_data->main_camera; 
                }
                if(light_type == "directional"){
                    if(light_elemtents.light_direction != nullptr || light_elemtents.light_direction_is_position){
                        if(light_elemtents.light_direction_is_position){
                            gameObject_output = new DirLight(basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader,light_elemtents.light_direction);
                            dynamic_cast<DirLight*>(gameObject_output)->direction = dynamic_cast<DirLight*>(gameObject_output)->light_pos;
                        }
                        else{
                            gameObject_output = new DirLight(basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader,light_elemtents.light_direction);
                        }
                    }
                }else if(light_type == "point"){
                    gameObject_output = new PointLight(basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader,scene_data->n_point_lights++);
                }else if(light_type == "spot"){
                    if(light_elemtents.light_direction != nullptr || light_elemtents.light_direction_is_position){
                        if(light_elemtents.light_direction_is_position){
                            gameObject_output = new SpotLight(basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader,light_elemtents.light_direction);
                            dynamic_cast<SpotLight*>(gameObject_output)->direction = dynamic_cast<DirLight*>(gameObject_output)->light_pos;
                        }
                        else{
                            gameObject_output = new SpotLight(basic_block,goElements.m_camera,goElements.model,goElements.initial_pos,goElements.m_shader,light_elemtents.light_direction);
                        }
                    }
                }
                if(gameObject_output == nullptr){
                     std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Missing Game Light Argument, did you select direction? \n";
                }else{
                    gameObject_output->model_mat = glm::scale(gameObject_output->model_mat,goElements.size);
                    dynamic_cast<Light*>(gameObject_output)->light_color = light_elemtents.light_color;
                    dynamic_cast<Light*>(gameObject_output)->light_intensity = light_elemtents.light_intensity;
                    std::regex_search(parameters,matches,reg);
                    if(matches.ready()){
                        gameObject_output->object_name = matches.str(1);
                    }
                    scene_data->AllObjects.push_back(gameObject_output);
                    scene_data->AllLights.push_back(dynamic_cast<Light*>(gameObject_output));
                }
            }else{
                std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Missing Game Object Argumetns, did you select a camera, initial position? \n";
            }
                return SceneReaderState::waiting;
            }
    return current_state;
}

    


void ClearGoELemetns(){
    goElements.basic_block = nullptr;
    goElements.initial_pos = nullptr;
    goElements.m_camera = nullptr;
    goElements.m_shader = nullptr;
    goElements.model = nullptr;
    goElements.size = glm::vec3(1.0);

    light_elemtents.light_direction = nullptr;
    light_elemtents.light_direction_is_position = false;
    light_elemtents.light_color = glm::vec3(1.0);
    light_elemtents.light_intensity = 1.0;
}