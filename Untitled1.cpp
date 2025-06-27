#include <bits/stdc++.h>

using namespace std;

int arr_ref[1000];

void fifo(int n_ref, int n_frame) {
    list<int> page_list;
    list<int>::iterator it;
    int page_faults = 0;

    for (int i = 0; i < n_ref; ++i) {
        it = find(page_list.begin(), page_list.end(), arr_ref[i]);

        if (it == page_list.end()) {
            if (page_list.size() == n_frame) {
                page_list.pop_front();
            }
            page_list.push_back(arr_ref[i]);
            ++page_faults;
        }
    }

    cout << "Number of page faults using FIFO Page Replacement Algorithm: " << page_faults << endl;
    cout << "Page Fault Rate: " << (int)round(page_faults * 100.00 / n_ref) << "%" << endl;
}

void lru(int n_ref, int n_frame) {
    list<int> page_list;
    list<int>::iterator it;
    int page_faults = 0;

    for (int i = 0; i < n_ref; ++i) {
        it = find(page_list.begin(), page_list.end(), arr_ref[i]);

        if (it == page_list.end()) {
            if (page_list.size() == n_frame) {
                page_list.pop_front();
            }
            page_list.push_back(arr_ref[i]);
            ++page_faults;
        } else {
            int temp = *it;
            page_list.erase(it);
            page_list.push_back(temp);
        }
    }

    cout << "Number of page faults using Least Recently Used Page Replacement Algorithm: " << page_faults << endl;
    cout << "Page Fault Rate: " << (int)round(page_faults * 100.00 / n_ref) << "%" << endl;
}

int main() {
    int n_page, n_ref, n_frame;

    cout << "Number of pages: ";
    cin >> n_page;

    cout << "Number of Page References: ";
    cin >> n_ref;

    cout << "Reference String: ";
    for (int i = 0; i < n_ref; ++i) {
        cin >> arr_ref[i];
        cin.ignore();
    }

    cout << "Number of Memory Page Frames: ";
    cin >> n_frame;

    fifo(n_ref, n_frame);
    lru(n_ref, n_frame);

    return 0;
}
