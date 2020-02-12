#include "game_managing/Time.hpp"

Time::Time():delta_time(0.0),last_value(0.0){

}

double Time::GetTime(bool last_frame){
    if(last_frame){
        return glfwGetTime() - this->last_value;
    }else{
        return glfwGetTime();
    }
}

void Time::UpdateDelta(){
    this->delta_time = this->GetTime() - this->last_value;
    this->last_value = this->GetTime();
    if(this->last_value >= 1000){
        std::cout<<"\nReseting time\n";
        glfwSetTime(0.0);
        this->last_value = 0.0;
    }
}