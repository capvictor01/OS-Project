Module 2: Real-Time Memory Management

Overview  
This module manages memory in real time using **paging and segmentation**. It assigns memory to processes, keeps track of usage, and shows updates in a simple grid.

Features  
- Paging and Segmentation:Divides memory into pages and segments for better organization.  
- Live Memory Display: Shows which memory parts are used and which are free.  
- Automatic Allocation and Freeing: Assigns memory when needed and releases it when done.  
- **Works on Different Systems:** Runs on Windows, Linux, and Mac.  

 How It Works  
1. Paging: Breaks memory into equal-sized blocks and assigns them to frames.  
2. Segmentation: Gives memory in different-sized sections based on needs.  
3. Live Display: Shows memory changes in a simple table.  
4. Tracking: Keeps updating memory allocation in real time.  

 How to Use  
1. Compile the C++ code using:  
   ```bash
   g++ memory_visualization.cpp -o memory.out
   ./memory.out
   ```  
2. Run the program to see memory being allocated and released.  
3. The memory display will update as changes happen.  

Example Output  
```plaintext
=== Paging Table ===
Page 0 -> Frame 3
Page 1 -> Frame 7
Page 2 -> Frame 5

=== Segmentation Table ===
Segment 0 -> Base Address 1000 -> Limit 150
Segment 1 -> Base Address 1150 -> Limit 200

Memory Grid:
■ ■ ■ ■ ■ ■ ■ ■ ■ ■ 
■ ■ ■ ■ ■ ■ ■ ■ ■ ■ 
■ ■ ■ ■ ■ ■ ■ ■ ■ ■ 
■ ■ ■ ■ ■ ■ ■ ■ ■ ■ 
■ ■ ■ ■ ■ ■ ■ ■ ■ ■ 

Legend: ■ Allocated, ■ Free
```

This module shows how memory is given to processes and freed when no longer needed.

