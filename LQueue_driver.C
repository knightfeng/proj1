/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include "LQueue_simulation.C"

using namespace std;

// testing for git
void print(Queue q)
{
  q.display(cout);
}

int main(void)
{

  Queue q1;

  cout << "Queue created.  Empty? (TYPE 5)" << boolalpha << q1.empty() << endl;

  cout << "How many elements to add to the queue? ";
  int numItems;
  cin >> numItems;
  for (int i = 1; i <= numItems; i++)
    q1.enqueue(100 * i);

  cout << "Contents of queue q1 (via  print):\n";
  std::cout<<"Q1: ";print(q1);
  cout << endl;

  Queue q2;

  q2 = q1;
  std::cout<<"--------TESTING MOVE TO FRONT AREA---------"<<std::endl;
  q1.move_to_front(500);
  std::cout<<"Q1: ";
  print(q1);
  std::cout<<"--------TESTING END---------"<<std::endl;
  
  std::cout<<"--------TESTING MERGE AREA---------"<<std::endl;
  q1.merge_two_queues(q2);
  std::cout<<"Q1: ";print(q1);
  std::cout<<"Q2: ";print(q2);
  std::cout<<"--------TESTING END---------"<<std::endl;
  

  std::cout<<"--------TESTING SIMULATION---------"<<std::endl;
  sim();
  std::cout<<"--------SIMULATION END---------"<<std::endl;


  //I leave this here for the marker in case they want it. 
  /*
  cout << "Contents of queue q2 after q2 = q1 (via  print):\n";
  print(q2);
  cout << endl;

  cout << "Queue q2 empty? " << q2.empty() << endl;

  cout << "Front value in q2: " << q2.front() << endl;

  while (!q2.empty())
  {
    cout << "Remove front -- Queue contents: ";
    q2.dequeue();
    q2.display(cout);
  }
  cout << "Queue q2 empty? " << q2.empty() << endl;
  cout << "Front value in q2?" << endl
       << q2.front() << endl;
  cout << "Trying to remove front of q2: " << endl;
  q2.dequeue();
  */


  
  return 0;
}
