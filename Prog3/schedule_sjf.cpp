/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: scheduling_sjf.cpp
 */


/*
 * The input file is in the format:
 * [name], [priority], [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

#include "PCB.h"

using namespace std;
/*
bool operator<(const PCB& p1, PCB& p2)
{
    // Convert to negative to reverse priority scheduling for 
    // cpu time burst
    int negativeBurstP1 = -1 * p1.getCpuBurst();
    int negativeBurstP2 = -1 * p2.getCpuBurst();

    // The smaller value would have higher priority
    return negativeBurstP1 < negativeBurstP2;
}
*/
int main(int argc, char *argv[])
{

    Functions::show_header("SJF");

    int QUANTUM = 10;
    
    // Check that input file is provided at command line
    if(argc < 2 ) {
        cerr << "Usage: " << argv[0] << " <input_file> [<time_quantum>]" << endl;
        exit(1);
    }

    // Read the time quantum if provided.
    if(argc >= 3) {
        QUANTUM = atoi(argv[2]); 
        if (QUANTUM != 0) {
            cout << "Time quantum: "<< QUANTUM << endl;
        } else {
            cout << "No time quantum.\n";
        }
    }

    // Read task name, priority and burst length from the input file 
    string name;
    int priority;
    int burst;

    // create a table object to save 10 processes
    //PCBTable myTable(10);
    int numProcesses = 10;
    PCB myTable[numProcesses];

    // open the input file
    std::ifstream infile(argv[1]);
    string line;

    while(getline(infile, line) ) {
        std::istringstream ss (line);
        // Get the task name
        getline(ss, name, ',');
        
        // Get the task priority 
        string token;
        getline(ss, token, ',');
        priority = std::stoi(token);

        // Get the task burst length 
        getline(ss, token, ',');
        burst = std::stoi(token);

	// Save pcb into table
	int i = 0;
        myTable[i].setID(name);
        myTable[i].setPriority(priority);
        myTable[i].setCpuBurst(burst);
        myTable[i].displayPCB();
        i++;
    }
    
    // ReadyQueue for SJF 
    priority_queue<PCB> sjf_queue;
   /* 
    for (int i = 0; i < numProcesses; i++) 
    {
        // insert a process in the queue
        sjf_queue.push(myTable[i]);       
    }
    
    // Test if queue is correct
    while(!sjf_queue.empty()
    {
       PCB process = sjf_queue.top();
       sjf_queue.pop();
       process.displayPCB();
  
    }

*/


    // TODO: Add your code to run the scheduler and print out statistics

    return 0;
}
