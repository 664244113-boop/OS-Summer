#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int shared_counter = 0;

mutex mtx; 

void increaseCounter(int thread_id) {
    for (int i = 0; i < 100000; ++i) {
        
        mtx.lock();   
        
        shared_counter++; 
        
        mtx.unlock(); 
        
    }
    cout << "Thread " << thread_id << " finished counting." << endl;
}

int main() {
    cout << "=== Lab 5: Process Synchronization (Mutex) ===" << endl;
    cout << "Expected Counter Value: 200000" << endl;
    cout << "Processing..." << endl;

    thread t1(increaseCounter, 1);
    thread t2(increaseCounter, 2);

    t1.join();
    t2.join();

    cout << "---------------------------------" << endl;
    cout << "Actual Final Counter Value: " << shared_counter << endl;
    
    if(shared_counter == 200000) {
        cout << "Status: SUCCESS (No data lost!)" << endl;
    } else {
        cout << "Status: FAILED (Race Condition occurred)" << endl;
    }

    return 0;
}