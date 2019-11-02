#include "game_managing/Time.h"

Time::Time():delta_time(0.0),last_value(0.0){

}

double Time::GetTime(){
    return glfwGetTime();
}

void Time::UpdateDelta(){
    this->delta_time = this->GetTime() - this->last_value;
    this->last_value = this->GetTime();
    if(this->last_value >= 200){
        std::cout<<"Reseting time";
        glfwSetTime(0.0);
        this->last_value = 0.0;
    }
}