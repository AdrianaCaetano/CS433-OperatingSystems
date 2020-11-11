/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: schedule_priority_rr.cpp
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
    Functions::show_header("Priority with RR");
    
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
  
    // sort queue by priority
    sort(priority_queue.begin(), priority_queue.end(), &Functions::comparePriority); 

    // variable to hold wait time
    int time = 0;

    // Run tasks in the queue
    cout << endl << "Run Highest Priority first. If same priority, run RR for ";
    cout << QUANTUM << " time quantum." << endl;
    while(!priority_queue.empty())
    {
        //get next job in the queue
        PCB* task = priority_queue.front();
        
        // check if next process in the queue has the same priority
        if (priority_queue.size() >= 2 && 
            priority_queue[0]->getPriority() == priority_queue[1]->getPriority()) 
        { 
            // create a new queue to run RR
            vector<PCB*> rr_queue;
            
            // populate rr queue with all process that have the same priority
            for (auto i = 0; i < priority_queue.size(); i++)
            {
                auto rr_priority = task->getPriority();
                if (rr_priority == priority_queue[i]->getPriority())
                { 
                    // save process into the new queue
                    rr_queue.push_back(priority_queue[i]);
                }
            }

            // delete same priority processes from priority queue
            for (auto i = 0; i < rr_queue.size(); i++)
            {
                priority_queue.erase(priority_queue.begin());
            }
            
            // run round robin scheduler
            cout << "Run RR for " << QUANTUM << " time quantum.\n";

            while(!rr_queue.empty())
            {
                PCB* job = rr_queue.front(); // first job in the queue
                int remainder = job->getCpuBurst() - job->getRuntime();
                if (QUANTUM < remainder)
                { 
                    time += QUANTUM;
                }
                else 
                {
                    time += remainder;
                }

                // run process for time quantum
                Functions::run_task(job, QUANTUM);
                
                // remove from the front of the queue
                rr_queue.erase(rr_queue.begin());
        
                // check if process is complete, change process state   
                if (job->getCpuBurst() == job->getRuntime())
                {
                    job->setTerminated();
                    cout << "Task " << job->getID() << " finished." << endl;

                    job->updateTurnaroundRR(time);
                    job->updateWaitRR();
                 }
                 else 
                 {
                     job->setWaiting(); // job incomplete
                     rr_queue.push_back(job); // back at the end of the queue
                 }  
            } // end of RR queue with same priority processes     
        } 
        // run hieghest priority first
        else 
        {

            // increment wait time
            time += task->getCpuBurst();

            // run job until completion
            Functions::run_task(task, task->getCpuBurst());

            // compute turnaround and wait time
            task->updateTurnaroundRR(time);
            task->updateWaitRR();

            // change state to terminated
            task->setTerminated();
            cout << "Task " << task->getID() << " finished.\n";

            // remove process from the queue
            priority_queue.erase(priority_queue.begin());
        }
    }

    // Show statistics
    cout << endl << "Show statistics:" << endl;
    Functions::calculateAverages(myTable);

    return 0;
}
