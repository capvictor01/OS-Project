#include <iostream>
using namespace std;

#define TOTAL_FRAMES 8  // Total available memory frames
#define PAGE_SIZE 4      // Each page is of size 4KB (example)

// Page Table Structure
struct PageTable {
    int pages[10]; // Max 10 pages
    int frame[10]; // Store which frame is assigned
    int pageCount;
    bool allocated; // To check if memory is allocated
};

// Memory Frames
bool frames[TOTAL_FRAMES] = {false}; // False means frame is free

// Function to check available frames
int availableFrames() {
    int count = 0;
    for (int i = 0; i < TOTAL_FRAMES; i++) {
        if (!frames[i]) count++;
    }
    return count;
}

// Function to allocate pages
void allocatePages(PageTable &pt, int numPages) {
    if (numPages > availableFrames()) {
        cout << "Error: Not enough memory available! Allocation failed.\n";
        return;
    }

    pt.pageCount = numPages;
    pt.allocated = true;
    int assigned = 0;

    for (int i = 0; i < numPages; i++) {
        for (int j = 0; j < TOTAL_FRAMES; j++) {
            if (!frames[j]) { // If frame is free
                frames[j] = true;
                pt.pages[i] = i;  // Page number
                pt.frame[i] = j;  // Assigned frame
                assigned++;
                break;
            }
        }
    }
    cout << "Pages allocated successfully.\n";
}

// Function to deallocate pages
void deallocatePages(PageTable &pt) {
    if (!pt.allocated) {
        cout << "Error: No memory allocated to free!\n";
        return;
    }

    for (int i = 0; i < pt.pageCount; i++) {
        frames[pt.frame[i]] = false; // Free the frame
    }
    pt.allocated = false;
    pt.pageCount = 0; // Reset page count
    cout << "Memory freed successfully!\n";
}

// Function to display page table
void displayPageTable(PageTable &pt) {
    if (!pt.allocated) {
        cout << "No memory allocated yet!\n";
        return;
    }

    cout << "Page Table:\n";
    cout << "Page Number -> Frame Number\n";
    for (int i = 0; i < pt.pageCount; i++) {
        cout << "   " << pt.pages[i] << " -> " << pt.frame[i] << "\n";
    }
}

int main() {
    PageTable process1;

    // Try allocating pages
    allocatePages(process1, 4);
    displayPageTable(process1);

    // Try deallocating memory
    deallocatePages(process1);
    
    // Try freeing memory again (should show error)
    deallocatePages(process1);

    return 0;
}
