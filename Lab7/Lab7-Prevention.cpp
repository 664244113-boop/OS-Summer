#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx1;
mutex mtx2;

void threadA() {
    mtx1.lock();
    mtx2.lock();
    
    cout << "Thread A is holding both mutexes and running.\n";
    
    mtx2.unlock();
    mtx1.unlock();
}

void threadB() {
    mtx1.lock();
    mtx2.lock();
    
    cout << "Thread B is holding both mutexes and running.\n";
    
    mtx2.unlock();
    mtx1.unlock();
}

int main() {
    cout << "=== Deadlock Prevention ===" << endl;
    
    thread t1(threadA);
    thread t2(threadB);
    
    t1.join();
    t2.join();
    
    cout << "Execution finished successfully." << endl;
    return 0;
}