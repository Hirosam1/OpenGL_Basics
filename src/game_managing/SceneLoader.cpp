#include "game_managing/SceneLoader.hpp"

enum SceneReaderState : char{
    waiting = 0,
    addingGO,
    addingLight,
    addingCamera,
    addingCubeMap
};


char waitingState(char current_state, std::string line, std::string* output);
char addingGOState(char current_state, std::string line, unsigned int object_id, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data);
char addingLightState(char current_state, std::string line, std::string light_type, GameObject* gameObject_output, BasicsBlock* basic_block, SceneData* scene_data);
//char addingOpaqueState(char current_state, std::string line);
char addingCameraState(char current_state, std::string line);
char addingShaderState(char current_state, std::string line);
char addingModelState(char current_state, std::string line);
char addingCubeMapState(char current_state, std::string line,BasicsBlock* basic_block, SceneData* scene_data);

bool MakeModel(BasicsBlock* basic_block, SceneData* scene_data, std::string parameters);
float* GetVec3(std::vector<std::string> tokens);
bool MakeShader(BasicsBlock* basic_block, SceneData* scene_data, std::string parameters);
Texture* MakeTexture(BasicsBlock* basic_block, SceneData* scene_data, std::string parameters, unsigned int id);

void ClearGoELemetns();

//Elements to be used on the game Object creation
GameObjectElements goElements;
LightElements light_elemtents;
SceneData* old_scene_d;
int line_number;
bool SceneLoader::LoadSceneFromFile(std::string scene_path, BasicsBlock* basic_block,SceneData* scene_data, SceneData* old_scene_data){
    old_scene_d = old_scene_data;
    line_number = 0;
    scene_data->scene_name = scene_path.substr(scene_path.find_last_of("/")+1,scene_path.length());
    int current_state = SceneReaderState::waiting;
    std::ifstream infile(scene_path);
    if(infile.fail()){
        return false;
    }
    std::string line;
    std::string output;
    GameObject* go;
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
            case SceneReaderState::addingCubeMap:
                current_state = addingCubeMapState(current_state, line, basic_block, scene_data);
                break;
        }

    }
    return true;
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
            }else if(tokens[1] == "CubeMap"){
                return SceneReaderState::addingCubeMap;
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
        if(tokens.size() > 1){
            //It also gets the parameters as one string, in case we need string handling
            parameters = line.substr(line.find(tokens[1]),line.length());
        }
        if(tokens.size() >0){
            //NECESSARY sets what camera to use
           if(tokens[0] == "camera"){
               // sets the camera as the main one, setted on global settings (maybe should be scene NOT global)
               if(parameters == "main_camera"){
                   goElements.m_camera = scene_data->main_camera;
               }
               //defines the model to be used
           }else if(tokens[0] == "model"){
              MakeModel(basic_block,scene_data,parameters);
            //NECESSARY (Should it be?) sets the initial position
           }else if(tokens[0] == "position"){
               if(tokens.size() > 3){
                   goElements.initial_pos = GetVec3(tokens);
               }
               
            //Sets shader to be used in this model, similarly to model, it searches if the shader metioned exists
           }else if(tokens[0] == "shader"){
               try{
                   MakeShader(basic_block,scene_data,parameters);
               }catch(std::exception &exp){
                    std::cout<<"Shader not loaded. Error at line " << line_number <<"\n";
                    Debug::WriteErrorLog(exp.what());
               }
           }else if(tokens[0] == "size"){
                if(tokens.size() > 3){
                   goElements.size = glm::vec3(glm::make_vec3(GetVec3(tokens)));
               }else if (tokens.size() > 1){
                    float size;
                    size = std::stof(tokens[1]);
                    goElements.size = glm::vec3(size);
               }
           }else if(tokens[0] == "make_opaque"){
               goElements.isOpaque = true;
           } else if(tokens[0] == "add_texture" && goElements.model != nullptr){
                std::string id = parameters.substr(parameters.find_last_of("\"") + 1, parameters.length());
                Texture* tex = MakeTexture(basic_block,scene_data,parameters,std::stoi(id));
                ///Only sets to the first model????
                goElements.model->meshes[0].textures.push_back(tex);
           }else{
                std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Unknown operator \""<<tokens[0]<<"\"\n";
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
                    if(goElements.isOpaque){
                        gameObject_output->isOpaque = true;
                        scene_data->AllOpaques.push_back(gameObject_output);
                    }
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
            //sets what camera to use
           if(tokens[0] == "camera"){
               // sets the camera as the main one, setted on global settings (maybe should be scene NOT global)
               if(parameters == "main_camera"){
                   goElements.m_camera = scene_data->main_camera;
               }
               //defines the model to be used
           }else if(tokens[0] == "model"){
               MakeModel(basic_block,scene_data,parameters);
            //NECESSARY (Should it be?) sets the initial position
           }else if(tokens[0] == "position"){
               if(tokens.size() > 3){
                   goElements.initial_pos = GetVec3(tokens);
               }
           }else if(tokens[0] == "size"){
                if(tokens.size() > 3){
                   goElements.size = glm::vec3(glm::make_vec3(GetVec3(tokens)));
               }else if (tokens.size() > 1){
                    float size;
                    size = std::stof(tokens[1]);
                    goElements.size = glm::vec3(size);
               }
               //Sets shader to be used in this model, similarly to model, it searches if the shader metioned exists
           }else if(tokens[0] == "shader"){
                try{
                   MakeShader(basic_block,scene_data,parameters);
               }catch(std::exception &exp){
                    std::cout<<"Shader not loaded. Error at line " << line_number <<"\n";
                    Debug::WriteErrorLog(exp.what());
               }
           //Sets the direction of the light, unessessary if it is a point light
           }else if(tokens[0] == "direction"){
               if(tokens.size() > 3){
                   std::string to_remove = " ";
                   FileManagementTools::RemoveFromString(parameters,to_remove.data());
                   light_elemtents.light_direction = GetVec3(tokens);
            //This  sets the direction equal to the objet position
            }else if(parameters == "this_position"){
                light_elemtents.light_direction_is_position = true;
            }
        //Sets the color of the light
        }else if(tokens[0] == "color"){
            if(tokens.size() > 3){
                light_elemtents.light_color = glm::vec3(glm::make_vec3(GetVec3(tokens)));
            }
         //Sets the intensity of the light
        }else if(tokens[0] == "intensity"){
            if(tokens.size() > 1){
                float intensity;
                intensity = std::stof(tokens[1]);
                light_elemtents.light_intensity = intensity;
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
                        scene_data->n_spot_lights++;
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
                std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Missing Game Object Argumetns, did you select a initial position? \n";
            }
                return SceneReaderState::waiting;
            }
    return current_state;
}

char addingCubeMapState(char current_state, std::string line,BasicsBlock* basic_block, SceneData* scene_data){
    std::string parameters= "";
    //Regex to catch elements in between ""
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    int e;
    //Searches for > element, that is a addition of a game object propirty, that wil be added to goElements
    if((e = line.find(">")) != std::string::npos){
        line.erase(0,e+1);
        //Parse the line by the whitespace char
        std::vector<std::string> tokens = FileManagementTools::ParseLine(line," ");
        //It also gets the parameters as one string, in case we need string handling
        parameters = line.substr(line.find(tokens[1]),line.length());
        if(tokens.size() >1){
            if(tokens[0] == "model"){
             MakeModel(basic_block,scene_data,parameters);
            //NECESSARY (Should it be?) sets the initial position
           }else if(tokens[0] == "shader"){
                try{
                   MakeShader(basic_block,scene_data,parameters);
               }catch(std::exception &exp){
                    std::cout<<"Shader not loaded. Error at line " << line_number <<"\n";
                    Debug::WriteErrorLog(exp.what());
               }
            }
        }
    }else if((e = line.find("|")) != std::string::npos){
        CubeMap* cube_map = nullptr;
        parameters = line.substr(e,line.length());
         std::regex_search(parameters,matches,reg);
        if(goElements.model != nullptr && goElements.m_shader != nullptr && matches.ready()){
                    Texture* cubeMapTex = MakeTexture(basic_block,scene_data,parameters,4);
                    scene_data->loaded_textures[matches.str(1)] = cubeMapTex;
                    cube_map = new CubeMap(dynamic_cast<CubeMapTexture*>(cubeMapTex),goElements.model,goElements.m_shader);
            }
            scene_data->cube_map = cube_map;
            return SceneReaderState::waiting;
    }

    return current_state;
}


bool MakeModel(BasicsBlock* basic_block, SceneData* scene_data, std::string parameters){
    //Regex to catch elements in between ""
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    //Apply the regex rule
    std::regex_search(parameters,matches,reg);
    if (matches.ready()){
        //Searches if it is in loaded models
        if(scene_data->loaded_models.count(matches.str(1))){
            //If it is give it to goElements
            goElements.model = scene_data->loaded_models[matches.str(1)];
            return true;
        //Checks if the last scene has the desired model
        }else if(old_scene_d != nullptr && old_scene_d->loaded_models.count(matches.str(1))){
            goElements.model = old_scene_d->loaded_models[matches.str(1)];
            scene_data->loaded_models[matches.str(1)] = goElements.model;
            old_scene_d->loaded_models.erase(matches.str(1));
            return true;
        } else{
            if(basic_block->global_data.models_path.count(matches.str(1))){
                Model* loaded_model = new Model(basic_block->global_data.models_path[matches.str(1)]);
                scene_data->loaded_models[matches.str(1)] = loaded_model;
                goElements.model = loaded_model;
                return true;
            }else{
                std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find loaded model \""<<matches.str(1)<<"\"\n";
                return false;
            }
        }
        
    }
    else{
        return false;
        std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cant match \"name of model\"\n";
    }
}

Texture* MakeTexture(BasicsBlock* basic_block, SceneData* scene_data, std::string parameters, unsigned int id){
    //Regex to catch elements in between ""
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    std::regex_search(parameters,matches,reg);
    Texture* out_texture = nullptr;
    if(scene_data->loaded_textures.count(matches.str(1))){
        Texture* cubeMapTex = scene_data->loaded_textures[matches.str(1)];
        //Check if texture is in old scene
        }else if(old_scene_d != nullptr && old_scene_d->loaded_textures.count(matches.str(1))){
            out_texture = old_scene_d->loaded_textures[matches.str(1)];
            scene_data->loaded_textures[matches.str(1)] = out_texture;
            //Remove texture from old_scene to avoid deletion
            old_scene_d->loaded_textures.erase(matches.str(1));
        }else{
            if(basic_block->global_data.textures_path.count(matches.str(1))){
                out_texture = TextureFactory::GetObjectFromID(id,(basic_block->global_data.textures_path[matches.str(1)]));
                scene_data->loaded_textures[matches.str(1)] = out_texture;
            }else{
                std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find texture name \""<<matches.str(1)<<"\"\n"; 
            }
        }
    return out_texture;
}

bool MakeShader(BasicsBlock* basic_block, SceneData* scene_data, std::string parameters){
    //Regex to catch elements in between ""
    std::regex reg ("\"(.*)\"");
    std::smatch matches;
    std::regex_search(parameters,matches,reg);
    Shader* output = nullptr;
    //Checks if shader is alreadyloaded
    if(scene_data->loaded_shaders.count(matches.str(1))){
        goElements.m_shader = scene_data->loaded_shaders[matches.str(1)];
    }
    //Check if last scene has the desired shader
    else if(old_scene_d != nullptr && old_scene_d->loaded_shaders.count(matches.str(1))){
            goElements.m_shader = old_scene_d->loaded_shaders[matches.str(1)];
            scene_data->loaded_shaders[matches.str(1)] = goElements.m_shader;
            old_scene_d->loaded_shaders.erase(matches.str(1));
            return true;
    } else if(basic_block->global_data.shaders_path.count(matches.str(1))){
        std::string vertex_path = basic_block->global_data.shaders_path[matches.str(1)][0];
        std::cout<<"Loading shader: " << matches.str(1) << "\n";
        if(basic_block->global_data.shaders_path[matches.str(1)].size() > 2){
            std::string geometry_shader = basic_block->global_data.shaders_path[matches.str(1)][1];
            std::string fragment_path = basic_block->global_data.shaders_path[matches.str(1)][2]; 
            scene_data->loaded_shaders[matches.str(1)] = new Shader(vertex_path,geometry_shader,fragment_path);
            goElements.m_shader = scene_data->loaded_shaders[matches.str(1)];
        }else{
                std::string fragment_path = basic_block->global_data.shaders_path[matches.str(1)][1];
                scene_data->loaded_shaders[matches.str(1)] = new Shader(vertex_path,fragment_path);
                goElements.m_shader = scene_data->loaded_shaders[matches.str(1)];
        }
    }
    else{
        std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE(" << line_number <<") -> Cannot find loaded shader \""<<matches.str(1)<<"\"\n";
        Debug::WriteErrorLog("FILE::SCENE::INTEPRETER:ERROR::LINE(" + std::to_string(line_number) + ") -> Cannot find loaded shader \"" + matches.str(1) + "\"");
        return false;
    }
    return true;
}

float* GetVec3(std::vector<std::string> tokens){
    float* vec3 = new float[3];
    vec3[0] = std::stof(tokens[1]);
    vec3[1] = std::stof(tokens[2]);
    vec3[2] = std::stof(tokens[3]);
    return vec3;
}

void ClearGoELemetns(){
    goElements.basic_block = nullptr;
    goElements.initial_pos = nullptr;
    goElements.m_camera = nullptr;
    goElements.m_shader = nullptr;
    goElements.model = nullptr;
    goElements.size = glm::vec3(1.0);
    goElements.isOpaque = false;

    light_elemtents.light_direction = nullptr;
    light_elemtents.light_direction_is_position = false;
    light_elemtents.light_color = glm::vec3(1.0);
    light_elemtents.light_intensity = 1.0;
}
