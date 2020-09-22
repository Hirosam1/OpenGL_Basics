#include "game_managing/Time.hpp"

namespace Time{
    double delta_time = 0;
    double last_value = 0;
};

double Time::GetTime(){
    return glfwGetTime();  
}

void Time::UpdateDelta(){
    delta_time = GetTime() - last_value;
    last_value = GetTime();
    if(Time::last_value >= 1000){
        std::cout<<"\nReseting time\n";
        glfwSetTime(0.0);
        last_value = 0.0;
    }
}