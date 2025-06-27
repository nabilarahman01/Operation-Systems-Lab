#include<iostream>
#include<vector>
using namespace std;

bool is_need_available(int *need, int *work, int n) {
    for (int i = 0; i < n; ++i) {
        if (need[i] > work[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int n_process;
    cout << "Enter the no. of processes:";
    cin >> n_process;

    cout<<endl;
    int n_resource;
    cout << "Enter the no. of resources:";
    cin >> n_resource;

    int total_resource[n_resource];
    int available[n_resource];
    int allocation[n_process][n_resource];
    int max[n_process][n_resource];
    int need[n_process][n_resource];

    for (int i = 0; i < n_process; ++i) {
        cout<<endl;
        cout << "Process " << i + 1 << endl;
        for (int j = 0; j < n_resource; ++j) {
            cout << "Maximum value for resource " << j + 1 << ":";
            cin >> max[i][j];
        }
        for (int j = 0; j < n_resource; ++j) {
            cout << "Allocated from resource " << j + 1 << ":";
            cin >> allocation[i][j];
        }
        for (int j = 0; j < n_resource; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    cout<<endl;
    for (int i = 0; i < n_resource; ++i) {
        cout << "Enter total value of resource " << i + 1 << ":";
        cin >> total_resource[i];
    }

    for (int i = 0; i < n_resource; ++i) {
        available[i] = total_resource[i];
    }

    for (int i = 0; i < n_process; ++i) {
        for (int j = 0; j < n_resource; ++j) {
            available[j] -= allocation[i][j];
        }
    }

    bool is_finished[n_process] = {false};
    int work[n_resource];
    for (int i = 0; i < n_resource; ++i) {
        work[i] = available[i];
    }

    vector<int> safe_seq;

    while (true) {
        bool found = false;
        for (int i = 0; i < n_process; ++i) {
            if (is_finished[i]) {
                continue;
            }
            if (is_need_available(need[i], work, n_resource)) {
                for (int j = 0; j < n_resource; ++j) {
                    work[j] += allocation[i][j];
                }
                safe_seq.push_back(i);
                is_finished[i] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            break;
        }
    }

    bool all_completed = true;
    for (int i = 0; i < n_process; ++i) {
        if (!is_finished[i]) {
            all_completed = false;
            break;
        }
    }

    if(all_completed) {
        cout << "/nThe System is currently in safe state and < ";
        for (int i = 0; i < safe_seq.size(); ++i) {
            cout << "P" << safe_seq[i] + 1 << " ";
        }
        cout << "> is the safe sequence.";
    } else {
        cout << "No safe sequence found.";
    }

    return 0;
}
