#include <windows.h>
#include <iostream>

using namespace std;

DWORD Sum;

DWORD WINAPI Summation(LPVOID Param) {
    DWORD Upper = *(DWORD*)Param;
    Sum = 0;
    
    for (DWORD i = 1; i <= Upper; i++) {
        Sum += i;
        cout << "Child Thread: Calculating... current sum is " << Sum << endl;
        Sleep(50);  
    }
    return 0;
}

int main() {
    DWORD dwThreadId;
    HANDLE hThread;
    DWORD Param;

    cout << "=== Lab 4: Windows Thread API ===" << endl;
    cout << "Enter a number to calculate sum: ";
    cin >> Param;

    hThread = CreateThread(
        NULL,          
        0,              
        Summation,      
        &Param,            
        0,              
        &dwThreadId         
    );

    if (hThread == NULL) {
        cerr << "Error: Unable to create thread." << endl;
        return 1;
    }

    cout << "Main Thread: Child created with ID " << dwThreadId << endl;
    cout << "Main Thread: Waiting for child to finish..." << endl;

    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);

    cout << "Main Thread: Child finished execution." << endl;
    cout << "Final Result: " << Sum << endl;

    return 0;
}