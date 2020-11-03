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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

#include "PCB.h"

using namespace std;

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
        if (Functions::check_number(argv[2])) 
        {
            QUANTUM = atoi(argv[2]);
        }
        else 
        {
            cerr << "Time quantum must be a number." << endl;
            exit(1);
        }
    }

    // save file name from input
    string file = argv[1];

    // Create a container to hold processes from file
    vector<PCB> myTable = Functions::createTable(file);

    // Print table
    cout << "PCB Table: [name] [priority] [CPU burst]" << endl;
    for (auto p: myTable)
    {
        p.displayPCB();
        cout<<endl;
    }

    // Create a priority ready queue with the processes on the table
    vector<PCB*> priority_queue;
    for (int i = 0; i < myTable.size(); i++)
    { 
        priority_queue.push_back(&myTable[i]);
        myTable[i].setReady();
    }
  
    // sort queue by priority = highest first
    sort(priority_queue.begin(), priority_queue.end(), &Functions::comparePriority);

    // variable to hold wait time
    int waitTime = 0;

    // Run tasks in the queue
    cout << endl << "Run Hieghest Priority First:" <<endl;
    while(!priority_queue.empty())
    {

        //get next job in the queue
        PCB* task = priority_queue.front();

        // compute turnaround and wait time
        task->updateWait(waitTime);
        task->updateTurnaround();

        // increment wait time
        waitTime += task->getCpuBurst();

        // run job until completion
        Functions::run_task(task, task->getCpuBurst());

        // change state to terminated
        task->setTerminated();

        // remove process from the queue
        priority_queue.erase(priority_queue.begin());
    }

    // Show statistics
    cout << endl << "Show statistics:" << endl;
    Functions::calculateAverages(myTable);

    return 0;
}
