# CSOPESY_MCO1

A C-based program that shows a simulation of basic CPU scheduling algorithms which are: First-Come First Serve (FCFS), Shortest-Job First (SJF), Shortest-Remaining-Time-First (SRTF), and Round-Robin (RR).

**Input**
An input text file is accepted by the program which contains the following:
- The first line contains 3 integers separated by space, `X Y Z`.
- `X` denotes the CPU scheduling algorithm. 0 = FCFS, 1 = SJF, 2 = SRTF, and 3 = RR.
- `Y` denotes the number of processes where 3 <= `Y` <= 100.
- `Z` denotes a time slice value (applicable for RR only) where 1 <= `Z` <= 100.
- There will be `Y` lines of space-separated integers `A B C` where `A` is the process ID, `B` is the arrival time, and `C` is the burst time.

# How to Run the Program
1. Clone this repository.
2. Navigate to the cloned version of this repository.
3. Open the command prompt.
4. Type and run `gcc CSOPESY_MCO1_Code.c -o CSOPESY_MCO1_Code` in the command prompt.
5. Type and run `CSOPESY_MCO1_Code` in the command prompt or simply double-click the `CSOPESY_MCO1_Code.exe` file.
6. Wait for the program to start.
7. Input the filename of the text file which contains the input.
8. Wait until the program has finished executing.

You may also run the program using applications like Dev-C++ or Visual Studio Code.
