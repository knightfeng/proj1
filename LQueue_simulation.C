/*---------------------------------------------------------------------
                  Simulation program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <cstdlib>
#include <time.h>
#include <limits.h>
#include <set>

void sim()
{

    /*
        -Still need to implement average time.
        -Still need to implement a non-trivial method.
        -Still need to comment the code with descriptions.
     
     //avgerage minutes that an airplane spent waiting to land
     //if a plane is landing, the wait in landing time will be the time of entering - time of landing
     //store the waiting time in the queue
     //add all the time in the queue and divide by the total of num_planes_landing
     
      wait_landing_tick = land_tick - tick;
      total_wait_landing_tick = ????
      avg_landing_tick = ((float) total_wait_landing_tick)/((float) num_planes_landing);
     
    */
    
    
    //landing_queue holds the data for planes that are waiting to land
    //takeoff_queue holds the data for planes that are waiting to takeoff
    //emergency_landing_queue holds the data for planes that are emergency to land
    Queue landing_queue;
    Queue takeoff_queue;
    Queue emergency_landing_queue;
    
    Plane plane();
    Plane runway_plane();
    
    
    int landing_size;
    int total_wait_landing_tick;
    int total_wait_takeoff_tick;
    
    bool runway_free = true;
    static int land_tick = 0;
    static int takeoff_tick = 0;
    static int land_rate = 0;
    static int takeoff_rate = 0;
    static int sim_time = 0;

    std::cout << "Time for a plane to land (in minutes): " << std::endl;
    std::cin >> land_tick;

    std::cout << "Time for a plane to takeOff (in minutes): " << std::endl;
    std::cin >> takeoff_tick;

    std::cout << "Landing rate (planes per hour): " << std::endl;
    cin >> land_rate;

    std::cout << "Takeoff rate (planes per hour): " << std::endl;
    cin >> takeoff_rate;

    std::cout << "How long to run the simulation (in minutes): " << std::endl;
    cin >> sim_time;
    
    int tick = 0;
    int plane_number = 1000;

    int num_planes_landing = 0;
    int max_landing_length = 0;
    int avg_landing_tick = 0;

    int num_planes_taking = 0;
    int max_taking_length = 0;
    int avg_taking_tick = 0;
    

    srand(time(NULL));

    while (tick < sim_time)
    {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Time = " << tick << std::endl;
        int random_one = rand();
        int random_two = rand();
        
        
        //Precondition: first random number's remainder is less than landing rate
        //Postcondition: If an emergency plane requests to land, plane is added to the emergency landing queue, otherwwise plane is enqueued or added to the landing queue; in that case, calculate maximum queue length
        if (random_one % 60 < land_rate)
        {
            std::string emergencyLanding;
            std::cout << "Is it an emergerncy? (yes or no)" << std::endl;
            cin >> emergencyLanding;
            
            
            if (emergencyLanding == "yes")
            {
                Plane plane = new Plane();
                plane.plane_number = plane_number;
                plane.wait_start = tick;
                emergency_landing_queue.enqueue(plane);
                QueueElement qq = plane_number;
                std::cout << "Emergency plane to land: Plane " << qq << std::endl;
            }
            
            else if (emergencyLanding == "no")
            {
                landing_queue.enqueue(plane_number);
            }
            
            num_planes_landing++;
            max_landing_length = num_planes_landing > max_landing_length ? num_planes_landing : max_landing_length;
            std::cout << "Plane " << plane_number << " wants to land; added to the landing queue; " << num_planes_landing << " in queue" << std::endl;
            
            plane_number++;
        }
        
        //Precondition: second random number's remainder is less than takeoff rate
        //Postcondition: plane is added to the takeoff queue; calculate maximum queue length
        if (random_two % 60 < takeoff_rate)
        {
            takeoff_queue.enqueue(plane_number);
            num_planes_taking++;
            max_taking_length = num_planes_taking > max_taking_length ? num_planes_taking : max_taking_length;
            std::cout << "Plane " << plane_number << " wants to takeoff; added to the takeoff queue; " << num_planes_taking << " in queue" << std::endl;
            plane_number++;
        }

        
        if (runway_free)
        {
            //emergency plane request to land
            //Postcondition: next emergency plane requests to land
            if (!emergency_landing_queue.empty())
            {
                QueueElement temp = emergency_landing_queue.front();
                runway_plane = emergency_landing_queue.dequeue();
                runway_plane.move_start = tick;
                total_wait_landing_tick += plane.wait_start - tick;
                num_planes_landing--;
                std::cout << "Emergency Landing: Plane " << temp << "; " << num_planes_landing << " in queue" << std::endl;
                runway_free = false;
            }
            
            //number of planes request to land
            //Postcondition: next plane requests to land
            else if (!landing_queue.empty())
            {
                QueueElement temp = landing_queue.front();
                landing_queue.dequeue();
                num_planes_landing--;
                std::cout << "Landing: Plane " << temp << "; " << num_planes_landing << " in queue" << std::endl;
            }
            
            //number of planes request to takeoff
            //Postcondition: next plane requests to takeoff
            else if (!takeoff_queue.empty())
            {
                QueueElement temp = takeoff_queue.front();
                takeoff_queue.dequeue();
                num_planes_taking--;
                std::cout << "Taking off: Plane " << temp << "; " << num_planes_taking << " in queue" << std::endl;
            }

            else
            {
                std::cout << "No new takeoffs or landings will be generated." << std::endl;
            }
        }
        
        else if (!runway_free)
        {
            while ((runway_plane.move_start - tick) > land_tick)
            {
                //this plane is still landing, got to next tick because you can't do anything
            }
            runway_free = true;
        }

        std::cout << "Random One: " << random_one << std::endl;
        std::cout << "Random Two: " << random_two << std::endl;
        tick++;
    }

    std::cout << "------STATISTICS-------" << std::endl;
    std::cout << "Maximum number of planes in landing queue was: " << max_landing_length << std::endl;
    std::cout << "Average minutes spent waiting to land: " << avg_landing_tick << std::endl;
    std::cout << "Maximum number of planes in taking queue was: " << max_taking_length << std::endl;
    std::cout << "Average minutes spent waiting to takeoff: " << avg_taking_tick << std::endl;

}



class Plane
{
    int wait_start;
    int move_start;
    
public:
    
    plane();
    runway_plane(); //plane in runway already
    //void land (int land_tick);
    //void fly (int takeoff_tick);
    
   
};







