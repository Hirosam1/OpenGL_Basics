#include "game_managing/ResourceLoader.hpp"

void ResourceLoader::LoadResourceFromFile(std::string res_path,BasicsBlock* basic_block){
    std::ifstream infile(res_path);
    std::string line;
    std::string output;
    while(std::getline(infile,line)){
    }
}