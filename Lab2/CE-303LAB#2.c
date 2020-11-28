/*
 *Writing a C program to get numbers as an input from user
 and to sort them & display in ascending order.
 defining lib to get the input values*/
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

 // Global Variables
int number[1000];
pthread_t getnumbers;
pthread_t sortnumbers;
pthread_t displaynumbers;
int cnt;

// Function Prototypes
void *get_numbers(void *dummy_ptr1);
void *sort_numbers(void *dummy_ptr2);
void *display_numbers(void *dummy_ptr3);


int main(void)
{
pthread_create(&getnumbers,NULL,get_numbers,NULL); // Get numbers from the User //
pthread_join(getnumbers,NULL);

pthread_create(&sortnumbers,NULL,sort_numbers,NULL); // Sort the numbers given by the user //
pthread_join(sortnumbers,NULL);

pthread_create(&displaynumbers,NULL,display_numbers,NULL); // Display the sorted numbers //
pthread_join(displaynumbers,NULL);
}

void *display_numbers(void *dummy_ptr3)
{
printf("\n Sorted Numbers:\n");
for (int j = 0; j < cnt; j++)
   {
   printf("\n Number[ %d ]: ", j+1);
   printf("%d", number[j]);
   }
}

void *get_numbers(void *dummy_ptr1)
{
   int i=0;
   int ic=0;
   int n;
//get the count from the user
   printf("Please enter the amount of numbers:");
   scanf("%i", &ic);
   cnt = ic;
   printf("\n");
   printf("\n Enter the numbers to Sort one bye one: \n");
//get the values from the user one by one
   for (i = 0; i < ic; i++)
      {
       printf("number[ %d ]:",i+1);
       scanf("%d", &n);
 //flush buffer for scanf
       number[i] = n;
      }
}

//sort function
void *sort_numbers(void *dummy_ptr2)
{
   int temp, j=0, k=0;
   for (j = 0; j < cnt; j++)
   {
      for (k = j + 1; k < cnt; k++)
      {
         if (number[j] > number[k])
         {
            temp = number[j];
            number[j] = number[k];
            number[k] = temp;
         }
      }
   }
}
//End
