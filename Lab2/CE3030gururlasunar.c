#include <stdio.h>
#include <pthread.h>

int i, count, number[100];

pthread_t display_num;
pthread_t sort_num;
pthread_t get_num;

void *get_number(void *dummy_ptr3);
void *sort_numbers(void *dummy_ptr2);
void *display_function(void *dummy_ptr);

void main()
{
pthread_create(&get_num,NULL,get_number,NULL);
pthread_join(get_num,NULL);

pthread_create(&sort_num,NULL,sort_numbers,NULL);
pthread_join(sort_num,NULL);

pthread_create(&display_num,NULL,display_function,NULL);
pthread_join(display_num,NULL);
}

void *get_number(void *void_ptr3)
{
   puts("Enter the count of number to sort:");
   scanf("%d", &count);
   puts("\nEnter the numbers to Sort one bye one:");

   for (i = 0; i < count; ++i)
   {
       scanf("%d", &number[i]);
   }
   pthread_exit(NULL);
}

void *sort_numbers(void *dummy_ptr2)
{
   int temp, i, j, k;

   for (j = 0; j < count; ++j)
   {
      for (k = j + 1; k < count; ++k)
      {
         if (number[j] > number[k])

         {
            temp = number[j];
            number[j] = number[k];
            number[k] = temp;
         }
      }
   }
   pthread_exit(NULL);
}

void *display_function(void *dummy_ptr)
{
printf("Sorted Numbers:\n");

   for (i = 0; i < count; ++i)
   {
     printf("%d\n", number[i]);
   }
   pthread_exit(NULL);
}
