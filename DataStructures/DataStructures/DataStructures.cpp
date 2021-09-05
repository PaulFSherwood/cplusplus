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

//node *Insert(node *head, int x);
//void Print(node* head);
void Insert(int data, int n);
void InsertEnd(int data);
void Delete(int n);
void Print();

int main()
{
    head = NULL;  // list is empyt
    InsertEnd(2);
    InsertEnd(4);
    InsertEnd(6);
    InsertEnd(5);  // List: 2,4,6,5
    Print();
    int n;
    std::cout << "Enter a position\n";
    std::cin >> n;
    Delete(n);
    Print();


    // Insert anywhere testing
    //head = NULL;   // empty list
    //Insert(2, 1);  // List: 2
    //Print();
    //Insert(3, 2);  // List: 2, 3
    //Print();
    //Insert(4, 1);  // List: 4, 2, 3
    //Print();
    //Insert(5, 2);  // List: 4, 5, 2, 3
    //Print();
    //Insert(8, 5);  // List: 4, 5, 2, 3, 8
    //Print();

    //node *head = NULL;  // empty list;
    //printf("How many numbers?\n");
    //int n, i, x;
    //std::cin >> n;

    //std::cout << "Head: [" << head << "]\n";

    //for (i = 0; i < n; i++)
    //{
    //    printf("Enter the number \n");
    //    std::cin >> x;
    //    head = Insert(head, x);
    //    Print(head);
    //}
    
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

void Insert(int data, int n)
{
    node* temp1 = new node();
    temp1->data = data;
    temp1->next = NULL;
    if (n == 1)
    {
        temp1->next = head;
        head = temp1;
        return;
    }
    node* temp2 = head;
    for (int i = 0; i < n - 2; i++)
    {
        temp2 = temp2->next;
    }
    temp1->next = temp2->next;
    temp2->next = temp1;


    //std::cout << "[" << temp1->data << " | " << temp1->next << "]" << std::endl;
    //std::cout << "[" << temp2->data << " | " << temp2->next << "]" << std::endl;
    //std::cout << std::endl;
}
void InsertEnd(int data)
{
    // geeksforgeeks.com https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
    // allocate node
    struct node *temp = (node*)malloc(sizeof(struct node));
    // insert the data
    temp->data = data;
    temp->next = head;
    
    head = temp;
}
void Delete(int n)
{
    struct node* temp1 = head; // head now points to second node
    if (n == 1)
    {
        head = temp1->next;
        free(temp1);
        return;
    }

    int i;
    std::cout << "temp1: " << temp1->next << std::endl;
    for (i = 0; i < n - 2; i++)
    {
        if (temp1->next == NULL) { return; }
        temp1 = temp1->next;
        std::cout << i << "temp1: " << temp1->next << std::endl;

    }
    // This section below is to move the pointer location and free the temp memory
    // temp1 points to (n-1)th node
    struct node* temp2 = temp1->next;  // temp2 = address that temp1 points to
    /*std::cout << "&temp2: " << temp2 << std::endl;
    std::cout << "temp2: " << temp2->next << std::endl;*/
    temp1->next = temp2->next; // Move temp1->next pointer to what temp2->next points to
    //std::cout << "temp1: " << temp1->next << std::endl;
    free(temp2);
}
void Print() {
    node* temp = head;
    std::cout << head << "::" << head->next << std::endl;
    while (temp != NULL)
    {
        if (temp->next == 0)
        {
            //std::cout << temp->data;
            std::cout << "[" << temp->data << " | " << temp->next << "]" << std::endl;
            temp = temp->next;
        }
        else {
            //std::cout << temp->data << ", ";
            std::cout << "[" << temp->data << " | " << temp->next << "]-->";// << std::endl;
            temp = temp->next;
        }
    }
    printf("\n");
}

// Insert at the beginning
//node *Insert(node *head, int x)
//{
//    // create a node
//    struct node *temp = (node*)malloc(sizeof(struct node));
//    // node* temp = new node;
//    temp->data = x;
//    temp->next = NULL;
//    if (head != NULL) temp->next = head;
//    head = temp;
//    std::cout << x << ": [" << head << "]";
//
//    return head;
//}
//void Print(node *head)
//{
//    //struct node* temp = head;
//    printf("List is: ");
//    while (head != NULL)
//    {
//        printf(" %d", head->data);
//        head = head->next;
//    }
//    printf("\n");
//}