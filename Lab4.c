#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


typedef int array;
typedef int counter;
typedef int pagefault;
typedef bool checker;

typedef struct Stack
{
    int top;
    unsigned capacity;
    int* array;
}S;

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

void push(struct Stack* stack, int item)
{
if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("%d PUSHED \n", item);
}

int pop(struct Stack* stack)
{
 if (isEmpty(stack))
    return INT_MIN;

    printf("%d POP'ed \n", stack->top);
    return stack->array[stack->top--];
}

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

void displaystack()
{

}

int main()
{
    array staticvalues[] = {1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 4, 3, 7, 6, 6, 5, 3, 2, 1, 2, 3, 6}; // static values //
    int user_input; // users input //

    puts("Please provide the input"); // classic user identifier //

        scanf("%d",&user_input); // scanner for catching user input in order to use it as stack number //

        if(user_input <= 0)
        {
          puts("invalid input please type only integers > then 0"); // validation check for characters and negative integers could have used unsigned integer//
        }

        else
        {
         user_input = user_input; // if the scanf  value is valid then proceed with the rest of the code
        }


// --------------------------------------- FIFO ----------------------------------------------- //

    struct Stack* St = create(user_input); //creating the stack with respect to user's input //

    counter ct = 0;
    pagefault pf = 0;
    checker ch = false; // after the stack is full pushing from old popped slots counts as page faults //

    for(int i = 0; i < 23 ; i++)
    {
        if(ct == user_input)
        {
         pop(St); // if the stack maxed out pop the value in order to empty it //
         pf++;
         ct--;
         ch = true;
        }

        else
        {
          push(St,staticvalues[i]); //push the values from static array //
          ct++;
          if(ch == true)
          {
              pf++;
          }
        }
    }
    printf("%d page faults" , pf);

    char a;
    a =getchar();

    return 0;
}

