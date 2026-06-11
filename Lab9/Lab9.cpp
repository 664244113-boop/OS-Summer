#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class FIFOPageReplacement {
private:
    int numFrames;
    vector<int> frames;
    queue<int> fifoQueue;
    int pageFaults;
    int totalReferences;
    
    bool isPageInMemory(int page) {
        return find(frames.begin(), frames.end(), page) != frames.end();
    }
    
    int findEmptyFrame() {
        for (int i = 0; i < numFrames; i++) {
            if (frames[i] == -1) {
                return i;
            }
        }
        return -1;
    }
    
public:
    FIFOPageReplacement(int frames) : numFrames(frames), pageFaults(0), totalReferences(0) {
        this->frames.resize(frames, -1);
    }
    
    void referencePage(int page) {
        totalReferences++;
        
        cout << "\nReference: " << page << " | ";
        
        if (isPageInMemory(page)) {
            cout << "HIT";
        } else {
            cout << "FAULT";
            pageFaults++;
            
            int emptyFrame = findEmptyFrame();
            
            if (emptyFrame != -1) {
                frames[emptyFrame] = page;
                fifoQueue.push(page);
            } else {
                int victimPage = fifoQueue.front();
                fifoQueue.pop();
                
                for (int i = 0; i < numFrames; i++) {
                    if (frames[i] == victimPage) {
                        frames[i] = page;
                        break;
                    }
                }
                
                fifoQueue.push(page);
                cout << " (Replaced: " << victimPage << ")";
            }
        }
        
        cout << " | Frames: [";
        for (int i = 0; i < numFrames; i++) {
            if (frames[i] == -1) {
                cout << " -";
            } else {
                cout << setw(2) << frames[i];
            }
            if (i < numFrames - 1) cout << " ";
        }
        cout << "]" << endl;
    }
    
    void processReferenceString(const vector<int>& refString) {
        cout << "\n=== Processing Reference String ===" << endl;
        cout << "Number of Frames: " << numFrames << endl;
        cout << "Reference String: ";
        for (int page : refString) {
            cout << page << " ";
        }
        cout << endl;
        cout << string(60, '-') << endl;
        
        for (int page : refString) {
            referencePage(page);
        }
    }
    
    void displayStatistics() {
        cout << "\n=== Statistics ===" << endl;
        cout << "Total References: " << totalReferences << endl;
        cout << "Page Faults: " << pageFaults << endl;
        cout << "Page Hits: " << (totalReferences - pageFaults) << endl;
        cout << "Page Fault Rate: " << fixed << setprecision(2) 
             << (pageFaults * 100.0 / totalReferences) << "%" << endl;
        cout << "Page Hit Rate: " << fixed << setprecision(2) 
             << ((totalReferences - pageFaults) * 100.0 / totalReferences) << "%" << endl;
    }
    
    void reset() {
        frames.assign(numFrames, -1);
        while (!fifoQueue.empty()) fifoQueue.pop();
        pageFaults = 0;
        totalReferences = 0;
    }
};

int main() {
    cout << "=== FIFO Page Replacement Algorithm ===" << endl;
    
    vector<int> refString1 = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    FIFOPageReplacement fifo1(3);
    fifo1.processReferenceString(refString1);
    fifo1.displayStatistics();
    
    cout << "\n\n=== Demonstrating Belady's Anomaly ===" << endl;
    vector<int> refString2 = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    
    cout << "\n--- With 3 Frames ---" << endl;
    FIFOPageReplacement fifo2(3);
    fifo2.processReferenceString(refString2);
    fifo2.displayStatistics();
    
    cout << "\n--- With 4 Frames ---" << endl;
    FIFOPageReplacement fifo3(4);
    fifo3.processReferenceString(refString2);
    fifo3.displayStatistics();
    
    cout << "\n\n=== Another Test Case ===" << endl;
    vector<int> refString3 = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4};
    FIFOPageReplacement fifo4(4);
    fifo4.processReferenceString(refString3);
    fifo4.displayStatistics();
    
    return 0;
}