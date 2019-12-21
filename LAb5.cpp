#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 5

// type definitions for readability //
typedef int variable;
typedef int array;
typedef unsigned int counter;

// array definitions //
array  memory_blocks[] = {100,500,300,200,800,400};
array process_size[] = {212,418,585,349,277,166};

// Linked list definition //
typedef struct Linked_List
{
    int data;
    Linked_List *next;
}node;

//fonksiyon tanýmlarý //
void bestFit(array a[],array b[]);
void firstFit(array a[],array b[]);
void worstfit(array a[],array b[]);
int Findmax(array a[]);
void maxSort(array a[]);
void swap(int *a, int *b);
void displayArray(array a[]);
unsigned int findMinGap(variable a, variable b);


// main function //
int main(void)
{
     firstFit(process_size,memory_blocks);
     //printf("%d",Findmax(process_size));
     //worstfit(process_size,memory_blocks);
     //bestFit(process_size,memory_blocks);
}

void firstFit(array process[],array memory[])
{
   variable m = 0;
   variable p = 0;

   while(p <= SIZE)
   {

       if(process[p] > memory[m])
       {
           m++;
       }

        else if(process[p] <= memory[m])
       {
            memory[m] = memory[m] - process[p];
            process[p] = 0;
            m = 0;
            p++;
       }
   }

   puts("\n\n----------- Processses -----------");
   for(int i = 0;i <= SIZE;i++)
   {
       printf("\n%d)%d",i,process[i]);
       if(process[i] > 0)
       {
           puts("  ==>  Not Allocated");
       }
   }
puts("\n\n--------------- Memory ---------------");
   for(int a = 0;a <= SIZE;a++)
   {
       printf("\n%d)%d",a,memory[a]);
       if(memory[a] <= 0)
       {
           puts("  ==>  All Allocated");
       }
   }

}

int Findmax(array a[])
{
    variable max;
    variable i = 0;
    max = a[i];

    for(i = 1; i <= SIZE; i++)
    {
     if(a[i] > max)
     {
         max = a[i];
     }
    }
    return max;
}

void maxSort(array a[])
{
    variable i;
    variable j;

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE-i; j++)
        {
            if (a[j] > a[j+1])
            {
               swap(&a[j],&a[j+1]);
            }
        }
    }
}

void displayArray(array a[])
{
 for(int i = 0;i <= SIZE; i++)
 {
     printf("\n%d",a[i]);
 }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void worstfit(array process[],array memory[])
{
    maxSort(process);
    maxSort(memory);
    displayArray(process);
    puts("\n");
    displayArray(memory);

   for(int i=SIZE+1;i>0 ;i--)
   {
      memory[i] = memory[i] - process[i];
   }

   puts("\n");
   displayArray(process);
   puts("\n");
   displayArray(memory);
}

unsigned int findMinGap(variable a, variable b)
{
    variable gap;

   if(a >= b)
   {
     gap = a - b;
   }
  return gap;
}


void bestFit(array process[], array memory[])
{
    array temp[SIZE+1];

    for (int i=0; i<=SIZE; i++)
    {
        variable pos = -1;

        for (int j=0; j<=SIZE; j++)
        {
            if (memory[j] >= process[i])
            {
                if (pos == -1)
                {
                    pos = j;
                }

                else if (memory[pos] > memory[j])
                {
                    pos = j;
                }
            }
        }

        if (pos != -1)
        {
            temp[i] = pos;
            memory[pos] -= process[i];
        }
}

displayArray(temp);
}

