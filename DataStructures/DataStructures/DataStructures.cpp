// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
      A             200         100        300
    [200]--------->[2|100]---->[4|300]---->[6|0]---->NULL
      |             ^   ^                   ^ ^
      V             |    \                  |  \
Pointer to node   data   Link              int  Node*
*/

int main()
{
    std::cout << "Hello World!\n";

    struct node
    {
        int data;
        node *next;
    };
    // creating a memory block to store a node
    // malloc(sizeof(node))
    node* a;
    a = NULL;

    /*node* temp = (node*)malloc(sizeof(node));
    (*temp).data = 2;*/
    node* temp = new node();
    temp->data = 2;
    temp->next = NULL;
    a = temp;

    

}

