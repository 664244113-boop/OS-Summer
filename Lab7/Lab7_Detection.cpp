#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 5;
    int m = 3;
    
    int alloc[5][3] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 3}, {2, 1, 1}, {0, 0, 2} };
    int request[5][3] = { {0, 0, 0}, {2, 0, 2}, {0, 0, 0}, {1, 0, 0}, {0, 0, 2} };
    int avail[3] = {0, 0, 0};

    bool finish[5] = {false};
    
    for(int i = 0; i < n; i++) {
        bool hasAlloc = false;
        for(int j = 0; j < m; j++) {
            if(alloc[i][j] > 0) hasAlloc = true;
        }
        if(!hasAlloc) finish[i] = true;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canFulfill = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) {
                        canFulfill = false;
                        break;
                    }
                }
                if (canFulfill) {
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    finish[i] = true;
                }
            }
        }
    }

    bool deadlock = false;
    vector<int> dl_processes;
    
    for(int i = 0; i < n; i++) {
        if(!finish[i]) {
            deadlock = true;
            dl_processes.push_back(i);
        }
    }

    cout << "=== Deadlock Detection ===" << endl;
    if(deadlock) {
        cout << "System is in DEADLOCK.\nDeadlocked processes: ";
        for(int p : dl_processes) {
            cout << "P" << p << " ";
        }
        cout << endl;
    } else {
        cout << "No Deadlock detected. System is running fine." << endl;
    }

    return 0;
}