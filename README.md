# CSOPESY_MCO1

A C-based program that shows a simulation of basic CPU scheduling algorithms which are: First-Come First Serve (FCFS), Shortest-Job First (SJF), Shortest-Remaining-Time-First (SRTF), and Round-Robin (RR).

**Input**
An input text file is accepted by the program which contains the following:
- The first line contains 3 integers separated by space, `X Y Z`.
- `X` denotes the CPU scheduling algorithm. 0 = FCFS, 1 = SJF, 2 = SRTF, and 3 = RR.
- `Y` denotes the number of processes where 3 <= `Y` <= 100.
- `Z` denotes a time slice value (applicable for RR only) where 1 <= `Z` <= 100.
- There will be `Y` lines of space-separated integers `A B C` where `A` is the process ID, `B` is the arrival time, and `C` is the burst time.

To run the program, use the command prompt or use programs like Dev-C++ or Visual Studio Code.
