#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>


using namespace std;

struct Process {
    int id;
    int burstTime;
    int priority;
    int arrivalTime;
    int remainingTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool comparePriority(const Process& p1, const Process& p2) {
    return p1.priority > p2.priority; // Higher priority comes first
}

void calculateWaitingTurnaroundTime(const vector<Process>& processes, vector<int>& waitingTime, vector<int>& turnaroundTime) {
    int n = processes.size();

    for (int i = 0; i < n; ++i) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }
}

void priorityScheduling(vector<Process>& processes, vector<int>& waitingTime, vector<int>& turnaroundTime) {
    int currentTime = 0;
    int n = processes.size();
    priority_queue<Process, vector<Process>, decltype(&comparePriority)> processQueue(comparePriority);

    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    sort(processes.begin(), processes.end(), compareArrivalTime);

    int idx = 0;

    while (idx < n || !processQueue.empty()) {
        while (idx < n && processes[idx].arrivalTime <= currentTime) {
            processQueue.push(processes[idx]);
            ++idx;
        }

        if (processQueue.empty()) {
            currentTime = processes[idx].arrivalTime;
            continue;
        }

        Process currentProcess = processQueue.top();
        processQueue.pop();

        int executeTime = min(currentProcess.remainingTime, 1); // Preemptive execution with time quantum of 1
        currentProcess.remainingTime -= executeTime;

        currentTime += executeTime;
        waitingTime[currentProcess.id - 1] += currentTime - currentProcess.burstTime;

        if (currentProcess.remainingTime > 0) {
            processQueue.push(currentProcess);
        }
    }

    calculateWaitingTurnaroundTime(processes, waitingTime, turnaroundTime);
}

int main() {
    int numProcesses;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);
    vector<int> waitingTime(numProcesses, 0);
    vector<int> turnaroundTime(numProcesses, 0);

    cout << "Enter burst times for processes:" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cin >> processes[i].burstTime;
    }

    cout << "Enter arrival times for processes:" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter priority values for processes:" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        cin >> processes[i].priority;
    }

    priorityScheduling(processes, waitingTime, turnaroundTime);

    // Print the results
    cout << "Sample Output:" << endl;
    for (int i = 0; i < numProcesses; ++i) {
        cout << "Process " << processes[i].id << " : Waiting Time : " << waitingTime[i] << " Turnaround Time : " << turnaroundTime[i] << endl;
    }

    // Calculate and print average waiting and turnaround time
    double avgWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / numProcesses;
    double avgTurnaroundTime = accumulate(turnaroundTime.begin(), turnaroundTime.end(), 0.0) / numProcesses;

    cout << "Average Waiting time : " << avgWaitingTime << endl;
    cout << "Average Turnaround time : " << avgTurnaroundTime << endl;

    return 0;
}
