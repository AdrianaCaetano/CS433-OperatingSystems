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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "PCB.h"

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

    // Read task name, priority and burst length from the input file 
    string name;
    int priority;
    int burst;

    // Array to hold PCBs
    int numProcesses = 8;
    PCB myTable[numProcesses];

    // open the input file
    std::ifstream infile(argv[1]);
    string line;

    // iterator to populate table
    int i =0;
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
        myTable[i].setID(name);    
        myTable[i].setPriority(priority);    
        myTable[i].setCpuBurst(burst);    
        myTable[i].displayPCB();
        cout << endl;
        i++;    
    }

    for (int i = 0; i < numProcesses; i++) 
    {   
        // run task until completion
        Functions::run_task(myTable[i], myTable[i].getCpuBurst());

        // compute wait time
        int waitTime = 0;
        for (int j = 0; j < i; j++)
        { 
            waitTime += myTable[j].getCpuBurst();
        }
        
        // update wait and turnaround times
        myTable[i].updateWait(waitTime);
        myTable[i].updateTurnaround();
    }
    
    Functions::calculateAverages(myTable, numProcesses);    

    return 0;
}
