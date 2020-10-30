
/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: schedule_rr.cpp
 */


/**
 * The input file is in the format:
 *  [name], [priority], [CPU burst]
 */

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "PCB.h"

using namespace std;

int main(int argc, char *argv[])
{
    Functions::show_header("RR");

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

    // Create a table to hold PCBs
    vector<PCB> myTable;

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
    
        // Save PCB into table
        myTable.push_back(PCB(name, priority, burst));    
    }

    // Print table
    cout << "PCB Table: [name] [priority] [CPU burst]" << endl;
    for (auto p : myTable)
    {
        p.displayPCB();
        cout << endl;
    }

    // Ready Queue
    vector<PCB*> rr_queue;
    for (int i = 0; i < myTable.size(); i++ ) 
    {
        rr_queue.push_back(&myTable[i]);
        myTable[i].setReady();
    }
    
    // sort ready queue by name/arrival order
    sort(rr_queue.begin(), rr_queue.end(), &Functions::compareName);

    // variable to hold wait time
    int waitTime = 0;

    // Run process in the queue for the time slice
    cout << endl << "Run RR - Round Robin with time quantum of " << QUANTUM << endl;
    while (!rr_queue.empty())
    {
        // get first job in the queue to run
        PCB* job = rr_queue.front();
        
        // compute wait and turnaround time
        job->updateWait(waitTime);
        job->updateTurnaround();

        // increment wait time
        if (job->getCpuBurst() - job->getTurnaround() < QUANTUM) 
        { 
            waitTime += QUANTUM;
        } 
        else
        {
            waitTime = waitTime + (job->getCpuBurst() - job->getTurnaround());
        }
        
        // run process for the time quantum
        Functions::run_task(job, QUANTUM);

        // remove process from queue
        rr_queue.erase(rr_queue.begin()); 

       // change process state 
        if (job->getCpuBurst() == job->getRuntime())
        {
            // job is complete
            job->setTerminated();
            cout << "Task " << job->getID() << " finished." << endl;
        } 
        else
        {
            // job needs to go back to the end of ready queue
            job->setReady();
            rr_queue.push_back(job);
        }
    }

    // Show statistics 
    cout << endl << "Show statistics:" << endl ;
    Functions::calculateAverages(myTable);

    return 0;
}
