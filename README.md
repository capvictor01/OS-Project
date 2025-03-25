Module 1: Memory Management

Overview  
This module implements memory management using paging and segmentation. It is designed to efficiently allocate and track memory usage in a structured manner.  

Features  
- Paging: Divides memory into fixed-size blocks to optimize allocation.
- Segmentation: Allocates memory based on process requirements.
- Memory Tracking: Displays real-time memory usage tables.
- Memory Deallocation: Releases memory when it is no longer needed.  

How It Works  
1. Paging: Splits memory into fixed-size pages and assigns them to available frames.  
2. Segmentation: Divides memory into logical sections with specific base addresses and limits.  
3. Tracking: Displays memory allocation and deallocation tables in real-time.  

How to Use  
1. Compile the C++ code using:  
   bash
   g++ module1.cpp -o module1.out
   ./module1.out
     
2. Execute the program to observe memory allocation and tracking.  
3. The program will automatically allocate, display, and then deallocate memory.  

Example Output  
plaintext
=== Paging Example ===
Pages allocated successfully.
Page Table:
Page Number -> Frame Number
   0 -> 3
   1 -> 5
   2 -> 7
   3 -> 2
Memory freed successfully!

=== Segmentation Example ===
Segments allocated successfully.
Segment Table:
Segment ID -> Base Address -> Limit
   0 -> 1000 -> 100
   1 -> 1100 -> 200
   2 -> 1300 -> 300
Segments freed successfully!
  

This module demonstrates memory allocation and deallocation through paging and segmentation methods.
