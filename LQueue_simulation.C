/*---------------------------------------------------------------------
                  Simulation program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <cstdlib>
#include <time.h>




int main(void)
{
    //srand(time(NULL)); //SET TO NULL FOR PSEUDO-RANDOM.
    //int answer = rand() % 100 + 1;
    
    int land_time = 0;
    int takeoff_time = 0;
    int land_rate = 0;
    int takeoff_rate = 0;
    int sim_time = 0;
    
    std::cout<<"Time for a plane to land (in minutes): "<<std::endl;
    std::cin>>land_time;
    
    std::cout<<"Time for a plane to takeOff (in minutes): "<<std::endl;
    std::cin>>takeoff_time;
    
    std::cout<<"Landing rate (planes per hour): "<<std::endl;
    cin>>land_rate;
    
    std::cout<<"Takeoff rate (planes per hour): "<<std::endl;
    cin>>takeoff_rate;
    
    std::cout<<"How long to run the simulation (in minutes): "<<std::endl;
    cin>>sim_time;
    
    return 0;
}
