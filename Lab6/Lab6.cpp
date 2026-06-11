#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

mutex chopsticks[NUM_PHILOSOPHERS]; 

mutex cout_mutex; 

void philosopher(int id) {
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    int first = (id % 2 == 0) ? right_chopstick : left_chopstick;
    int second = (id % 2 == 0) ? left_chopstick : right_chopstick;

    for (int i = 0; i < 2; ++i) { 
        
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Philosopher " << id << " is thinking..." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500)); 

        chopsticks[first].lock();
        chopsticks[second].lock();

        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Philosopher " << id << " is EATING (Round " << i + 1 << ")." << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(500)); 

        chopsticks[first].unlock();
        chopsticks[second].unlock();
        
        {
            lock_guard<mutex> lock(cout_mutex);
            cout << "Philosopher " << id << " put down chopsticks." << endl;
        }
    }
}

int main() {
    cout << "=== Lab 6: Dining Philosophers Simulation ===" << endl;
    thread philosophers[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = thread(philosopher, i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    cout << "=== All philosophers have finished dining successfully! ===" << endl;
    return 0;
}