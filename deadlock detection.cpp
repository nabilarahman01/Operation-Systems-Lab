#include<bits/stdc++.h>
using namespace std;

map<char, vector<char>> process;
map<char, bool> is_visited;
vector<char> in_queue;
vector<vector<char>> cycle_list;

void insert_list(int from) {
    vector<char> curr_list;
    for (int i = from; i < in_queue.size(); ++i) {
        curr_list.push_back(in_queue[i]);
    }
    cycle_list.push_back(curr_list);
}

void modified_dfs(char c) {
    is_visited[c] = true;
    for (int i = 0; i < in_queue.size(); ++i) {
        if (in_queue[i] == c) {
            insert_list(i);
            return;
        }
    }
    in_queue.push_back(c);
    for (int i = 0; i < process[c].size(); ++i) {
        modified_dfs(process[c][i]);
    }
    for (int i = 0; i < in_queue.size(); ++i) {
        if (in_queue[i] == c) {
            in_queue.erase(in_queue.begin() + i);
            break;
        }
    }
}



int main() {
    int n_process;
    cout << "Number of nodes : ";
    cin >> n_process;
    cout << "Node Names : ";
    for (int i = 0; i < n_process; ++i) {
        char p;
        cin >> p;
        vector<char> p_edges;
        process.insert({p, p_edges});
    }
    int n_edge;
    cout << "Number of edges : ";
    cin >> n_edge;
    cout << "Edges : " << endl;
    for (int i = 0; i < n_edge; ++i) {
        char u, v;
        cin >> u >> v;
        process[u].push_back(v);
    }

    for (map<char, vector<char>>::iterator it = process.begin(); it != process.end(); ++it) {
        in_queue.clear();
        if(!is_visited[(*it).first]) {
            modified_dfs((*it).first);
        }
    }

    if (cycle_list.size() == 0) {
        cout << "No deadlock detected." << endl;
    }
    else {
        cout << "Deadlock Detected Among nodes :" << endl;
        for (int i = 0; i < cycle_list.size(); ++i) {
            for (int j = 0; j < cycle_list[i].size(); ++j) {
                cout << cycle_list[i][j] << " ";
            }
            cout << endl;
        }
    }
}
