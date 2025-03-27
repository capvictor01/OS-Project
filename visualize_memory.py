import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import subprocess
import os

file_path = "memory_status.txt"
exe_path = "memory_tracker.exe"  # Change name if your compiled C++ file is different

def read_memory_status():
    frames = []
    try:
        with open(file_path, 'r') as file:
            content = file.read().strip().split()
            for val in content:
                frames.append(1 if val == '1' else 0)
    except FileNotFoundError:
        frames = [0] * 8  # default empty frames
    return frames

fig, ax = plt.subplots(figsize=(8, 4))

def update(frame):
    ax.clear()
    frames = read_memory_status()

    colors = ['green' if f == 1 else 'red' for f in frames]
    labels = ['Allocated' if f == 1 else 'Free' for f in frames]

    ax.bar(range(len(frames)), [1]*len(frames), color=colors)
    ax.set_xticks(range(len(frames)))
    ax.set_xticklabels([f'Frame {i}' for i in range(len(frames))])
    ax.set_title('Memory Frame Allocation (Real-Time)')
    ax.set_xlabel('Frame Number')
    ax.set_ylabel('Status')
    ax.set_ylim(0, 1.2)

    for i, label in enumerate(labels):
        ax.text(i, 1.05, label, ha='center', fontsize=9)

def run_cpp_program():
    if not os.path.exists(exe_path):
        print(f"❗️Error: {exe_path} not found. Please compile your C++ code first.")
        return
    subprocess.Popen(exe_path)  # Runs C++ executable in background

# =========================
# 🔥 Run C++ Program First
# =========================
run_cpp_program()

# =========================
# 🎯 Start Real-Time Plot
# =========================
ani = FuncAnimation(fig, update, interval=1000)
plt.tight_layout()
plt.show()
