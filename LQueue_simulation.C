/*---------------------------------------------------------------------
                  Simulation program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <cstdlib>
#include <time.h>

void sim()
{

    /*
        -Still need to implement average time.
        -Still need to implement a non-trivial method.
        -Still need to comment the code with descriptions. 
    */
    
    Queue landing_queue;
    Queue takeoff_queue;
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

        if (random_one % 60 < land_rate)
        {
            landing_queue.enqueue(plane_number);
            num_planes_landing++;
            max_landing_length = num_planes_landing > max_landing_length ? num_planes_landing : max_landing_length;
            std::cout << "Plane " << plane_number << " wants to land; added to the landing queue; " << num_planes_landing << " in queue" << std::endl;
            plane_number++;
        }

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

            if (!landing_queue.empty())
            {
                QueueElement temp = landing_queue.front();
                landing_queue.dequeue();
                num_planes_landing--;
                std::cout << "Landing: Plane " << temp << "; " << num_planes_landing << " in queue" << std::endl;
            }

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

        std::cout << "Random One: " << random_one << std::endl;
        std::cout << "Random Two: " << random_two << std::endl;
        tick++;
    }

    std::cout << "------STATISTICS-------" << std::endl;
    std::cout << "Maximum number of planes in landing queue was: " << max_landing_length << std::endl;
    std::cout << "Average minutes spent waiting to land: " << std::endl;
    std::cout << "Maximum number of planes in taking queue was: " << max_taking_length << std::endl;
    std::cout << "Average minutes spent waiting to takeoff: " << std::endl;
}
