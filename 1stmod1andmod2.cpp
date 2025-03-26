#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace std;

#define TOTAL_FRAMES 8   
#define PAGE_SIZE 4      

vector<bool> memory(TOTAL_FRAMES, false);

struct PageTable {
    int pages[10];  
    int frame[10];  
    int pageCount;
    bool allocated;
};

int availableFrames() {
    int count = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (!memory[i]) count++;
    }
    return count;
}

void allocatePages(PageTable &pt, int numPages) {
    if (numPages > availableFrames()) {
        cout << "Error: Not enough memory available!\n";
        return;
    }

    pt.pageCount = numPages;
    pt.allocated = true;

    for (int i = 0; i < numPages; i++) {
        for (int j = 0; j < TOTAL_FRAMES; j++) {
            if (!memory[j]) {
                memory[j] = true;
                pt.pages[i] = i;
                pt.frame[i] = j;
                break;
            }
        }
    }
    cout << "Pages allocated successfully.\n";
}

void deallocatePages(PageTable &pt) {
    if (!pt.allocated) {
        cout << "Error: No memory allocated to free!\n";
        return;
    }

    for (int i = 0; i < pt.pageCount; i++) {
        memory[pt.frame[i]] = false;
    }
    pt.allocated = false;
    cout << "Memory freed successfully!\n";
}

void displayMemory() {
    system("cls");

    cout << "Real-Time Memory Visualization\n\n";
    cout << "Legend: # Allocated, . Free\n\n";

    for (int i = 0; i < TOTAL_FRAMES; i++) {
        cout << (memory[i] ? '#' : '.') << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;
}

int main() {
    PageTable process1;

    cout << "\n=== Allocating Pages ===\n";
    allocatePages(process1, 4);
    displayMemory();
    this_thread::sleep_for(chrono::seconds(2));

    cout << "\n=== Deallocating Pages ===\n";
    deallocatePages(process1);
    displayMemory();
    this_thread::sleep_for(chrono::seconds(2));

    return 0;
}
