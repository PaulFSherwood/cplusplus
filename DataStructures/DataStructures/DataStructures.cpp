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
void Print();

int main()
{

    head = NULL;   // empty list
    Insert(2, 1);  // List: 2
    Insert(3, 2);  // List: 2, 3
    Insert(4, 1);  // List: 4, 2, 3
    Insert(5, 2);  // List: 4, 5, 2, 3
    Print();

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
}
void Print() {
    node* temp = head;
    while (temp != NULL)
    {
        /*if (temp->next == NULL)
        {
            printf("%d", temp->data);
        }
        else {*/
            printf("%d -|- %d \n", temp->data, temp->next);
            temp = temp->next;
        //}
            if (temp->next == 0) { std::cout << "its zero" << std::endl; }
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