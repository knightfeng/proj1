/*---------------------------------------------------------------------
                  Simulation program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include <cstdlib>
#include <time.h>

static Queue landing_queue;
static Queue takeoff_queue;
static Queue merged_queue;
static Queue emergency_queue;

static Queue prev_landing_queue;
static Queue prev_takeoff_queue;

static bool emergency_landing = false;
static bool runway_one_free = true;
static bool runway_two_free = true;
static int runway_one_tick = 0;
static int runway_two_tick = 0;

static int land_time = 0;
static int takeoff_time = 0;
static int land_rate = 0;
static int takeoff_rate = 0;
static int sim_time = 0;

static int tick = 0;
static int emergency_tick = 0;
static int plane_number = 1000;

static int total_time_waiting_landing = 0;
static int num_planes_landing_queue = 0;
static int max_landing_queue_length = 0;
static int num_planes_landed = 0;

static int total_time_waiting_taking = 0;
static int num_planes_taking_queue = 0;
static int max_taking_queue_length = 0;
static int num_planes_took = 0;

void land_takeoff_method(string value, bool emergency = false)
{
    if (value == "land")
    {

        if (emergency)
        {
            if (merged_queue.empty())
            {
                std::cout << "No new landings will be generated." << std::endl;
                return;
            }
            merged_queue.dequeue();
            prev_landing_queue.dequeue();
        }

        else
        {
            if (landing_queue.empty())
            {
                std::cout << "No new landings will be generated." << std::endl;
                return;
            }
            landing_queue.dequeue();
        }

        QueueElement temp = emergency ? merged_queue.front() : landing_queue.front();
        num_planes_landed++;
        num_planes_landing_queue--;
        total_time_waiting_landing += num_planes_landing_queue;

        if (runway_one_free)
        {
            runway_one_tick = land_time;
            runway_one_free = false;
        }

        else
        {
            runway_two_tick = land_time;
            runway_two_free = false;
        }

        std::cout << "Landing: Plane " << temp << "; " << num_planes_landing_queue << " in queue" << std::endl;
    }

    else if (value == "takeoff")
    {

        if (emergency)
        {
            if (merged_queue.empty())
            {
                std::cout << "No new takeoff will be generated." << std::endl;
                return;
            }
            merged_queue.dequeue();
            prev_takeoff_queue.dequeue();
        }

        else
        {
            if (takeoff_queue.empty())
            {
                std::cout << "No new takeoff will be generated." << std::endl;
                return;
            }
            takeoff_queue.dequeue();
        }
        QueueElement temp = emergency ? merged_queue.front() : takeoff_queue.front();

        num_planes_took++;
        num_planes_taking_queue--;
        total_time_waiting_taking += num_planes_taking_queue;

        string runway;

        if (runway_one_free)
        {
            runway_one_tick = takeoff_time;
            runway_one_free = false;
            runway = "runway ONE ";
        }
        else
        {
            runway_two_tick = takeoff_time;
            runway_two_free = false;
            runway = "runway TWO ";
        }

        std::cout << "Taking off: Plane " << temp << " from " << runway << "; " << num_planes_taking_queue << " in queue" << std::endl;
    }

    else if (value == "emergency")
    {
        //Store previous queues in order to restore normal operations.
        prev_landing_queue = landing_queue;
        prev_takeoff_queue = takeoff_queue;

        //Merge takeoff and landing queue into merged queue.
        std::cout << "MERGED EMERGENCY QUEUE: " << std::endl;
        merged_queue.merge_two_queues(takeoff_queue);
        merged_queue.merge_two_queues(landing_queue);

        std::cout << "EMERGENCY LANDING" << std::endl;
        emergency_queue.enqueue(plane_number);
        emergency_queue.display(cout);
        num_planes_landing_queue++;
        plane_number++;

        //Immediate emergency landing
        num_planes_landed++;
        emergency_queue.dequeue();
        QueueElement temp = emergency_queue.front();
        num_planes_landing_queue--;
        emergency_tick = land_time;

        string runway;

        if (runway_one_free)
        {
            runway_one_tick = land_time;
            runway_one_free = false;
            runway = "runway ONE ";
            std::cout << "EMERGENCY Landing: Plane " << temp << " on " << runway << std::endl;
        }

        else
        {
            runway_two_tick = land_time;
            runway_two_free = false;
            runway = "runway TWO ";
            std::cout << "EMERGENCY Landing: Plane " << temp << " on " << runway << std::endl;
        }
    }
}

void sim()
{
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

    srand(time(NULL));

    while (tick < sim_time)
    {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Time = " << tick << std::endl;
        int random_one = rand();
        int random_two = rand();

        //Decrementing runway/emergency tick and setting runways free once tick is 0 and splitting merged queue back into normal queue.
        if (emergency_tick != 0)
            emergency_tick--;
        if (runway_one_tick != 0)
            runway_one_tick--;
        if (runway_two_tick != 0)
            runway_two_tick--;
        if (runway_one_tick == 0)
            runway_one_free = true;
        if (runway_two_tick == 0)
            runway_two_free = true;
        if (emergency_tick == 0)
        {
            emergency_landing = false;
            landing_queue = prev_landing_queue;
            takeoff_queue = prev_takeoff_queue;
        }

        //Emergency Landing if at least one of the takeoff or landing runway is free.
        if ((random_one % 960 < land_rate) && (runway_two_free || runway_one_free))
        {
            std::cout << "**********EMERGENCY LANDING REQUESTED***********" << std::endl;
            std::cout << "Allow Plane Number: " << plane_number << " to land? Please type y/n" << std::endl;

            //User input to confirm/deny emergency landing.
            string confirmation;
            cin >> confirmation;

            if (confirmation == "n")
            {
                std::cout << "Plane Number: " << plane_number << " has crashed! RIP." << std::endl;
                plane_number++;
                continue;
            }

            else if (confirmation == "y")
            {
                emergency_landing = true;
                land_takeoff_method("emergency");
            }
        }

        //Generate Landing. Will NOT generate if EMERGENCY LANDING generated.
        else if (random_one % 60 < land_rate)
        {
            num_planes_landing_queue++;
            max_landing_queue_length = num_planes_landing_queue > max_landing_queue_length ? num_planes_landing_queue : max_landing_queue_length;

            //Generate landings during EMERGENCY SITUATIONS (merged).
            if (emergency_landing)
            {
                prev_landing_queue.enqueue(plane_number);
                merged_queue.enqueue(plane_number);
                std::cout << "Plane " << plane_number << " wants to land; added to the emergency merged queue; " << num_planes_landing_queue + num_planes_taking_queue << std::endl;
            }

            else
            {
                landing_queue.enqueue(plane_number);
                std::cout << "Plane " << plane_number << " wants to land; added to the landing queue; " << num_planes_landing_queue << " in queue" << std::endl;
            }

            //Count total waiting time ONLY when runways are not free.
            if (runway_one_free == false && runway_two_free == false)
                total_time_waiting_landing += num_planes_landing_queue;
            plane_number++;
        }

        //Generate Takeoff
        if (random_two % 60 < takeoff_rate)
        {
            num_planes_taking_queue++;
            max_taking_queue_length = num_planes_taking_queue > max_taking_queue_length ? num_planes_taking_queue : max_taking_queue_length;

            //Generate takeoffs during EMERGENCY SITUATIONS (merged).
            if (emergency_landing)
            {
                prev_takeoff_queue.enqueue(plane_number);
                merged_queue.enqueue(plane_number);
                std::cout << "Plane " << plane_number << " wants to takeoff; added to the emergency merged queue; " << num_planes_landing_queue + num_planes_taking_queue << std::endl;
            }

            else
            {
                takeoff_queue.enqueue(plane_number);
                std::cout << "Plane " << plane_number << " wants to takeoff; added to the takeoff queue; " << num_planes_taking_queue << " in queue" << std::endl;
            }

            //Count total waiting time when runways are not free AND there are planes landing.
            if ((runway_one_free == false && runway_two_free == false) ||
                ((num_planes_landing_queue != 0) && 
                ((runway_one_free == true && runway_two_free == false) || (runway_one_free == false && runway_two_free == true))))
                total_time_waiting_taking += num_planes_taking_queue;
            plane_number++;
        }

        // Planes Landing and Taking off
        if (runway_one_free || runway_two_free)
        {
            if (emergency_landing)
            {
                //Check to see if MERGED QUEUE's front is LAND or TAKEOFF
                if (merged_queue.front() == prev_landing_queue.front())
                    land_takeoff_method("land", true);

                else if (merged_queue.front() == prev_takeoff_queue.front())
                    land_takeoff_method("takeoff", true);
            }

            else
            {
                land_takeoff_method("land");
                land_takeoff_method("takeoff");
            }
        }

        //Print time till runway is free.
        if (runway_one_tick > 0)
        {
            std::cout << "Time left till runway one is free: " << runway_one_tick << std::endl;
        }

        if (runway_two_tick > 0)
        {
            std::cout << "Time left till runway two is free: " << runway_two_tick << std::endl;
        }

        tick++;
    }

    std::cout << "------STATISTICS-------" << std::endl;
    std::cout << "Maximum number of planes in landing queue was: " << max_landing_queue_length << std::endl;
    std::cout << "Average minutes spent waiting to land: " << ((float)total_time_waiting_landing / (float)num_planes_landed) << std::endl;
    std::cout << "Maximum number of planes in taking queue was: " << max_taking_queue_length << std::endl;
    std::cout << "Average minutes spent waiting to takeoff: " << ((float)total_time_waiting_taking / (float)num_planes_took) << std::endl;
}
