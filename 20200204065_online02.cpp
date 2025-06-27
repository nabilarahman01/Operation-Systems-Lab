#include<bits/stdc++.h>
using namespace std;

struct Process
{
    int arrivalTime;
    int cpuTime;
    int waitingTime;
    int turnAroundTime;
    int listedName;
    int startingTime;
};

bool comparator(Process A, Process B)
{
    return A.arrivalTime < B.arrivalTime;
}


int main()
{
    int len;
    cout << "Enter the number of process: ";
    cin >> len;
    Process processList[len];

    cout << "Enter the CPU times: " << endl;
    for(int i = 0; i < len; ++i)
    {
        processList[i].listedName = i + 1;
        cin >> processList[i].cpuTime;
    }

    cout << "Enter the Arrival times: " << endl;
    for(int i = 0; i < len; ++i)
    {
        cin >> processList[i].arrivalTime;
    }
    sort(processList, processList + len, comparator);
    processList[0].startingTime = 0;
    processList[0].waitingTime = 0;
    processList[0].turnAroundTime = processList[0].cpuTime;
    for(int i = 1; i < len; ++i)
    {
        int temp = processList[i - 1].startingTime + processList[i - 1].cpuTime;
        if(processList[i].arrivalTime > temp)
        {
            processList[i].startingTime = processList[i].arrivalTime;
            processList[i].waitingTime = 0;
        }
        else
        {
            processList[i].startingTime = temp;
            processList[i].waitingTime = temp - processList[i].arrivalTime;
        }
        processList[i].turnAroundTime = processList[i].waitingTime + processList[i].cpuTime;
    }
    float sumWaitingTime = 0;
    float sumTurnaroundTime = 0;
    for(int i = 0; i < len; ++i)
    {
        cout << "Process " << processList[i].listedName << ": Waiting Time: " << processList[i].waitingTime << "\tTurnaround Time: " << processList[i].turnAroundTime << endl;
        sumWaitingTime += processList[i].waitingTime;
        sumTurnaroundTime += processList[i].turnAroundTime;
    }
    cout<< "Gantt Chart: "<<endl;
    for(int i=0; i<len; ++i)
    {
        cout << "P" << processList[i].listedName<< "     ";
    }
    cout<< endl;
    int ct=0;
    for(int i=0; i<len; ++i)
    {
        ct+=processList[i].cpuTime;
        cout<< ct<< "\t";
    }
    return 0;
}
