#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

const int MEMORY_SIZE = 50;
vector<bool> memory(MEMORY_SIZE, false); // false = free, true = allocated

void displayMemory() {
    system("cls"); // Clear screen for Windows

    cout << "Real-Time Memory Visualization\n\n";
    cout << "Legend: # Allocated, . Free\n\n";

    for (int i = 0; i < MEMORY_SIZE; i++) {
        cout << (memory[i] ? '#' : '.') << " ";
        if ((i + 1) % 10 == 0) cout << endl; // New line every 10 blocks
    }
    cout << endl;
}

int main() {
    while (true) {
        displayMemory();
        this_thread::sleep_for(chrono::seconds(2)); // Refresh every 2 seconds
    }
    return 0;
}
