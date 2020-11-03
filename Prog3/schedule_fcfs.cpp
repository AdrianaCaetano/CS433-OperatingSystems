/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: schedule_fcfs.cpp
 */

/**
 * The input file is in the format:
 *  [name], [priority], [CPU burst]
 */

#include <algorithm>   //sort function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "PCB.h"
//#include "schedule_fcfs.h"

using namespace std;

int main(int argc, char *argv[])
{
    Functions::show_header("FCFS");

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

    // Save file name from input command
    string file = argv[1];

    // Container to hold PCBs
    vector<PCB> myTable = Functions::createTable(file);
 
    // Print table
    cout << "PCB Table: [name] [priority] [CPU burst]" << endl;
    for (auto p: myTable)
    {
        p.displayPCB();
        cout<<endl;
    } 

 //   FCFS::run(&myTable);
  
    // Ready Queue FCFS
    vector<PCB*> fcfs_queue;
    for (int i = 0; i < myTable.size(); i++)
    {
        fcfs_queue.push_back(&myTable[i]);
        myTable[i].setReady();
    }

    // Sort queue by name/order arrival
    sort(fcfs_queue.begin(), fcfs_queue.end(), &Functions::compareName);

    // variable to hold wait time
    int waitTime = 0;

    cout << endl << "Run FCFS - First Come First Serve:" << endl;
    while (!fcfs_queue.empty())
    {
        // get next process in the queue
        PCB* job = fcfs_queue.front();

        // compute wait time
        job->updateWait(waitTime);
        job->updateTurnaround();

        // increment wait time
        waitTime += job->getCpuBurst();

        // run process to completion
        Functions::run_task(job, job->getCpuBurst());

        // change state to terminated
        job->setTerminated();

        // remove process from the queue
        fcfs_queue.erase(fcfs_queue.begin());
    }

    cout << endl << "Show statistics:" << endl;
    Functions::calculateAverages(myTable);

    return 0;
}
