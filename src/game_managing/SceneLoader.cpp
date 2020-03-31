#include "game_managing/SceneLoader.hpp"


void SceneLoader::LoadSceneFromFile(std::string scene_path, SceneData* scene_data){
    std::ifstream infile(scene_path);
    std::string line;
    while(std::getline(infile,line)){ 
        int e = line.find("#");
        if(e != std::string::npos)
            line.erase(e,line.length());
        //std::cout<<line <<"\n";
        e = line.find('>');
        if(e != -1){
            std::vector<std::string> tokens = FileManagementTools::ParseLine(line,",");
            for(int i = 0; i < tokens.size();i++){
                std::cout<<tokens[i] << "\n";
            }
        }

    }
}