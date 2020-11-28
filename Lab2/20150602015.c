#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

// Atahan Ekici 20150602015 Ce-303 Section-1 //
typedef unsigned int uint;

typedef struct LINKED_LIST // Since we can not initialize array dynamically in C I will use linked list structure in order to store the given inputs //
{
    int data;
    struct LINKED_LIST * next;
}node;

void *display(void *void_ptr3);
void *bubblesort(void *void_ptr2);
void *initialize(void *void_pointer1);
int list_size(node *a);
void swap(struct LINKED_LIST  *a , struct LINKED_LIST *b);

node *root;
node *iter;

int main()
{
root = (node*)malloc(sizeof(node));  // allocate the memory space //
iter = root; //attach iterator to the first linked list node //

pthread_t getnumbers;
pthread_t sortnumbers;
pthread_t displaynumbers;

pthread_create(&getnumbers,NULL,initialize,NULL); // Get numbers from the User //
pthread_join(getnumbers,NULL);

pthread_create(&sortnumbers,NULL,bubblesort,NULL); // Sort the numbers given by the user //
pthread_join(sortnumbers,NULL);

pthread_create(&displaynumbers,NULL,display,NULL); // Display the sorted numbers //
pthread_join(displaynumbers,NULL);

exit(0); // Terminate the program when main function reaches the end //
}

void* initialize(void *void_pointer1) // Add the given input values to the specified linked list //
{
int scanned = 0;

while(true) // This is where i needed to include stdbool header file since I forgot how to define infinite while loop //
{
puts("Writing -1 exits to the sorting process");
puts("Please enter an integer: ");
scanf("%d",&scanned); // get the input from user //

if(scanned == -1)
{
break; // break the loop if the scanned is -1 //
}
else
{
iter -> next = (node*)malloc(sizeof(node)); // create new memory space for the new linked list element //
iter -> data = scanned; // assign the data to the specified member //
iter = iter -> next; // iterate the iterator to the next list element //
}
}
pthread_exit(NULL);
return NULL; // Not mandatory just to suppress warnings //
}

int list_size(node *a) // This function is used for my bubblesort algorithm to acknowledge how many time i have to iterate over my linked list //
{
    int counter = 0;
    node *iter = root;

    while(iter -> next != NULL)
    {
        counter++;
        iter = iter -> next;
    }
    return counter;
}

void* bubblesort(void *void_ptr2) // The bubblesort algorithm I have written 2 years ago github link: https://github.com/AtahanEkici/AlgortihmsDevolepedWhileOnBus/blob/master/random%20linked%20list.cpp - line:376 //
  {
    node *prev;
    node *current;

    current = (node*)malloc(sizeof(node));
    prev = (node*)malloc(sizeof(node));

    prev = root;
    current = root -> next;

    uint ctr1 = list_size(root);

      while(ctr1 != 0)
    {
        if(current -> next == NULL)
        {
            ctr1--;
            prev = root;
            current = root -> next;
        }

        else if(prev -> data > current -> data)
        {
            swap(prev , current);
            prev = prev -> next;
            current = current -> next;
        }

        else
        {
            prev = prev -> next;
            current = current -> next;
        }
    }
    pthread_exit(NULL);
    return NULL; // Not mandatory just to suppress warnings //
  }

void swap(struct LINKED_LIST  *a , struct LINKED_LIST *b) // swapping 2 elements with each other //
{
    struct LINKED_LIST *c;
    struct LINKED_LIST *d;

    c = (node*)malloc(sizeof(node));
    d = (node*)malloc(sizeof(node));

    c -> data = a -> data;
    d -> data = b -> data;

    a -> data = d -> data;
    b -> data = c -> data;
}

void* display(void *void_ptr3) // displaying the linked list //
{
   unsigned int ctr = 1;

    while(root -> next != NULL)
{
      printf(" %d-) %d\n" , ctr , root -> data);
      ++ctr;
      root = root -> next;
}
pthread_exit(NULL);
return NULL;// Not mandatory just to suppress warnings //
}
// As a side note i could not execute this code properly with using MinGW compiler so i have tested this on: https://www.onlinegdb.com/online_c_compiler  - it runs perfectly on the online compiler//
