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
    if(A.arrivalTime < B.arrivalTime){
        return true;
    }
    if (A.arrivalTime = B.arrivalTime)
    {
        return A.cpuTime < B.cpuTime;
    }
    else return false;
}


int main()
{
    int len;
    cout << "Enter the number of process: "<< endl;
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

    sort(processList, processList+len, comparator);
    processList[0].startingTime = 0;
    processList[0].waitingTime = 0;
    processList[0].turnAroundTime = processList[0].cpuTime;
    for(int i = 1; i < len; ++i)
    {
        int temp = processList[i - 1].startingTime + processList[i - 1].cpuTime;
        processList[i].startingTime = temp;
        processList[i].waitingTime = temp - processList[i].arrivalTime;
        processList[i].turnAroundTime = processList[i].waitingTime + processList[i].cpuTime;
    }

    cout<<endl;

    cout<< "Process" << "\t Waiting Time:" << "\tTurnaround Time: " << endl;
    for(int i = 0; i < len; ++i)
    {
        cout << processList[i].listedName<< "\t\t" << processList[i].waitingTime<< "\t\t" <<  processList[i].turnAroundTime << endl;
    }

    cout << endl;

    cout<< "Gantt Chart:"<< "\n\t";
    for(int i=0; i<len; ++i)
    {
        cout << "P" << processList[i].listedName<< "\t";
    }
    cout<< endl;
    int ct=0;
    cout << "0\t";
    for(int i=0; i<len; ++i)
    {
        ct+=processList[i].cpuTime;
        cout<< ct<< "\t";
    }
    cout << endl;
    return 0;
}
