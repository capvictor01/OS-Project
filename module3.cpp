#include <iostream>
#include <fstream>
using namespace std;

#define TOTAL_FRAMES 8
#define PAGE_SIZE 4

// ===============================
// Project: Real-Time Memory Allocation Tracker
// Modules: Paging, Segmentation, First Fit Allocation
// ===============================

// Segment Structure
struct Segment {
    int base;
    int limit;
};

// Page Table Structure
struct PageTable {
    int pages[10];
    int frame[10];
    int pageCount;
    bool allocated;
};

// Global Memory Arrays
bool frames[TOTAL_FRAMES] = {false};
Segment segments[5];
PageTable process;

// ================= PAGING =================
int availableFrames() {
    int count = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (!frames[i]) count++;
    }
    return count;
}

void saveFramesToFile() {
    ofstream file("memory_status.txt");
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        file << frames[i] << " ";
    }
    file.close();
}

void allocatePages(PageTable &pt, int numPages) {
    if (numPages > availableFrames()) {
        cout << "Error: Not enough memory! Allocation failed.\n";
        return;
    }
    pt.pageCount = numPages;
    pt.allocated = true;

    for (int i = 0; i < numPages; i++) {
        for (int j = 0; j < TOTAL_FRAMES; j++) {
            if (!frames[j]) {
                frames[j] = true;
                pt.pages[i] = i;
                pt.frame[i] = j;
                break;
            }
        }
    }
    cout << "Pages allocated successfully.\n";
    saveFramesToFile();
}

void deallocatePages(PageTable &pt) {
    if (!pt.allocated) {
        cout << "Error: No memory allocated!\n";
        return;
    }
    for (int i = 0; i < pt.pageCount; i++) {
        frames[pt.frame[i]] = false;
    }
    pt.allocated = false;
    cout << "Memory deallocated successfully.\n";
    saveFramesToFile();
}

void displayPageTable(PageTable &pt) {
    if (!pt.allocated) {
        cout << "No memory allocated yet!\n";
        return;
    }
    cout << "\nPage Table (Paging):\n";
    cout << "Page Number -> Frame Number\n";
    for (int i = 0; i < pt.pageCount; i++) {
        cout << "   " << pt.pages[i] << " -> " << pt.frame[i] << "\n";
    }
}

// ================= SEGMENTATION =================
void allocateSegments() {
    int n;
    cout << "Enter number of segments (max 5): ";
    cin >> n;

    if (n > 5) {
        cout << "Error: Maximum 5 segments allowed!\n";
        return;
    }

    int base = 0;
    for (int i = 0; i < n; i++) {
        cout << "Enter limit (size) of segment " << i << ": ";
        cin >> segments[i].limit;
        segments[i].base = base;
        base += segments[i].limit;
    }
    cout << "Segments allocated successfully.\n";
}

void displaySegments(int n) {
    cout << "\nSegment Table (Segmentation):\n";
    cout << "Segment No -> Base -> Limit\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << i << " -> " << segments[i].base << " -> " << segments[i].limit << "\n";
    }
}

// ================= MEMORY STATUS =================
void displayFrames() {
    cout << "\nMemory Frames Status:\n";
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        cout << "Frame " << i << ": " << (frames[i] ? "Allocated" : "Free") << "\n";
    }
}

// ================= MAIN MENU =================
int main() {
    int choice, numPages, numSegments = 0;

    while (true) {
        cout << "\n===== Real-Time Memory Allocation Tracker =====\n";
        cout << "1. Allocate Pages (Paging)\n";
        cout << "2. Deallocate Pages\n";
        cout << "3. Display Page Table\n";
        cout << "4. Allocate Segments (Segmentation)\n";
        cout << "5. Display Segment Table\n";
        cout << "6. Display Memory Frames\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (process.allocated) {
                    cout << "Error: Memory already allocated! Deallocate first.\n";
                } else {
                    cout << "Enter number of pages to allocate: ";
                    cin >> numPages;
                    allocatePages(process, numPages);
                }
                break;

            case 2:
                deallocatePages(process);
                break;

            case 3:
                displayPageTable(process);
                break;

            case 4:
                allocateSegments();
                numSegments = 5; // Since we allow up to 5 segments
                break;

            case 5:
                displaySegments(numSegments);
                break;

            case 6:
                displayFrames();
                break;

            case 7:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
