#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 5;
    int m = 3;
    
    int alloc[5][3] = { {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2} };
    int max_need[5][3] = { {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3} };
    int avail[3] = {3, 3, 2};
    int need[5][3];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max_need[i][j] - alloc[i][j];
        }
    }

    bool finish[5] = {false};
    vector<int> safeSeq;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAlloc = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAlloc = false;
                        break;
                    }
                }
                if (canAlloc) {
                    for (int y = 0; y < m; y++) {
                        avail[y] += alloc[i][y];
                    }
                    safeSeq.push_back(i);
                    finish[i] = true;
                }
            }
        }
    }

    cout << "=== Deadlock Avoidance (Banker's Algorithm) ===" << endl;
    if (safeSeq.size() == n) {
        cout << "System is in a SAFE state.\nSafe Sequence: ";
        for (int i = 0; i < n; i++) {
            cout << "P" << safeSeq[i] << (i == n - 1 ? "" : " -> ");
        }
        cout << endl;
    } else {
        cout << "System is in an UNSAFE state!" << endl;
    }

    return 0;
}