#include<bits/stdc++.h>
using namespace std;

bool is_need_available(int *need, int *work, int n)
{
    for(int i=0;i<n;i++){
        if(need[i] > work[i]){
            return false;
        }
    }
    return true;
}

int main(){

    int n_process;
    cout<< "enter the number of processes: ";
    cin>> n_process;

    int n_resource;
    cout<< "enter the number of resources: ";
    cin>> n_resource;

    int total[n_resource];
    int available[n_resource];
    int alloc[n_process][n_resource];
    int max[n_process][n_resource];
    int need[n_process][n_resource];

    for(int i=0; i<n_process; i++){
        cout<< "process"<< i+1 << endl;
        for(int j=0; j<n_resource; j++){
            cout<< "maximum value for resource" << j+1 << ":";
            cin>> max[i][j];
        }
        for(int j=0; j<n_resource; j++){
            cout<< "allocation for resource" << j+1 << ":";
            cin>> alloc[i][j];
        }
        for(int j=0; j<n_resource; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    for(int i=0; i<n_resource; i++){
        cout<< "Total amount of resource"<< i+1<<":";
        cin>> total[i];
    }

    for(int i=0; i<n_resource; i++){
        available[i]=total[i];
    }

    for(int i=0; i<n_process; i++){
        for(int j=0; j<n_resource; j++){
            available[j]-= alloc[i][j];
        }
    }

    bool is_finished[n_process]={false};
    int work[n_resource];
    vector<int> safeSeq;

    for(int j=0; j<n_resource; j++){
        work[j]=available[j];
    }

    while(true){
        bool found=false;
        for(int i=0; i<n_process; i++){
            if(is_finished[i]){
                continue;
            }

            if(is_need_available(need[i], work, n_resource)){
                for(int j=0; j<n_resource; j++){
                    work[j]+=alloc[i][j];
                }

                safeSeq.push_back(i);
                is_finished[i]=true;
                found=true;
                break;
            }
        }

        if(!found){
            break;
        }

    }

    bool complete= true;
    for(int i=0; i<n_process; i++){
        if(!is_finished[i]){
            complete= false;
            break;
        }
    }

    if(complete){
        cout<<"safe sequence found"<<endl;
        cout<< "safe sequence is <";
        for(int i=0; i<safeSeq.size(); i++){
            cout<< "P"<< safeSeq[i]+1;
        }
        cout<<">";
    }
    else{
        cout<<"not found"<<endl;
    }

    return 0;
}
