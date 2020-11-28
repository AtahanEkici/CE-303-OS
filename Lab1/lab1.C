#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>

int fibbonacci(int num);

int main() 
{
    
    pid_t pid1;
    
    int n;
    int i;
    int counter = 1;
    
    printf("Enter an integer: ");
    scanf("%d" , &n);
    
    pid1 = fork();
    
    if(pid1 == 0) // Child process //
    {
        printf("Fibbonacci of %d: " , n);

   for(i = 0;i<n;i++) 
   {
      printf("%d ",fibbonacci(i));
   }
 }
    else // Parent Process //
    {
        wait(&pid1);
    }
}

int fibbonacci(int num)
{
   if(num == 0)
   {
      return 0;
   } else if(num == 1) 
   {
      return 1;
   } else 
   {
      return (fibbonacci(num-1) + fibbonacci(num-2));
   }
}