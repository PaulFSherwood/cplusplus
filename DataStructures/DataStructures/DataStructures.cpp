// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

/*
      A             200         100        300
    [200]--------->[2|100]---->[4|300]---->[6|0]---->NULL
      |             ^   ^                   ^ ^
      V             |    \                  |  \
Pointer to node   data   Link              int  Node*
*/
struct node
{
    int data;
    struct node* next;
};
struct node* head;  // global variable, that can be accessed from anywhere
void Insert(int x);
void Print();

int main()
{
    std::cout << "Hello World!\n";

    head = NULL;  // empty list;
    printf("How many numbers?\n");
    int n, i, x;
    std::cin >> n;

    std::cout << "Head: [" << head << "]\n";

    for (i = 0; i < n; i++)
    {
        printf("Enter the number \n");
        std::cin >> x;
        Insert(x);
        Print();
    }
    
    // creating a memory block to store a node
    // malloc(sizeof(node))
    //node* a;
    //a = NULL;

    ///*node* temp = (node*)malloc(sizeof(node));
    //(*temp).data = 2;*/
    //node* temp = new node();
    //temp->data = 2;
    //temp->next = NULL;
    //a = temp;

    //temp = new node();
    //temp->data = 4;
    //temp->next = NULL;

    //node* temp1 = a;
    //while (temp1->next != NULL)
    //{
    //    temp1 = temp1->next;
    //}

}

void Insert(int x)
{
    // create a node
    struct node *temp = (node*)malloc(sizeof(struct node));
    // node* temp = new node;
    temp->data = x;
    temp->next = head;
    head = temp;
    std::cout << x << ": [" << head << "]";
}

void Print()
{
    struct node* temp = head;
    printf("List is: ");
    while (temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}