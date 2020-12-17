#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Hard Coded array Bounds //
#define NUMBER_OF_PROCESSES 5
#define NUMBER_OF_RESOURCES 3
// Hard Coded array Bounds //

typedef struct Array_Return_Type  // As the name implies this structure is for returning an array //
{
    int array[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES];
}art; // Since C can not return arrays but can return structures i will use this structure to return arrays //

typedef struct One_Dimentional_Array_Return
{
    int array[NUMBER_OF_PROCESSES];
}odar;  // Return type for one dimensional arrays with a longevity of 5//

// Arrays //
int allocated[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES] = {{ 0, 1, 0 },{ 2, 0, 0 }, { 3, 0, 2 },{ 2, 1, 1 },{ 0, 0, 2 }};  // Allocated Matrix //
int max[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES] = {{ 8, 5, 3 },{ 3, 2, 2 },{ 9, 0, 2 },{ 6, 2, 2 },{ 4, 5, 3 }};  // Maximum Matrix //
int available[NUMBER_OF_RESOURCES] = {3, 3, 2};  // Available Matrix //
int states[NUMBER_OF_PROCESSES];
// Arrays //

// Function Prototypes //
art calculate_need(int maximum[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES],int allocated[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]);
void display(art a);
bool isSafe(art a);
odar calculate_safe_state(art need);
void display_safe_state(odar a);
odar initializer(odar a);
// Function Prototypes //

int main(void)
{
art need_matrix = calculate_need(max,allocated);
display(need_matrix);
odar states = calculate_safe_state(need_matrix);
display_safe_state(states);
}

// Function Definitions //
odar calculate_safe_state(art need)
{
int a,b,c,d,identifier,counter = 0;
odar safes,test;

test = initializer(test); // Load checker array with 0 values in order not to get error when the indexes are empty //

for (a = 0; a < NUMBER_OF_PROCESSES; a++)
{
for (b = 0; b < NUMBER_OF_PROCESSES; b++)
{
 if (test.array[b] == 0)
{
identifier = 0;
for (c = 0; c < NUMBER_OF_RESOURCES; c++)
{
if (need.array[b][c] > available[c])  // if the need matrix is bigger than available the process can not be satisfied //
{
identifier = 1;
break;
}
}
if (identifier == 0) // If the process is safe //
{
safes.array[counter++] = b; // Add the states index number to the resulting array //
for (d = 0; d < NUMBER_OF_RESOURCES; d++)
{
available[d] += allocated[b][d]; // After the process is finished load up the rest of the resources to available resources //
}
test.array[b] = 1;
}  // identifier //
}  // test //
}  // b //
}  // a //
return safes;
}

odar initializer(odar a)
{
    int index;

    for(index = 0; index < NUMBER_OF_PROCESSES; index++)
    {
        a.array[index] = 0;
    }
    return a;
}

bool isSafe(art a)  // Used this function for testing purposes //
{
int i,j = 0;// Some compilers does not support assignment on 'for' so i define these here //

for (i = 0; i < NUMBER_OF_PROCESSES; i++)
{
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
         if(a.array[i][j] < 0)
         {
             puts("\n --------");
             puts("\n Not safe \n");
             return false;  // If a matrix value is smaller than 0 the execution for this process may not possible for the specific machine //
             break;
         }
    }
}
puts("\n --------");
puts("\n Safe \n");
return true;  // If none of the matrix members are smaller than 0 than the need matrix is safe //
}

art calculate_need(int maximum[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES],int allocated[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES])
{
puts("Need Matrix: ");
art need; // define our returning array //
int i,j; // Some compilers does not support assignment on 'for' so i define these here //

for (i = 0; i < NUMBER_OF_PROCESSES; i++)
{
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
         need.array[i][j] = maximum[i][j] - allocated[i][j];
    }
}
return need;
}

void display(art a)  // For debugging issues //
{
int i,j; // Some compilers does not support assignment on 'for' so i define these outside of the 'for' scope //

for (i = 0; i < NUMBER_OF_PROCESSES; i++)
{
    if(i > 0)  // Just for beatification //
    {
        puts(" \n ");
    }
    printf("\nP%d)",(i+1)); // Prints the Process ID //
    for (j = 0; j < NUMBER_OF_RESOURCES; j++)
    {
        printf(" %d ", a.array[i][j]);
    }
}
}

void display_safe_state(odar a) // Display the safe state in an orderly fashion//
{
int i;
puts("\n");
puts("Order for one of the Safe States: \n");

    for(i = 0; i<NUMBER_OF_PROCESSES;i++)
    {
        if(i == 4)
        {
            printf(" P%d <=>", (a.array[i]+1)); // Last indexed Process does not need a "==>" pointing to nothing //
        }
        else if(i == 0)
        {
             printf("<=> P%d ==>",(a.array[i]+1));
        }
        else
        {
            printf(" P%d ==>", (a.array[i]+1));
        }
    }
}


// Function Definitions //
