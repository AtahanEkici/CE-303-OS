#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

typedef pid_t pid;

int main(void)
{
    int end_number;
    pid pid;
    long int counter = 1;
    pid = fork();

    if(pid == 0)
    {
        int before = 0;
        int after = 1;
        int aft = after;

        puts("Please provide a number bigger than 0\n");
    scanf("%d" , &end_number);

        if(end_number <= 0)
        {
           puts("Wrong Input");
        }

        else
        {

        while(counter <= end_number)
        {
            printf("\n %ld)%d \n" , counter , before);
            after = before + after;
            before = aft;
            aft = after;
            counter++;
        }
    }
        }

    else
    {
        wait(&pid);
        fflush(stdout);
    }

}

