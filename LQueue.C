/*--- LQueue.cpp ----------------------------------------------------------
  This file implements LQueue member functions.
  From:  "ADTs, Data Structures, and Problem Solving with C++", 2nd edition
         by Larry Nyhoff
-------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

#include "LQueue.h"
#include <typeinfo>

//--- Definition of Queue constructor
Queue::Queue()
    : myFront(0), myBack(0)
{
}

//--- Definition of Queue copy constructor
Queue::Queue(const Queue &original)
{
  myFront = myBack = 0;
  if (!original.empty())
  {
    // Copy first node
    myFront = myBack = new Queue::Node(original.front());

    // Set pointer to run through original's linked list
    Queue::NodePointer origPtr = original.myFront->next;
    while (origPtr != 0)
    {
      myBack->next = new Queue::Node(origPtr->data);
      myBack = myBack->next;
      origPtr = origPtr->next;
    }
  }
}

//--- Definition of Queue destructor
Queue::~Queue()
{
  // Set pointer to run through the queue
  Queue::NodePointer prev = myFront,
                     ptr;
  while (prev != 0)
  {
    ptr = prev->next;
    delete prev;
    prev = ptr;
  }
}

//--- Definition of assignment operator
const Queue &Queue::operator=(const Queue &rightHandSide)
{
  if (this != &rightHandSide) // check that not q = q
  {
    this->~Queue();            // destroy current linked list
    if (rightHandSide.empty()) // empty queue
      myFront = myBack = 0;
    else
    { // copy rightHandSide's list
      // Copy first node
      myFront = myBack = new Queue::Node(rightHandSide.front());

      // Set pointer to run through rightHandSide's linked list
      Queue::NodePointer rhsPtr = rightHandSide.myFront->next;
      while (rhsPtr != 0)
      {
        myBack->next = new Queue::Node(rhsPtr->data);
        myBack = myBack->next;
        rhsPtr = rhsPtr->next;
      }
    }
  }
  return *this;
}

//--- Definition of empty()
bool Queue::empty() const
{
  return (myFront == 0);
}

//--- Definition of enqueue()
void Queue::enqueue(const QueueElement &value)
{
  Queue::NodePointer newptr = new Queue::Node(value);
  if (empty())
    myFront = myBack = newptr;
  else
  {
    myBack->next = newptr;
    myBack = newptr;
  }
}

//--- Definition of display()
void Queue::display(ostream &out) const
{
  Queue::NodePointer ptr;
  for (ptr = myFront; ptr != 0; ptr = ptr->next)
    out << ptr->data << " ";
  out << endl;
}

//--- Definition of front()
QueueElement Queue::front() const
{
  if (!empty())
    return (myFront->data);
  else
  {
    return 0;
  }
}

//--- Definition of dequeue()
void Queue::dequeue()
{
  if (!empty())
  {
    Queue::NodePointer ptr = myFront;
    myFront = myFront->next;
    delete ptr;
    if (myFront == 0) // queue is now empty
      myBack = 0;
  }
  else
    cerr << "*** Queue is empty -- can't remove a value ***\n";
}

void Queue::merge_two_queues(Queue &q2)
{

  Queue* q1 = this;
  Queue temp = Queue();

  // First two cases are the trivial empty list cases.
  if (q2.empty())
  {
    temp.~Queue();
    return;
  }

  else if (q1->empty())
  {
    *q1=q2;
    temp.~Queue();
    return;
  }

  else
  {
    //Merge two lists 
    while (!q1->empty() || !q2.empty())
    {

      if (q1->empty() && !q2.empty())
      {
        temp.enqueue(q2.front());
        q2.dequeue();
      }

      else if (!q1->empty() && q2.empty())
      {
        temp.enqueue(q1->front());
        q1->dequeue();
      }

      else if (q1->front() <= q2.front())
      {
        temp.enqueue(q1->front());
        q1->dequeue();
      }

      else
      {
        temp.enqueue(q2.front());
        q2.dequeue();
      }
    }

    //Assign q1 to merged list and destroy q2.
    *q1=temp;
    q2.~Queue();

    return;
  }
}

void Queue::move_to_front(QueueElement e)
{
  
  //NULL Guard along with empty Queue case.
  if (e == NULL || empty())
  {
    return;
  }

  //We skip right to the second Node since if the first Node matches then it's already in place.
  if (myFront->next == NULL)
    return;
  if (myFront->next->data == e)
  {
    Node *secondNode = myFront;
    Node *newNode = new Node(e);
    Node *removeNode = myFront->next;

    this->myFront = newNode;
    newNode->next = secondNode;

    delete removeNode;
    removeNode = NULL;
  }

  //Declaring for loop variables.
  QueueElement nextElement;

  //We loop starting from the second Node checking to see if the Node ahead matches e.
  for (Node *ptr = myFront->next; ptr != NULL; ptr = ptr->next)
  {

    if (ptr->next == NULL)
      return;

    nextElement = ptr->next->data;

    if (nextElement == e)
    {
      Node *secondNode = myFront;
      Node *newNode = new Node(nextElement);
      Node *removeNode = ptr->next;

      ptr->next = ptr->next->next;

      this->myFront = newNode;
      newNode->next = secondNode;

      delete removeNode;
      removeNode = NULL;
    }
  }
}
