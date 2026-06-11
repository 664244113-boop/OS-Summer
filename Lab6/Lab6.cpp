#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int NUM_PHILOSOPHERS = 5;
mutex chopsticks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    for (int i = 0; i < 2; i++) {
        
        cout << "Philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::milliseconds(100));

        if (id % 2 == 0) {
            chopsticks[right].lock();
            chopsticks[left].lock();
        } else {
            chopsticks[left].lock();
            chopsticks[right].lock();
        }

        cout << "Philosopher " << id << " is eating." << endl;
        this_thread::sleep_for(chrono::milliseconds(100));

        chopsticks[left].unlock();
        chopsticks[right].unlock();
    }
}

int main() {
    thread philosophers[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i] = thread(philosopher, i);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].join();
    }

    return 0;
}
