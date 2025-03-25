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

    for (int i = 0; i < numPages; i++) {
        for (int j = 0; j < TOTAL_FRAMES; j++) {
            if (!frames[j]) { // If frame is free
                frames[j] = true;
                pt.pages[i] = i;  // Page number
                pt.frame[i] = j;  // Assigned frame
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

// Segmentation Structure
struct SegmentTable {
    int segmentID[10];
    int base[10];
    int limit[10];
    int segmentCount;
    bool allocated;
};

// Function to allocate segments
void allocateSegments(SegmentTable &st, int numSegments) {
    st.segmentCount = numSegments;
    st.allocated = true;
    int baseAddress = 1000; // Arbitrary base address start

    for (int i = 0; i < numSegments; i++) {
        st.segmentID[i] = i;
        st.base[i] = baseAddress;
        st.limit[i] = (i + 1) * 100;
        baseAddress += st.limit[i];
    }
    cout << "Segments allocated successfully.\n";
}

// Function to deallocate segments
void deallocateSegments(SegmentTable &st) {
    if (!st.allocated) {
        cout << "Error: No segments allocated to free!\n";
        return;
    }

    st.allocated = false;
    cout << "Segments freed successfully!\n";
}

// Function to display segment table
void displaySegmentTable(SegmentTable &st) {
    if (!st.allocated) {
        cout << "No segments allocated yet!\n";
        return;
    }

    cout << "Segment Table:\n";
    cout << "Segment ID -> Base Address -> Limit\n";
    for (int i = 0; i < st.segmentCount; i++) {
        cout << "   " << st.segmentID[i] << " -> " << st.base[i] << " -> " << st.limit[i] << "\n";
    }
}

int main() {
    PageTable process1;
    SegmentTable process2;

    cout << "\n=== Paging Example ===\n";
    allocatePages(process1, 4);
    displayPageTable(process1);
    deallocatePages(process1);

    cout << "\n=== Segmentation Example ===\n";
    allocateSegments(process2, 3);
    displaySegmentTable(process2);
    deallocateSegments(process2);

    return 0;
}
