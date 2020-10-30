
/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: schedule_priority.cpp
 */


/**
 * The input file is in the format:
 *  [name], [priority], [CPU burst]
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <string>

#include "PCB.h"

using namespace std;

// Overload operator< to order the queue using pcb priority
bool operator<(PCB& P1, PCB& P2)
{
    // higher value = higher priority
    int p1 = P1.getPriority();
    int p2 = P2.getPriority();
    return p1 < p2;
}

int main(int argc, char *argv[])
{
    Functions::show_header("Priority");
    
    int QUANTUM = 10;
    // Check that input file is provided at command line
    if(argc < 2 ) {
        cerr << "Usage: " << argv[0] << " <input_file> [<time_quantum>]" << endl;
        exit(1);
    }

    // Read the time quantum if provided.
    if(argc >= 3) {
        QUANTUM = atoi(argv[2]);
    }

    // Read task name, priority and burst length from the input file 
    string name;
    int priority;
    int burst;

    // Container to hold processes
    int numProcesses = 8;
    PCB myTable[numProcesses];

    // open the input file
    std::ifstream infile(argv[1]);
    string line;
   
    // iterator to populate container 
    int i = 0;
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
    
        // Save PCBs into table
        myTable[i].setID(name);
        myTable[i].setPriority(priority);
        myTable[i].setCpuBurst(burst);
        myTable[i].displayPCB();
        cout << endl;
        i++;
    }
    
  //  myTable.showTable();

    // Priority queue from std library
    priority_queue<PCB*> pq;
    for (int i = 0; i < numProcesses; i++)
    {
        // insert processes into queue
        pq.push(&myTable[i]);
        
        // change state to ready
        myTable[i].setReady();
    }

    // variable to hold wait time
    int waitTime = 0;       

    // run processes from priority queue
    while (!pq.empty()) 
    {
        PCB* task = pq.top();

        // compute wait time into process        
        task->updateWait(waitTime);
        task-> updateTurnaround();

        // increment wait time
        waitTime += task->getCpuBurst();
        
        // get first process and run to completion
        Functions::run_task(task, task->getCpuBurst());
        
        // change state to terminated
        task->setTerminated();

        // remove process from ready queue
        pq.pop();
    }

    // Show statistics
    Functions::calculateAverages(myTable, numProcesses);

    return 0;
}
