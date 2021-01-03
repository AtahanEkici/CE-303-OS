#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int variable;
typedef int array;

typedef struct LINKED_LIST
{
   int data;
   struct LINKED_LIST * next;
}node;

// Function Prototypes //
void display(node *r);
void display_array(int a[], int length);
void get_lenght(node *r);
void initialize(node *r, int a);
void bestFit(array a[],array b[]);
void firstFit(array a[],array b[]);
void worstfit(array a[],array b[]);
int find_max(node *a);
int get_size(node *a);
void swap(int a, int b);
int Findmax(array a[]);
// Function Prototypes //

int size;
int SIZE;


int main()
{
node *root;
root = (node*)malloc(sizeof(node));

node *root_2;
root_2 = (node*)malloc(sizeof(node));

node * iter = root;
node *iter_2 = root_2;

initialize(root,1);
puts("\n Now Please input Process Sizes\n");
initialize(root_2,2);

SIZE = get_size(root);

int memory_blocks[SIZE];
int process_sizes[SIZE];

for(int i = 0; i < SIZE; i++) // cast the values on the linked list to arrays //
{
memory_blocks[i] = iter -> data;
iter = iter -> next;
}

for(int i = 0; i < SIZE; i++) // cast the values on the linked list to arrays //
{
process_sizes[i] = iter_2 -> data;
iter_2 = iter_2 -> next;
}

puts("First Fit: \n");
firstFit(process_sizes,memory_blocks);
puts("First Fit: \n-----------");

puts("Worst Fit: \n");
//worstfit(process_sizes,memory_blocks);
puts("Worst Fit: \n-----------");

puts("Best Fit: \n");
//bestFit(process_sizes,memory_blocks);
puts("Best Fit: \n-----------");
}

// Function Definitions //

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

void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
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
               swap(a[j],a[j+1]);
            }
        }
    }
}



void worstfit(array process[],array memory[])
{
    maxSort(process);
    maxSort(memory);

    display_array(process, SIZE);
    puts("\n");
    display_array(memory, SIZE);

   for(int i=SIZE+1;i>0 ;i--)
   {
      memory[i] = memory[i] - process[i];
   }

   puts("\n");
   display_array(process, SIZE);
   puts("\n");
   display_array(memory, SIZE);
}

int findMinGap(variable a, variable b)
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

display_array(temp, SIZE);
}

void display_array(int a[], int length)
{
    for(int i = 0;i <= SIZE; i++)
 {
     printf("\n%d",a[i]);
 }
}

int get_size(node *a)
{
    int counter = 0;
    node *iter = a;

    while((iter -> next) != (NULL))
    {
        counter++;
        iter = iter -> next;
    }

    return counter;
}


int find_max(node *a)
{
node *iter = a;
int max = iter -> data;

 while((iter -> next) != (NULL))
 {
     if(iter -> data > max)
     {
         max = iter -> data;
     }
     iter = iter -> next;
 }
 return max;
}

void display(node *r)
{
   int ctr = 1;

    while((r -> next) != (NULL))
{
      printf(" %d-) %d\n" , ctr , r -> data);
        ++ctr;
      r = r -> next;
}
}


void initialize(node *r, int a) // Add the given input values to the specified linked list //
{
int scanned = 0;
node * iter = r;
int counter = 0;

if(a == 1)
{
while(true) // This is where i needed to include stdbool header file since I forgot how to define infinite while loop //
{
puts("Please enter Memory Blocks: ");
puts("Writing -1 exits to the next phase");
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
size++;
}
}
}
else
{
while(counter < size) // This is where i needed to include stdbool header file since I forgot how to define infinite while loop //
{
puts("Please enter Memory Blocks: ");
puts("Writing -1 exits to the next phase");
printf("%d)",(counter+1));
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
counter++;
}
}
}
}

// Function Definitions //

