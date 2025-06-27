#include<bits/stdc++.h>
using namespace std;

class Process
{
public:
    string processName;
    int arrivalTime;
    int CPUTime;
    int priority;
    int id;

    int remainingTime;

    int responseTime;
    int completionTime;

    int waitingTime;
    int turnAroundTime;

    void initialize()
    {
        remainingTime = CPUTime;
    }
};

int main()
{
    int n;
    cout << "Enter number of process: ";
    cin >> n;

    Process processes[n];

    cout << "Enter the CPU times "  << ": ";
    for(int i=0; i<n; i++)
    {

        cin >> processes[i].CPUTime;
    }
    cout << "Enter the arrival times "  << ": ";
    for(int i=0; i<n; i++)
    {

        cin >> processes[i].arrivalTime;
        processes[i].id=i+1;

    }
    cout << "Enter the priority values"  << ": ";
    for(int i=0; i<n; i++)
    {


        cin >> processes[i].priority;

        processes[i].initialize();
    }

    cout << endl;
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(processes[j].arrivalTime < processes[i].arrivalTime)
            {
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }

    int currentTime = 0;

    while(true)
    {

        int currentHighestPriorityIndex = -1;
        int currentHighestPriority = numeric_limits<int>::max();

        bool isAllCompleted = true;

        for(int i=0; i<n; i++)
        {
            if(processes[i].remainingTime > 0)
            {
                isAllCompleted = false;
                if(processes[i].arrivalTime <= currentTime)
                {
                    if(processes[i].priority < currentHighestPriority)
                    {
                        currentHighestPriority = processes[i].priority;
                        currentHighestPriorityIndex = i;
                    }

                    if(processes[i].priority == currentHighestPriority)
                    {


                        if(processes[i].arrivalTime <processes[currentHighestPriorityIndex].arrivalTime  )
                        {
                            currentHighestPriority = processes[i].priority;
                            currentHighestPriorityIndex = i;
                        }
                    }

                }
            }
        }
        if(isAllCompleted)
        {
            break;
        }


        processes[currentHighestPriorityIndex].remainingTime--;
        currentTime++;

        if(processes[currentHighestPriorityIndex].remainingTime == 0)
        {
            processes[currentHighestPriorityIndex].completionTime = currentTime;
        }
    }


    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;
    int idd[n], x, i;

    for(i=0; i<n; i++)
    {

        x = processes[i].id;
        idd[x - 1] = i;

        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].CPUTime;


        sumCompletionTime += processes[i].completionTime;
        sumWaitingTime += processes[i].waitingTime;
        sumTurnAroundTime += processes[i].turnAroundTime;
    }
    for (x = 0; x < n; x++)
    {
        i = idd[x];
        cout<<"Process"<<processes[i].id<<" : Waiting time: "<<processes[i].waitingTime<<"\tTurnaround time: "<<processes[i].turnAroundTime<<endl;
    }

    cout << "\nAverage Waiting Time    : "  << (float) sumWaitingTime/n;
    cout << "\nAverage Turn Around Time: " << (float) sumTurnAroundTime/n<<"\n";

    return 0;
}

