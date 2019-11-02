#include <string>
#include <cstdio>
#include <cstring>
#include<iostream>


class FileManagementTools{
    public:
        FileManagementTools();
        static char* GetFilesContents(const char *filename,int* lenght);
};