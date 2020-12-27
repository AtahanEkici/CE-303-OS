#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 23

// Global Reference String //
int page_numbers[SIZE] = {1,2,3,4,2,1,5,6,2,1,2,4,3,7,6,6,5,3,2,1,2,3,6};
int page_size;
int number_of_frames;
// Global Reference String //

// Function Prototypes //
void FIFO(int a[],int b);
void Optimal_Replacement(int a[],int b);
void LRU_Replacement(int a[],int b);
void display_array(int a[]); // A function that i have used for testing purposes //
int find_Least_Recently_Used(int a[], int b);
// Function Prototypes //

int main()
{
puts("Please enter the Frame Size");
scanf("%d",&number_of_frames);

FIFO(page_numbers,number_of_frames);
LRU_Replacement(page_numbers,number_of_frames);
Optimal_Replacement(page_numbers,number_of_frames);
}

// Function Definitions //

void Optimal_Replacement(int a[], int b)
{
int i,j,position,maximum;
bool identifier_1,identifier_2,identifier_3;
int frames[b],temp[b];
int page_faults = 0;

for(i = 0; i < b; i++)
{
frames[i] = -1; // Initialize the array by iteration -1 to every address to be replaced by page values later;
}

for(int i = 0; i < SIZE; i++) // main iterator //
{
identifier_1 = false;
identifier_2 = false;

for(j = 0; j < b; j++)
{
    if(frames[j] == a[i])
    {
        identifier_1 = true;
        identifier_2 = true;
        break;
    }
}
if(identifier_1 == false)
{
for(j = 0; j < b; j++)
{
    if(frames[j] == -1) // if the current frame address is not initialized //
    {
        page_faults++;
        frames[j] = a[i];
        identifier_2 = true;
        break;
    }
}
}
if(identifier_2 == true)
{
    identifier_3 = false;

    for(j = 0; j < b; j++)
    {
        temp[j] = -1; // initialize a temporary array and iterate -1 through it //

        for(int k = 0; k < SIZE; k++)
        {
            if(frames[j] == a[k])
            {
                temp[j] = k;
                break;
            }
        }
    }

    for(j = 0; j < b; j++)
    {
        if(temp[j] == -1)
        {

            position = j;
            identifier_3 = true;
            break;
        }
    }

    if(identifier_3 == false)
    {
        maximum = temp[0];  // initially the maximum value is the starting position of the array //
        position = 0; // Store the maximum index of the array on a variable //

        for(j = 1; j < b; j++)
        {
            if(temp[j] > maximum)
            {
                maximum = temp[j];
                position = j;
            }

        }
    }
    frames[position] = a[i];
    page_faults++;
}
}
printf("Page Faults(Optimal Replacement): %d \n", page_faults);
}

int find_Least_Recently_Used(int a[], int b)
{
int i,min,result;
min = a[0]; // initially the minimum value is equal to the starting address of the array //
result = 0; // assigning the variable in case of not assigned on the loop //

for(i = 0; i < b; i++)
{
    if(a[i] < min)  // if the value is smaller than current minimum value we are holding //
    {
        min = a[i]; // the current minimum value is assigned to the smaller value //
        result = i; // and we have our result //
    }
}
return result;
}

void display_array(int a[])
{
    int i;

    for(i = 0; i < SIZE; i++)
    {
        printf("%d)%d \n",(i+1),a[i]);
    }
}

void LRU_Replacement(int a[], int b)
{
int i,j,page_faults,counter,position;
bool identifier_1 = false;
bool identifier_2 = false;
int frames[b];  // C99 Instruction (Variable lenght array) may not work on every compiler //
int times[b];

page_faults = 0;

for(i = 0; i < b; i++)
{
    frames[i] = -1; // Initialize the frames array for later use and since we are trying the simulate a stack structure 0 should be bigger than the initial value hence we assign -1 to the specified array address //
}

for(i = 0; i < SIZE; i++)
{
identifier_1 = false;
identifier_2 = false; // For each iteration both identifiers are set to false initially //

for(j = 0; j < b; j++)
{
    if(frames[j] == a[i])
    {
        counter++;
        times[j] = counter;
        identifier_1 = 1;
        identifier_2 = 1;
        break;
    }
}
if(identifier_1 == false)
{
for(j = 0; j < b; j++)
{
    if(frames[j] == -1)// Check to see if the address is initialized or not //
    {
        page_faults++;
        counter++;
        frames[j] = a[i];
        times[j] = counter;
        identifier_2 = true;
        break;
    }
}
}
if(identifier_2 == false)
{
position = find_Least_Recently_Used(times, b);
counter++;
page_faults++;
frames[position] = a[i];
times[position] = counter;
}
}
printf("Page Faults(LRU): %d \n", page_faults);
}

void FIFO(int a[], int b)
{
int i,j,iter,page_faults; // Some compiler does not support initializing variables inside for loop so i define them at the beginning of the function scope //
int frames[b];  // C99 Instruction (Variable lenght array) may not work on every compiler //
bool occupied = false;

for(i = 0; i < b; i++)
{
    frames[i] = -1; // Initialize the frames array for later use and since we are trying the simulate a stack structure 0 should be bigger than the initial value hence we assign -1 to the specified array address //
}

iter = 0;
page_faults = 0; // initially the page faults are 0 as well //

for(i = 0; i < SIZE; i++)
{
occupied = false;  // Availability variable could be boolean but i did not wanted to add another header file(stdbool.h) just for one variable //

for(j = 0; j < b; j++)  // look for availability inside simulated stack //
{
    if(frames[i] == a[i])  // If the specific page variable are found on our frames array availability is assigned to 1 for the given address //
    {
        occupied = true;
    }

    if(occupied == false)  // If the specified page is not occupied for the moment flag it as a page fault and iterate the new variable to its place //
    {
        frames[iter] = a[i];
        iter = (++iter) % b;
        page_faults++;
    }
}
}
printf("Page Faults(FIFO): %d \n", page_faults);  // Finally print the page fault result to the screen for the user to observe //
}

// Function Definitions //
