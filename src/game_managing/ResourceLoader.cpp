#include "game_managing/ResourceLoader.hpp"

std::smatch find_match(std::string m_string, std::regex reg, int* success){
    std::smatch matches;
    std::regex_search(m_string,matches,reg);
    if(matches.size() > 0){
       *success = 1;
       return matches;
    }
    *success = 0;
    return matches;
}

void ResourceLoader::LoadResourceFromFile(std::string res_path,BasicsBlock* basic_block){
    int line_number = 0;
    std::ifstream infile(res_path);
    std::string line;
    std::string output;
    std::regex reg ("\"(.*)\"");
    std::smatch matches;

    std::string parameters= "";
    while(std::getline(infile,line)){
        line_number++;
        int e = line.find("#");
        if(e != std::string::npos){
            line.erase(e,line.length());
        }
        if (line.find("Game_Name") != std::string::npos){
            e = line.find(":");
            if (e != std::string::npos){
                parameters = line.substr(e+1,line.length());
                int check;
                //Sets the name of the game
                matches = find_match(parameters,reg,&check);
                basic_block->global_data.game_name = check ? matches.str(1) : "NULL";
            }
        }else if(line.find("Add_Model") != std::string::npos){
            e = line.find(":");
            if (e != std::string::npos){
                std::string model_path;
                parameters = line.substr(e+1,line.length());
                std::vector<std::string> tokens = FileManagementTools::ParseLine(parameters, ",");
                if(tokens.size() == 2){
                    int check = 0;
                    output = find_match(tokens[0],reg,&check).str(1);
                    int success = check;
                    model_path = find_match(tokens[1],reg,&check).str(1);
                    success += check;
                    if(success == 2){
                        //Sets a path to the list of path referenced by a name
                        basic_block->global_data.models_path[output] = model_path;
                    }
                    else{
                        std::cout<<"FILE::SCENE::INTEPRETER:ERROR::LINE("<<line_number<<")-> Can't read all input";
                    }
                }
            }
        }else if(line.find("Add_Shader") != std::string::npos){
            e = line.find(":");
            if (e != std::string::npos){
                Shader* a_shader;
                std::string vertex_shader, fragment_shader;
                parameters = line.substr(e+1,line.length());
                std::vector<std::string> tokens = FileManagementTools::ParseLine(parameters, ",");
                if(tokens.size() == 3){
                    int check = 0;
                    output = find_match(tokens[0],reg,&check).str(1);
                    int success = check;
                    vertex_shader = find_match(tokens[1],reg,&check).str(1);
                    success += check;
                    fragment_shader = find_match(tokens[2],reg,&check).str(1);
                    success += check;
                    
                    if(success == 3){
                        try{
                        a_shader = new Shader(vertex_shader,fragment_shader);
                        basic_block->global_data.all_shaders[output] = a_shader;
                        }catch(std::exception &exp){
                            std::cout<<"Shader not loaded\n";
                            Debug::WriteErrorLog(exp.what());
                        }
                    }
                }
            }
        }else if(line.find("Add_Texture") != std::string::npos){
            e = line.find(":");
            if (e != std::string::npos){
                std::string tex_name, tex_path;
                parameters = line.substr(e+1,line.length());
                std::vector<std::string> tokens = FileManagementTools::ParseLine(parameters, ",");
                if(tokens.size() == 2){
                    int succcess = 0;
                    int check = 0;
                    tex_name =  find_match(tokens[0],reg,&check).str(1);
                    succcess += check;
                    tex_path =  find_match(tokens[1],reg,&check).str(1);
                    succcess += check;
                    if(succcess == 2){
                        basic_block->global_data.textures_path[tex_name] = tex_path;
                    }
                }
            } 
        }

    }
}