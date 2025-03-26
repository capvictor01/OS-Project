#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// Cross-platform clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/Mac
#endif
}

// Function to display the memory allocation as a grid (from Module 2)
void displayMemory(const vector<int>& memory, int rows, int cols) {
    clearScreen(); // Clear the screen before displaying
    cout << "Real-Time Memory Allocation Tracker\n\n";
    
    // Display page/segment info here (from Module 1)
    // Example paging table display (assuming paging is part of memory management)
    cout << "=== Paging Table ===\n";
    for (int i = 0; i < 10; ++i) {
        cout << "Page " << i << " -> Frame " << (rand() % 10) << endl;
    }

    cout << "\n=== Segmentation Table ===\n";
    for (int i = 0; i < 5; ++i) {
        cout << "Segment " << i << " -> Base Address " << (1000 + i * 100) << " -> Limit " << (50 + i * 50) << endl;
    }

    cout << "\nMemory Grid:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = i * cols + j;
            if (memory[index] == 1) {
                cout << "\033[1;32m" << "■ " << "\033[0m"; // Green for allocated
            } else {
                cout << "\033[1;31m" << "■ " << "\033[0m"; // Red for free
            }
        }
        cout << endl;
    }
    cout << "\nLegend: \033[1;32m■ Allocated\033[0m, \033[1;31m■ Free\033[0m\n";
}

// Function to simulate memory allocation and deallocation (from Module 2)
void updateMemory(vector<int>& memory) {
    int index = rand() % memory.size();

    // Toggle the block between allocated and free
    if (memory[index] == 0) {
        memory[index] = 1; // Allocate
    } else {
        memory[index] = 0; // Free
    }
}

int main() {
    const int rows = 10; // Number of rows in the grid
    const int cols = 10; // Number of columns in the grid
    vector<int> memory(rows * cols, 0); // Initialize all blocks as free (0)
    
    srand(time(0)); // Seed for random number generation

    while (true) {
        displayMemory(memory, rows, cols); // Display both memory grid and paging/segmentation info
        updateMemory(memory); // Update memory allocation status
        this_thread::sleep_for(chrono::milliseconds(500)); // Pause for 500ms
    }

    return 0;
}
