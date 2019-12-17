#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{

typedef int matrix;
typedef char stopper;
typedef int variable;
typedef int counter;


variable a;
variable b;
variable c;
variable d;
variable e;

counter j;

bool identifier = false;

    a = 5; // Number OF Processes
    b = 3; // Number of Resources

    matrix available[3] = { 3, 3, 2 }; // Available Resources //

    matrix allocation[5][3] = { { 0, 1, 0 },{ 2, 0, 0 }, { 3, 0, 2 }, { 2, 1, 1 }, { 0, 0, 2 } }; // Matrix of Allocation //

    matrix max[5][3] = { { 8, 5, 3 },{ 3, 2, 2 },{ 9, 0, 2 },{ 6, 2, 2 },{ 4, 5, 3 } }; // Matrix of Limit - Max //


    int f[a], answer[a], ind = 0;
    for (e = 0; e < a; e++) {
        f[e] = 0;
    }
    int need[a][b];
    for (c = 0; c < a; c++) {
        for (d = 0; d < b; d++)
            need[c][d] = max[c][d] - allocation[c][d];
    }
    int y = 0;
    for (e = 0; e < 5; e++) {
        for (c = 0; c < a; c++) {
            if (f[c] == 0) {

                for (d = 0; d < b; d++) {
                    if (need[c][d] > available[d]){
                        identifier = true;
                        j++; // counter //
                         break;
                    }
                }

                if (identifier = false)
                    {
                    answer[ind++] = c;
                    for (y = 0; y < b; y++)
                        available[y] += allocation[c][y];
                    f[c] = 1;
                }
            }
        }
    }


    if (j > a - 1)
    {
        puts("The Sequence Is Not Safe");
    }

    else

    {

    puts("\nThe safe state for this sequence is the following : ");

    for (c = 0; c < a - 1; c++)
    {
    printf("  P%d ->", answer[c]);
    printf("  P%d", answer[a - 1]);
    }


    puts("\n");

    stopper z ;
    z = getchar(); // this line is for DEV C++ users that don't support command prompt stopping after execution function //

    }
    return 0; // traditional //
}
