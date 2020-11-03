
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

    string file = argv[1];

    // Create a table to hold PCBs
    vector<PCB> myTable = Functions::createTable(file);

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

    // Run process in the queue for the time slice
    cout << endl << "Run RR - Round Robin with time quantum of " << QUANTUM << endl;
    
    // variable to hold time
    int time = 0;
    while (!rr_queue.empty())
    {
        // get first job in the queue to run
        PCB* job = rr_queue.front();
    
        // Increment time
        int remainder = job->getCpuBurst() - job->getRuntime();
        if (QUANTUM < remainder) 
        { 
            time += QUANTUM;
        } 
        else
        {
            time += remainder;
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

            // compute wait and turnaround time
            job->updateTurnaroundRR(time);
            job->updateWaitRR();
        } 
        else
        {
            // job needs to go back to the end of ready queue
            job->setWaiting();
            rr_queue.push_back(job);
        }
    }

    // Show statistics 
    cout << endl << "Show statistics:" << endl ;
    Functions::calculateAverages(myTable);

    return 0;
}
