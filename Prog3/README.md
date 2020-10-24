#Scheduling Algorithms (100 points)
Implement programming project “Scheduling Algorithms” at page P-31 of the textbook.


##Required Output
Your program should implement following scheduling algorithms using C/C++ on the
server:
  • First-come, first-served (FCFS), which schedules tasks in the order in which they
request the CPU.
  • Shortest-job-first (SJF), which schedules tasks in order of the length of the tasks'
next CPU burst.
  • Priority scheduling, which schedules tasks based on priority.
  • Round-robin (RR) scheduling, where each task is run for a time quantum (or for
the remainder of its CPU burst).

As described in the textbook, you may build separate executables for different
scheduling algorithms using a Makefile. Each program should be able to read a text file
of tasks, run the corresponding scheduling algorithm and print out the average
turnaround and waiting time, for example
  ./fcfs schedule.txt
The round-robin (RR) scheduling should have another command-line argument for the
time quantum, e.g.
  ./rr schedule.txt 6

It is assumed that all tasks arrive at the same time 0, and in the order according to the
list in the input text file. An example input file “schedule.txt” is provided for testing
your programs. But your program should work for any list of tasks following the same
format and will be graded using a different input file.
1. Your program should always first print your names and a short description
when it starts.
2. Your program should print out the turn-around and waiting time of each thread,
and the average turn-around time and average waiting time, for example:
T1 turn-around time = 20, waiting time = 0
T2 turn-around time = 45, waiting time = 20
T3 turn-around time = 70, waiting time = 45
T4 turn-around time = 85, waiting time = 70
T5 turn-around time = 105, waiting time = 85
T6 turn-around time = 115, waiting time = 105
T7 turn-around time = 145, waiting time = 115
T8 turn-around time = 170, waiting time = 145
Average turn-around time = 94, Average waiting time = 73


##Extra Credits
You may earn extra credits by implementing
• Priority with round-robin, which schedules tasks in order of priority and uses
round-robin scheduling for tasks with equal priority.
