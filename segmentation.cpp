#include <iostream>
using namespace std;

#define TOTAL_MEMORY 32  // Total available memory (example size)

// Segment Table Structure
struct SegmentTable {
    int segment[10];  // Segment IDs
    int base[10];     // Base address of each segment
    int limit[10];    // Size of each segment
    int segmentCount;
    bool allocated;
};

// Memory Array (Simulating RAM)
bool memory[TOTAL_MEMORY] = {false}; // False means free

// Function to check available memory
int availableMemory() {
    int count = 0;
    for (int i = 0; i < TOTAL_MEMORY; i++) {
        if (!memory[i]) count++;
    }
    return count;
}

// Function to allocate segments
void allocateSegments(SegmentTable &st, int numSegments, int segmentSizes[]) {
    if (numSegments > 10) {
        cout << "Error: Too many segments!\n";
        return;
    }

    int totalRequired = 0;
    for (int i = 0; i < numSegments; i++) {
        totalRequired += segmentSizes[i];
    }

    if (totalRequired > availableMemory()) {
        cout << "Error: Not enough memory available!\n";
        return;
    }

    st.segmentCount = numSegments;
    st.allocated = true;

    int currentBase = 0;
    for (int i = 0; i < numSegments; i++) {
        // Find free space
        while (currentBase < TOTAL_MEMORY && memory[currentBase]) {
            currentBase++;
        }

        // Allocate segment
        st.segment[i] = i; 
        st.base[i] = currentBase;
        st.limit[i] = segmentSizes[i];

        for (int j = 0; j < segmentSizes[i]; j++) {
            memory[currentBase + j] = true;
        }
        currentBase += segmentSizes[i];
    }
    cout << "Segments allocated successfully.\n";
}

// Function to deallocate segments
void deallocateSegments(SegmentTable &st) {
    if (!st.allocated) {
        cout << "Error: No memory allocated to free!\n";
        return;
    }

    for (int i = 0; i < st.segmentCount; i++) {
        for (int j = 0; j < st.limit[i]; j++) {
            memory[st.base[i] + j] = false; // Free memory
        }
    }
    st.allocated = false;
    st.segmentCount = 0; // Reset segment count
    cout << "Memory freed successfully!\n";
}

// Function to display segment table
void displaySegmentTable(SegmentTable &st) {
    if (!st.allocated) {
        cout << "No memory allocated yet!\n";
        return;
    }

    cout << "Segment Table:\n";
    cout << "Segment ID -> Base Address | Limit\n";
    for (int i = 0; i < st.segmentCount; i++) {
        cout << "   " << st.segment[i] << " -> " << st.base[i] << " | " << st.limit[i] << "\n";
    }
}

int main() {
    SegmentTable process1;
    int segmentSizes[] = {5, 8, 6}; // Example segment sizes

    // Allocate memory for segments
    allocateSegments(process1, 3, segmentSizes);
    displaySegmentTable(process1);

    // Deallocate memory
    deallocateSegments(process1);

    // Try deallocating again (should show error)
    deallocateSegments(process1);

    return 0;
}
