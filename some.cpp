#include <bits/stdc++.h>
using namespace std;

int arr_ref[]={7,0,1,2,0,3,0,4,2,3,0,3,0,3,2,1,2,0,1,7,0,1};

void printMemoryState(const list<int>& memory) {
    cout << "Memory State: ";
    for (int page : memory) {
        cout << page << " ";
    }
    cout << endl;
}

void fifo(int n_ref, int n_frame) {
    cout<< "\n----First in First out----\n"<< endl;
    list<int> lst;
    list<int>::iterator it;
    int miss = 0;
    for (int i = 0; i < n_ref; ++i) {
        it = find(lst.begin(), lst.end(), arr_ref[i]);

        cout << "Page Reference: " << arr_ref[i] << endl;

        if (it == lst.end()) {
            if (lst.size() == n_frame) {
                cout << "Page Replaced: " << lst.front() << " ";
                lst.pop_front();
            }
            lst.push_back(arr_ref[i]);
            cout << "Page Added: " << arr_ref[i] << " "<< endl;
            ++miss;
            printMemoryState(lst);
        }

    }

    cout << "\nNumber of page fault using FIFO Page replacement Algorithm: " << miss << endl;
    cout << "Page Fault Rate: " << (int)round(miss * 100.00 / n_ref) << "%" << endl;
}

void lru(int n_ref, int n_frame) {

    cout<< "\n----Least Recently Used----\n"<< endl;
    list<int> lst;
    list<int>::iterator it;
    int miss = 0;
    for (int i = 0; i < n_ref; ++i) {
        it = find(lst.begin(), lst.end(), arr_ref[i]);

        cout << "Page Reference: " << arr_ref[i] << " ";

        if (it == lst.end()) {
            if (lst.size() == n_frame) {
                cout << "Page Replaced: " << lst.front() << " ";
                lst.pop_front();
            }
            lst.push_back(arr_ref[i]);
            cout << "Page Added: " << arr_ref[i] << endl;
            ++miss;
            printMemoryState(lst);
        } else {
            int temp = *it;
            lst.erase(it);
            lst.push_back(temp);
            cout << endl;
        }
    }

    cout << "\nNumber of page fault using Least Recently Used Page replacement Algorithm: " << miss << endl;
    cout << "Page Fault Rate: " << (int)round(miss * 100.00 / n_ref) << "%" << endl;
}

int main() {
    int n_page=8, n_ref=22, n_frame;
    /*cout << "Number of pages: ";
    cin >> n_page;

    cout << "Number of Page References: ";
    cin >> n_ref;

    cout << "Reference String: ";
    for (int i = 0; i < n_ref; ++i) {
        cin >> arr_ref[i];
        cin.ignore();
    }*/

    cout << "Number of Memory Page Frame: ";
    cin >> n_frame;

    fifo(n_ref, n_frame);
    lru(n_ref, n_frame);

    return 0;
}
