/*---------------------------------------------------------------------
                  Driver program to test the Queue class.
  ----------------------------------------------------------------------*/

#include <iostream>
#include "LQueue.h"
#include "LQUEUE_simulation.c"


using namespace std;
	
// testing for git 
void print(Queue q)
{ q.display(cout); }

int main(void)
{
   
  sim();

  /*
   Queue q1;
   
   cout << "Queue created.  Empty? " << boolalpha << q1.empty() << endl;

   cout << "How many elements to add to the queue? ";
   int numItems;
   cin >> numItems;
   for (int i = 1; i <= numItems; i++) 
      q1.enqueue(100*i);

   cout << "Contents of queue q1 (via  print):\n";
   print(q1); 
   cout << endl;

   Queue q2;
   
   q2 = q1;


   q1.merge_two_queues(q1, q2);
   
   
   
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
   cout << "Front value in q2?" << endl << q2.front() << endl;
   cout << "Trying to remove front of q2: " << endl;
   q2.dequeue();
   //system("PAUSE");
    
    cout << "TestPart1A\n"  << endl;
    QueueElement e = 500;
    q1.move_to_front(e);
    
    cout << "finished test1: " << endl;
    cout << "queue 1: " << endl;
    print(q1);
    cout << endl;
   
*/

   return 0;
}
