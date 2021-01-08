#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

// Struct definition for continous data reading //
typedef struct LINKED_LIST // Since we can not initialize array dynamically in C I will use linked list structure in order to store the given inputs //
{
    int data;
    struct LINKED_LIST * next;
}node;
// Struct definition for continous data reading //

// Function Prototypes //
void FIFO(int a[], int b);
void get_numbers();
void process_fifo();
void display_result();
// Function Prototypes //


// Global Variables //
int stack_size;
int array_size;
int pagefault_count;
int array[100];
node *root;
// Global Variables //

int main()
{
root = (node*)malloc(sizeof(node));
// Pthread references //
pthread_t getnumbers;
pthread_t processfifo;
pthread_t displayresult;
// Pthread references //

// Threaddding library function calls //
pthread_create(&getnumbers,NULL,get_numbers,NULL); // Get numbers from the User //
pthread_join(getnumbers,NULL);

node *iter = root;

for(int i = 0; i < array_size; i++) // cast the values on the linked list to arrays //
{
array[i] = iter -> data;
iter = iter -> next;
}

pthread_create(&processfifo,NULL,process_fifo,NULL); // Sort the numbers given by the user //
pthread_join(processfifo,NULL);

pthread_create(&displayresult,NULL,display_result,NULL); // Display the sorted numbers //
pthread_join(displayresult,NULL);
// Threaddding library function calls //
}

void display_result()
{
    printf("Page Fault Count: %d", pagefault_count);
}

void process_fifo()
{
int i,j,iterator; // Some compiler does not support initializing variables inside for loop so i define them at the beginning of the function scope //
int frames[stack_size];  // C99 Instruction (Variable lenght array) may not work on every compiler //
bool occupied = false;

for(i = 0; i < stack_size; i++)
{
    frames[i] = -1; // Initialize the frames array for later use and since we are trying the simulate a stack structure 0 should be bigger than the initial value hence we assign -1 to the specified array address //
}

iterator = 0;
pagefault_count = 0; // initially the page faults are 0 as well //

for(i = 0; i < array_size; i++)
{
occupied = false;  // Availability variable could be boolean but i did not wanted to add another header file(stdbool.h) just for one variable //

for(j = 0; j < stack_size; j++)  // look for availability inside simulated stack //
{
    if(frames[i] == array[i])  // If the specific page variable are found on our frames array availability is assigned to 1 for the given address //
    {
        occupied = true;
    }

    if(occupied == false)  // If the specified page is not occupied for the moment flag it as a page fault and iterate the new variable to its place //
    {
        frames[iterator] = array[i];
        iterator = (++iterator) % stack_size;
        pagefault_count++;
    }
}
}
}

void get_numbers()
{
int scanned = 0;
node * iter = root;
int array_counter = 0;

puts("Please input the stack size for FIFO");
scanf("%d", &stack_size);

puts("Please proceed to giving the memory addresses to the linked list\n");

while(1) // This is where i needed to include stdbool header file since I forgot how to define infinite while loop //
{
puts("Writing -1 exits the loop");
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
array_size++;
array[array_counter] = scanned;
}
}
pthread_exit(NULL);
}
