#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

typedef pid_t pid;

void lab_1();

int main(void)
{
    lab_1();
// This Program written using CppDroid For Android since Windows does not support fork() system call //
}

void lab_1()
{
    long int end_number;
    pid pid;
    long int counter = 1;
    pid = fork();

    if(pid == 0)
    {
        long int before = 0;
        long int after = 1;
        long int aft = after;

        puts("Please provide a number bigger than 0\n");
    scanf("%ld" , &end_number);

        if(end_number <= 0)
        {
           puts("Wrong Input");
           lab_1();
        }

        else
        {

        while(counter <= end_number)
        {
            printf("\n %ld) %ld \n" , counter , before);
            after = before + after;
            before = aft;
            aft = after;
            counter++;
        }
    }
        }

    else if(pid > 0) // Parent Process //
    {
        wait(&pid); // Waits for the Child //
        fflush(stdout);
    }
}
