/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: PCB.cpp
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "PCB.h"

using namespace std;

// ****** PCB *****
// Constructors
PCB::PCB() 
{
    this->id = "";
    this->priority = 0;
    this->cpuBurst = 0;
    this->runtime = 0;
    this->turnaround = 0;
    this->wait = 0;
    this->state = ProcState::NEW;
}

PCB::PCB(string id, int priority, int cpuBurst) 
{
    this->id = id;
    this->priority = priority;
    this->cpuBurst = cpuBurst;
    this->runtime = 0;
    this->turnaround = 0;
    this->wait = 0;
    this->state = ProcState::NEW;
}

PCB::PCB(string id, int priority, int cpuBurst, int runtime,  int turnaround, int wait, ProcState state)
  : id(id), priority(priority), cpuBurst(cpuBurst),runtime(runtime), turnaround(turnaround), wait(wait), state(state) {}

// Destructor
PCB::~PCB() {}

// Useful methods

void PCB::setID(string id) 
{
    this->id = id;
}

string PCB::getID()
{
    return id;
}

void PCB::setPriority(int priority) 
{
    this->priority = priority;
}

int PCB::getPriority()    
{
    return priority;
}

void PCB::setCpuBurst(int burst)
{
    this->cpuBurst = burst;
}

int PCB::getCpuBurst() 
{ 
    return cpuBurst;
}

int PCB::getRuntime() 
{
    return runtime;
}

void PCB::updateRuntime(int timeSlice)
{ 
    if (this->runtime == 0) 
    {   // first runtime
        if (this->cpuBurst > timeSlice) {    
            // run for the duration of the time slice
       	    this->runtime = timeSlice; 
        }
        else if (cpuBurst <= timeSlice) {
            // run until completion
            this->runtime = cpuBurst ;
        }
    } 
    else  
    {
        if (this->cpuBurst - this->runtime > timeSlice)
        {    // it won't finish this time
            this->runtime += timeSlice;
        } 
        else 
        {    // run the remainder of the process and terminate
             this->runtime = cpuBurst;
        }  
    }
}

int PCB::getTurnaround() 
{
    return turnaround;
}
        
void PCB::updateTurnaround()
{
    this->turnaround = this->wait + this->cpuBurst;
}

int PCB::getWait()
{
    return wait;
}

void PCB::updateWait(int waitTime)
{
    this->wait += waitTime;
} 

string PCB::getState() 
{ 
    string sState = "";
    switch(state) 
    {
        case ProcState::NEW:
            sState = "New";
            break;
        case ProcState::READY: 
            sState = "Ready";
            break;
        case ProcState::WAITING:
            sState = "Waiting";
            break;
        case ProcState::RUNNING:
            sState = "Running";
            break;
        case ProcState::TERMINATED:
            sState = "Terminated";
            break;
    }
    return sState;
}

void PCB::updateState(ProcState state)
{ 
    this->state = state;
}

void PCB::setReady() {
    this->state = ProcState::READY;
}

void PCB::setRunning() {
    this->state = ProcState::RUNNING;
}

void PCB::setWaiting() {
    this->state = ProcState::WAITING;
}

void PCB::setTerminated() {
    this->state = ProcState::TERMINATED;
}

void PCB::displayPCB() 
{
    cout << "[" <<  id << "] [" <<  priority << "] [" << cpuBurst << "]";
}

void PCB::displayCompletePCB() 
{
    cout << "ID: " << id << " - Priority: "  << priority;
    cout << " - CPU Burst: " << cpuBurst << " - State: ", PCB::getState();
} 


// ***** General Functions *****

void Functions::show_header(string algorithm) 
{
    cout << "\n======================================================================\n\n";
    cout << "CS 433 Programming assignment 3\n";
    cout << "Author: Adriana Caetano and Ryan Pisuena\n";
    cout << "Date: 11/04/2020\n";
    cout << "Course: CS433 (Operating Systems)\n";
    cout << "Description: Scheduling Algorithm - " << algorithm << "\n";
    cout << "\n======================================================================\n\n";
}

void Functions::run_task(PCB* p1, int time) 
{
    // set state to running
    p1->setRunning();
    int remainder = p1->getCpuBurst() - p1->getRuntime();

    // Print process runtime
    cout << p1->getState();
    cout << " task = ";
    p1->displayPCB();

    // update runtime
    if (remainder > time) 
    {
        // run during the whole time
        p1->updateRuntime(time);
        cout << " for " << time << " units.\n";    
    } 
    else 
    {
        // run only the remainder time
        p1->updateRuntime(remainder);
        cout << " for " << remainder << " units.\n";    
    }
}


// Function for VECTOR table
void Functions::calculateAverages(const vector<PCB> &table)
{   
    int totalTurnaround = 0;
    int totalWait=0;
    int size = table.size();
    for (auto p: table)
    {
        cout << p.getID() << " turnaround time = " << p.getTurnaround();
        cout << ", waiting time = " << p.getWait() << endl;

        totalTurnaround += p.getTurnaround();
        totalWait += p.getWait();
    }
    cout << "Average turn-around time = " << double(totalTurnaround) / size;
    cout << ", average waiting time = " << double(totalWait) / size << endl << endl;
}

//Vector functions to compare and sort vector
bool Functions::compareName(PCB* lhs, PCB* rhs)
{ 
    // first has the lower value
    return lhs->getID() < rhs->getID();
}

bool Functions::comparePriority(PCB* lhs,PCB* rhs)
{
    // first has the higher value
    return lhs->getPriority() > rhs->getPriority();
}
bool Functions::compareCpuBurst (PCB* lhs, PCB* rhs)
{ 
    // first has the lower value
    return lhs->getCpuBurst() < rhs->getCpuBurst();
}

