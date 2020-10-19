#pragma once
class GameObject;

struct InstacingInformation{
    GameObject *game_object;
    unsigned int amount;
    unsigned int instace_vbo = 0;
    unsigned int vertex_index;
    unsigned int element_per_vertex;
    bool IsInstanced(){return this->instace_vbo;}
};
