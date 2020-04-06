#pragma once
#include <string>
#include<cstring>
#include<algorithm>
#include <cstdio>
#include <cstring>
#include<iostream>
#include<vector> 
#include<string>

namespace FileManagementTools{
    char* GetFilesContents(const char *filename,int* lenght);
    std::vector<std::string> ParseLine(std::string line, std::string delimiter);
    void RemoveFromString(std::string &line, char* to_remove);
};