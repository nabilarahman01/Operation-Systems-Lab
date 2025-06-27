#include<bits/stdc++.h>
using namespace std;

struct Process {
    int arrivalTime;
    int cpuTime;
    int startTime;
    int endTime;
    int waitingTime;
    int lastWorkingTime;
    int turnaroundTime;
    int index;
    bool inQueue;
};

bool comparator(Process a, Process b)
{
    return a.arrivalTime < b.arrivalTime;
}

bool comparator_index(Process a, Process b)
{
    return a.index < b.index;
}

int main()
{
    queue<Process> rrq;
    int n;
    cout << "Enter the number of process: ";
    cin >> n;
    Process arr[n];
    cout << "Enter time quantum: ";
    int q;
    cin >> q;




    cout << "Enter the CPU times" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].cpuTime;
    }

    cout << "Enter the arrival times" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].arrivalTime;
        arr[i].turnaroundTime = arr[i].cpuTime;
        arr[i].index = i;
        arr[i].lastWorkingTime = -1;
        arr[i].inQueue = false;
        // if (minTime > arr[i].arrivalTime) {
        //     minTime = arr[i].arrivalTime;
        //     minProcess = i;
        // }
    }



    sort(arr, arr + n, comparator);
    arr[0].inQueue = true;
    rrq.push(arr[0]);

    vector<Process> vec;

    int currTime = 0;
    while (!rrq.empty()) {
        Process curr = rrq.front();
        rrq.pop();
        // cout << currTime << " " << curr.index + 1 << endl;
        if (currTime - curr.lastWorkingTime != 0 && curr.lastWorkingTime != -1) {
            curr.waitingTime += (currTime - curr.lastWorkingTime);
        }

        if (curr.lastWorkingTime == -1) {
            curr.waitingTime = (currTime - curr.arrivalTime);
        }
        if (curr.cpuTime > q) {
            currTime += q;
            curr.cpuTime -= q;
        }
        else {
            currTime += curr.cpuTime;
            curr.cpuTime = 0;
        }
        curr.lastWorkingTime = currTime;
        // cout << curr.index + 1 << " " <<  curr.lastWorkingTime << " " << curr.waitingTime << endl;

        for (int i = 0; i < n; ++i) {
            // if (curr.index == arr[i].index) {
            //     arr[i] = curr;
            // }
            if (arr[i].inQueue) {
                continue;
            }
            if (currTime >= arr[i].arrivalTime) {
                // cout << "Comparing index Time: " << currTime << " " << arr[i].arrivalTime << " " << arr[i].index + 1 << endl;
                arr[i].inQueue = true;
                rrq.push(arr[i]);
            }
        }
        if (curr.cpuTime > 0) {
            rrq.push(curr);
        } else {
            vec.push_back(curr);
        }
    }

    sort(vec.begin(), vec.end(), comparator_index);

    cout << endl;
    float sumWaitingTime = 0;
    float sumTurnaroundTime = 0;
    for (int i = 0; i < vec.size(); ++i) {
        vec[i].turnaroundTime += vec[i].waitingTime;
        cout << "Process " << i + 1 << " : Waiting Time : " << vec[i].waitingTime << "\tTurnaround Time : " << vec[i].turnaroundTime << endl;
        sumWaitingTime += vec[i].waitingTime;
        sumTurnaroundTime += vec[i].turnaroundTime;
    }
    cout << endl;
    cout << "Average Waiting Time : " << sumWaitingTime/n << endl;
    cout << "Average Turnaround Time : " << sumTurnaroundTime/n << endl;
}
