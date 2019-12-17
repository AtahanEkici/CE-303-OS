#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#define SIZE 23

typedef int array;
typedef int counter;
typedef int pagefault;
typedef bool checker;

array staticvalues[SIZE] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 4, 3, 7, 6, 6, 5, 3, 2, 1, 2, 3, 6}; // static values //

typedef struct Linked_List // Linked List //
{
    int data;
    struct Linked_List * next;
    int occur;
}node;

typedef struct Stack // Stack //
{
    int top;
    unsigned capacity;
    int* array;
}St;

bool hasIt(int a,node *r);

struct Stack* create(unsigned capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack*));
    stack -> capacity = capacity;
    stack -> top = -1;
    stack -> array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack)
{
    return stack -> top == stack -> capacity - 1;
}

int isEmpty(struct Stack* stack)
{
    return stack->top == -1;
}

int frequency(int a, array b[])
{
    node *r;
    r = (node*)malloc(sizeof(node));
    int temp;
    int occurence;
    bool C;

    for(int i=0;i<SIZE;i++)
    {
            temp = b[i];
            C = hasIt(r,temp);
        if(C == 0)
        {
            r -> data = temp;
            r -> occur = r -> occur+1;
            r->next = (node*)malloc(sizeof(node));
        }
    }

    while(r->next != NULL)
    {
        if(r->data == a)
        {
           occurence = r ->occur;
        }
    }

    return occurence;
}


void push(struct Stack* stack, int item)
{
if (isFull(stack))
{
   return;
}
else
{
stack->array[++stack->top] = item;
printf("%d PUSHED \n", item);
}
}

int findmin(array values[])
{
    int min;
    min = values[0];

  for (int i = 1; i < SIZE; i++)
    if (values[i] < min)
    {
        min = values[i];
    }
    return min;

}

int pop(struct Stack* stack)
{
 if (isEmpty(stack))
 {
     return INT_MIN;
 }

else
{
    printf("POP occured\n", stack->top);
    return stack->array[stack->top--];
}

}

/*
int arraysize(array a[])
{

int size = sizeof(a)/sizeof(a[0]);

   return size;
}
*/

int peek(struct Stack* stack)
{
    if (isEmpty(stack))
    {
       return INT_MIN;
    }

    else
    {
        return stack->array[stack -> top];
    }
}

bool hasIt(int a,node *r)
{

while(r -> next ==! NULL)
{
    if(r -> data == a)
    {
        return 1;
    }
}
return 0;
}

int search(array values[],node *r)
{
    int searched;

    while(r -> next != NULL)
    {
        searched = r -> data;

       if(r -> data < r-> next -> data)
        {
r = r-> next;
        }

        else if(r -> data > r-> next -> data)
        {
           searched = r->next->data;
        }
             else
                {
r = r->next;
                }
    }
return searched;
}

int main(void)
{
    int user_input; // users input //

    puts("----------------FIFO START ----------------");
    puts("Please provide the max Stack count for FIFO"); // classic user identifier //

        scanf("%d",&user_input); // scanner for catching user input in order to use it as stack number //

        if(user_input <= 0)
        {
          puts("invalid input please type only integers > then 0"); // validation check for characters and negative integers could have used unsigned integer//
        }

        else
        {
         user_input = user_input; // if the scanf  value is valid then proceed with the rest of the code
        }

// --------------------------------------- START ----------------------------------------------- //

    struct Stack* St = create(user_input); //creating the stack with respect to user's input //

    counter ct = 0;
    pagefault pf = 0;
    checker ch = true; // after the stack is full pushing from old popped slots counts as page faults //

    for(int i = 0; i < 23 ; i++)
    {
        if(ct == user_input)
        {
         pop(St); // if the stack maxed out pop the value in order to empty it //
         pf++;
         ct--;
         ch = false;
        }

        else
        {
          push(St,staticvalues[i]); //push the values from static array //
          ct++;

          if(ch == true) //if the stack is full after the insertion don't count it as a page fault //
          {
              pf++;
          }
        }
    }

printf("\n%d page faults for FIFO\n" , pf);
puts("\n----------END----------\n");

    char a;
    a = getchar(); // For terminal to stay open until user enters a value //
    return 0;
}
//Algoritmayi daha iyi anlamak icin Sadi Evren Seker'in sitesinden yardim alinmistir. //
