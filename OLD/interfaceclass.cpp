/** Virtual functions: interface class    **
 ** C++ » Class » Interface               **
 ** http://www.java2s.com/Code/Cpp/Class/ **
 ** Virtualfunctionsinterfaceclass.htm    **/

#include <iostream>
#include <cstdlib>
using namespace std;

class list {
public:
  list *head;  // pointer to next item in list
  list *tail;
  list *next;
  int num;     // value to be stored

  list() { 
     head = tail = next = NULL; 
  }
  virtual void store(int i) = 0;
  virtual int retrieve() = 0;
};

class queue : public list {
public:
  void store(int i);
  int retrieve();
};

void queue::store(int i)
{
  list *item;

  item = new queue;
  if(!item) {
    cout << "Allocation error.\n";
    exit(1);
  }
  item->num = i;

  // put on end of list
  if(tail) 
     tail->next = item;
  tail = item;
  item->next = NULL;
  if(!head) 
     head = tail;
}

int queue::retrieve()
{
  int i;
  list *p;

  if(!head) {
    cout << "List empty.\n";
    return 0;
  }

  i = head->num;
  p = head;
  head = head->next;
  delete p;

  return i;
}

class stack : public list {
public:
  void store(int i);
  int retrieve();
};

void stack::store(int i)
{
  list *item;

  item = new stack;
  if(!item) {
    cout << "Allocation error.\n";
    exit(1);
  }
  item->num = i;

  // put on front of list for stack-like operation
  if(head) 
     item->next = head;
  head = item;
  if(!tail) 
     tail = head;
}

int stack::retrieve()
{
  int i;
  list *p;

  if(!head) {
    cout << "List empty.\n";
    return 0;
  }

  // remove from start of list
  i = head->num;
  p = head;
  head = head->next;
  delete p;

  return i;
}

class sorted : public list {
public:
  void store(int i);
  int retrieve();
};

void sorted::store(int i)
{
  list *item;
  list *p, *p2;

  item = new sorted;
  if(!item) {
    cout << "Allocation error.\n";
    exit(1);
  }
  item->num = i;

  // find where to put next item
  p = head;
  p2 = NULL;
  while(p) { // goes in middle
    if(p->num > i) {
      item->next = p;
      if(p2) p2->next = item;  // not 1st element
      if(p==head) head = item; // new 1st element
      break;
    }
    p2 = p;
    p = p->next;
  }
  if(!p) { // goes on end
    if(tail) tail->next = item;
    tail = item;
    item->next = NULL;
  }
  if(!head) // is first element
    head = item;
}

int sorted::retrieve()
{
  int i;
  list *p;

  if(!head) {
    cout << "List empty.\n";
    return 0;
  }

  // remove from start of list
  i = head->num;
  p = head;
  head = head->next;
  delete p;

  return i;
}

int main()
{
  list *p;

  queue q_ob;
  p = &q_ob; // point to queue

  p->store(1);
  p->store(2);
  p->store(3);

  cout << "Queue: ";
  cout << p->retrieve();
  cout << p->retrieve();
  cout << p->retrieve();

  cout << '\n';

  stack s_ob;
  p = &s_ob; // point to stack

  p->store(1);
  p->store(2);
  p->store(3);

  cout << "Stack: ";
  cout << p->retrieve();
  cout << p->retrieve();
  cout << p->retrieve();

  cout << '\n';

  sorted sorted_ob;
  p = &sorted_ob;

  p->store(4);
  p->store(1);
  p->store(3);
  p->store(9);
  p->store(5);

  cout << "Sorted: ";
  cout << p->retrieve();
  cout << p->retrieve();
  cout << p->retrieve();
  cout << p->retrieve();
  cout << p->retrieve();

  cout << '\n';


  return 0;
}
