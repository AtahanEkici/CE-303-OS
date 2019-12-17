#include<stdio.h>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bits/stdc++.h>

#define totalprocess 5

//Tested on Windows 10_1903_18362.449 //

using namespace std;

struct process
{
int at,bt,pr,pno;
};

process proc[50];

/* FCFS */

void findWaitingTime(int processes[], int n,
						int bt[], int wt[])
{
    wt[0] = 0;

	for (int  i = 1; i < n ; i++ )
        wt[i] =  bt[i-1] + wt[i-1] ;
}

void findTurnAroundTime( int processes[], int n,
				int bt[], int wt[], int tat[])
{

	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

void findavgTime( int processes[], int n, int bt[])
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTime(processes, n, bt, wt);

	findTurnAroundTime(processes, n, bt, wt, tat);

	printf("Processes   Burst time     Waiting time        Turn around time\n");

	for (int i=0; i<n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		printf("  %d ",(i+1));
		printf("	       %d ", bt[i] );
		printf("	       %d",wt[i] );
		printf("	       %d\n",tat[i] );
	}
	int s=(float)total_wt / (float)n;
	int t=(float)total_tat / (float)n;
	printf("Average waiting time = %d",s);
	printf("\n");
	printf("Average turn around time = %d ",t);
}
/* FCFS */




/* ROUND ROBIN */

void findWaitingTimeRR(int processes[], int n,
             int bt[], int wt[], int quantum)
{

    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] =  bt[i];

    int t = 0;

    while (1)
    {
        bool done = true;

        for (int i = 0 ; i < n; i++)
        {

            if (rem_bt[i] > 0)
            {
                done = false;

                if (rem_bt[i] > quantum)
                {

                    t += quantum;

                    rem_bt[i] -= quantum;
                }


                else
                {

                    t = t + rem_bt[i];


                    wt[i] = t - bt[i];


                    rem_bt[i] = 0;
                }
            }
        }


        if (done == true)
          break;
    }
}


void findTurnAroundTimeRR(int processes[], int n,
                        int bt[], int wt[], int tat[])
{

    for (int i = 0; i < n ; i++)
        tat[i] = bt[i] + wt[i];
}


void findavgTimeRR(int processes[], int n, int bt[],
                                     int quantum)
{
    int wt[n], tat[n], total_wt = 0, total_tat = 0;


    findWaitingTimeRR(processes, n, bt, wt, quantum);


    findTurnAroundTimeRR(processes, n, bt, wt, tat);



    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << i+1 << "\t\t" << bt[i] <<"\t "
             << wt[i] <<"\t\t " << tat[i] <<endl;
    }

    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}

/* ROUND ROBIN */



/* SJF */

int mat[10][6];

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void arrangeArrival(int num, int mat[][6])
{
    for(int i=0; i<num; i++)
    {
        for(int j=0; j<num-i-1; j++)
        {
            if(mat[j][1] > mat[j+1][1])
            {
                for(int k=0; k<5; k++)
                {
                    swap(mat[j][k], mat[j+1][k]);
                }
            }
        }
    }
}

void completionTime(int num, int mat[][6])
{
    int temp, val;
    mat[0][3] = mat[0][1] + mat[0][2];
    mat[0][5] = mat[0][3] - mat[0][1];
    mat[0][4] = mat[0][5] - mat[0][2];

    for(int i=1; i<num; i++)
    {
        temp = mat[i-1][3];
        int low = mat[i][2];
        for(int j=i; j<num; j++)
        {
            if(temp >= mat[j][1] && low >= mat[j][2])
            {
                low = mat[j][2];
                val = j;
            }
        }
        mat[val][3] = temp + mat[val][2];
        mat[val][5] = mat[val][3] - mat[val][1];
        mat[val][4] = mat[val][5] - mat[val][2];
        for(int k=0; k<6; k++)
        {
            swap(mat[val][k], mat[i][k]);
        }
    }
}

/* SJF */

bool comp(process a,process b)
{
if(a.at == b.at)
{
return a.pr<b.pr;
}
else
{
    return a.at<b.at;
}
}

void get_wt_time(int wt[])
{

int service[50];


service[0]=0;
wt[0]=0;


for(int i=1;i<totalprocess;i++)
{
service[i]=proc[i-1].bt+service[i-1];

wt[i]=service[i]-proc[i].at+1;


    if(wt[i]<0)
    {
    wt[i]=0;
    }
}

}

void get_tat_time(int tat[],int wt[])
{


for(int i=0;i<totalprocess;i++)
{
    tat[i]=proc[i].bt+wt[i];
}

}

void findgc()
{
int wt[50],tat[50];

double wavg=0,tavg=0;

get_wt_time(wt);

get_tat_time(tat,wt);

int stime[50],ctime[50];
stime[0]=1;
ctime[0]=stime[0]+tat[0];

for(int i=1;i<totalprocess;i++)
    {
        stime[i]=ctime[i-1];
        ctime[i]=stime[i]+tat[i]-wt[i];
    }

cout<<"Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time"<<endl;

for(int i=0;i<totalprocess;i++)
    {
        wavg += wt[i];
        tavg += tat[i];

        cout<<proc[i].pno<<"\t\t"<<
            stime[i]<<"\t\t"<<ctime[i]<<"\t\t"<<
            tat[i]<<"\t\t\t"<<wt[i]<<endl;
    }

    cout<<"Average waiting time is : ";
    cout<<wavg/(float)totalprocess<<endl;
    cout<<"average turnaround time : ";
    cout<<tavg/(float)totalprocess<<endl;

}


int main()
{
      // FCFS //


    puts("\n\n------- FCFS ------\n");

	int processes[] = { 1, 2, 3 , 4 , 5};

	int n = sizeof processes / sizeof processes[0];

	int burst_time[] = {10, 1, 2 , 3 , 5};

	findavgTime(processes, n, burst_time);





	puts("\n\n------- ROUND ROBIN ------\n");
    printf("Processes   Burst time     Waiting time        Turn around time\n");



	// ROUND ROBIN //

	int quantum = 2;
    findavgTimeRR(processes, n, burst_time, quantum);




    // SJF //

    puts("\n\n ------ SJF ------ \n\n");

    int num;

    num = 5;

    for(int i=0; i<num; i++)
    {

        mat[0][0] = 1 , mat[1][0] = 2 , mat[2][0] = 3 , mat[3][0] = 4 , mat[4][0] = 5;
        mat[0][1] = 0 , mat[1][1] = 0 , mat[2][1] = 0 , mat[3][1] = 0 , mat[4][1] = 0;
        mat[0][2] = 10 , mat[1][2] = 1 , mat[2][2] = 2 , mat[3][2] = 3 , mat[4][2] = 5;
    }
    arrangeArrival(num, mat);
    completionTime(num, mat);

    cout<<"Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for(int i=0; i<num; i++)
    {
        cout<<mat[i][0]<<"\t\t"<<mat[i][1]<<"\t\t"<<mat[i][2]<<"\t\t"<<mat[i][4]<<"\t\t"<<mat[i][5]<<"\n";
    }


    // PRIORITY //


    puts("\n\n ------ PRIORITY ------ \n\n");

int arrivaltime[] = { 0, 0 , 0 , 0 , 0};
int bursttime[] = { 10 , 1 ,  2, 3 , 5};
int priority[] = { 3 , 4 , 1 , 7 , 8 };

for(int i=0;i<totalprocess;i++)
{
    proc[i].at=arrivaltime[i];
    proc[i].bt=bursttime[i];
    proc[i].pr=priority[i];
    proc[i].pno=i+1;
    }

    sort(proc,proc+totalprocess,comp);

    findgc();

	return 0;
}

