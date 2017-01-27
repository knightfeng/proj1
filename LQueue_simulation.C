/*---------------------------------------------------------------------
                  Simulation program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <cstdlib>
#include <time.h>

void sim()
{
    Queue landing_queue;
    Queue takeoff_queue;
    bool runway_free = true;

    static int land_time = 0;
    static int takeoff_time = 0;
    static int land_rate = 0;
    static int takeoff_rate = 0;
    static int sim_time = 0;

    std::cout << "Time for a plane to land (in minutes): " << std::endl;
    std::cin >> land_time;

    std::cout << "Time for a plane to takeOff (in minutes): " << std::endl;
    std::cin >> takeoff_time;

    std::cout << "Landing rate (planes per hour): " << std::endl;
    cin >> land_rate;

    std::cout << "Takeoff rate (planes per hour): " << std::endl;
    cin >> takeoff_rate;

    std::cout << "How long to run the simulation (in minutes): " << std::endl;
    cin >> sim_time;


    int time = 0;
    int plane_number = 1000;
    int num_planes_landing = 0;
    int num_planes_taking = 0;
    
    srand(1);             //time(NULL) as parameter in srand() FOR PSEUDO-RANDOM.
     
    //sim_time;
    while (time < sim_time)
    {
        std::cout<<"---------------------"<<std::endl;
        std::cout<<"Time = "<<time<<std::endl;
        int random_one = 59; //% 100 + 1;
        int random_two = 60; //rand()

        if(random_one % 60 < land_rate){
            
            landing_queue.enqueue(plane_number);
            num_planes_landing++;
            std::cout << "Plane "<<plane_number<<" wants to land; added to the landing queue; " << num_planes_landing<<" in queue"<<std::endl;
            plane_number++;
        }

        if(random_two % 60 < takeoff_rate){
            
            takeoff_queue.enqueue(plane_number);
            num_planes_taking++;
            std::cout << "Plane "<<plane_number<<" wants to takeoff; added to the takeoff queue; " << num_planes_taking<<" in queue"<<std::endl;
            plane_number++;
        }

        if(runway_free){

            if(!landing_queue.empty()){
                QueueElement temp = landing_queue.front();
                landing_queue.dequeue();
                num_planes_landing--;
                std::cout << "Landing: Plane "<<temp<<"; "<<num_planes_landing<<" in queue"<<std::endl;
            }

            else if (!takeoff_queue.empty()){
                QueueElement temp = takeoff_queue.front();
                takeoff_queue.dequeue();
                num_planes_taking--;
                std::cout << "Taking off: Plane "<<temp<<"; "<<num_planes_taking<<" in queue"<<std::endl;
            }
        }
        

        std::cout << "Random One: " << random_one << std::endl;
        std::cout << "Random Two: " << random_two << std::endl;
        time++;
    }
}
