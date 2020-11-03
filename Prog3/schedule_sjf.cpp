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
    }

    // Save file name from input
    string file = argv[1];

    // create a table to save processes
    vector<PCB> myTable = Functions::createTable(file);

    // Print table
    cout << "PCB Table: [name] [priority] [CPU burst]" << endl;
    for (auto p: myTable)
    {
        p.displayPCB();
        cout<<endl;
    }
    
    // ReadyQueue for SJF 
    vector<PCB*> sjf_queue;
    for (int i = 0; i < myTable.size(); i++) 
    {
        sjf_queue.push_back(&myTable[i]);
        myTable[i].setReady();
    }

    // Sort queue by burst time
    sort(sjf_queue.begin(),sjf_queue.end(), &Functions::compareCpuBurst);

    // variable to hold wait time
    int waitTime = 0;

    // Run processes in the queue
    cout << endl << "Run SJF - Short Job First:" << endl;
    while(!sjf_queue.empty())
    {
        // get next process in the queue
        PCB* process = sjf_queue.front();  // vector queue

        // compute wait time
        process->updateWait(waitTime);
        process->updateTurnaround();

        //increment wait time 
        waitTime += process->getCpuBurst();

        // run process to completion
        Functions::run_task(process, process->getCpuBurst());

        // change state to terminated
        process->setTerminated();

        // remove process from the queue
        sjf_queue.erase(sjf_queue.begin());  // vector queue
    }
 
    // Show statistics
    cout << endl << "Show statistics:" << endl;
    Functions::calculateAverages(myTable);  //VECTOR

    return 0;
}
