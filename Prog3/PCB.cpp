/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: PCB.cpp
 */

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
    this->state = ProcState::NEW;
}

PCB::PCB(string id, unsigned int priority, unsigned int cpuBurst) 
{
    this->id = id;
    this->priority = priority;
    this->cpuBurst = cpuBurst;
    this->state = ProcState::NEW;
}

PCB::PCB(string id, unsigned int priority, unsigned int cpuBurst, ProcState state)
  : id(id), priority(priority), cpuBurst(cpuBurst), state(state) {}

// Destructor
PCB::~PCB() {}

// Useful methods

void PCB::setID(string id) 
{
    this->id = id;
}

string PCB::getID()
{
    return this->id;
}

void PCB::setPriority(unsigned int priority) 
{
    this->priority = priority;
}

unsigned int PCB::getPriority()    
{
    return this->priority;
}

void PCB::setCpuBurst(unsigned int burst)
{
    this->cpuBurst = burst;
}

unsigned int PCB::getCpuBurst() 
{ 
    return this->cpuBurst;
}

void PCB::updateCpuBurst(unsigned int usedTime)
{ 
    if (cpuBurst > usedTime) {    
        this->cpuBurst -= usedTime;
    }
    else if (cpuBurst < usedTime) {
        this->cpuBurst = 0;
    }
}        

ProcState PCB::getState() 
{ 
    return this->state;
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
    cout << "[" <<  id << "] [" <<  priority << "] [" << cpuBurst << "]\n";
}

void PCB::displayCompletePCB() 
{
    cout << "ID: " << id << " - Priority: " << priority << " - CPU Burst: " << cpuBurst << " - State: ";
    switch(state) 
    {
        case ProcState::NEW:
            printf("NEW\n");
            break;
        case ProcState::READY: 
            printf("READY\n");
            break;
        case ProcState::WAITING:
            printf("WAITING\n");
            break;
        case ProcState::RUNNING:
            printf("RUNNING\n");
            break;
        case ProcState::TERMINATED:
            printf("TERMINATED\n");
            break;
    }
} 


//***** PCB Table *****
PCBTable::PCBTable() {}

PCBTable::PCBTable(unsigned int size) 
{
    PCB tablePCB [size];	// array of PCBs
}

PCBTable::~PCBTable() 
{ 
    delete [] tablePCB; 	        // delete array
/*
    for (auto &pcb : pcbTable) {	// delete vector
        delete pcb;
    }
*/
}

// array table functions ***********
// show all processes in the table
void PCBTable::showTable()
{
    for (auto i=0; i < size; i++)
    {
        tablePCB[i].PCB::displayPCB();
    }
}

PCB* PCBTable::getProcess(unsigned int priority)
{
    //find process position
    unsigned int i;
    for (i = 0; i < size; i++) {
        if (tablePCB[i].getPriority() == priority) { return &tablePCB[i]; }

        printf("priority not found\n");
        return NULL;
    }       
}


// vector table functions **********

/*
//vector table - add pcb
void PCBTable::pushToTable(PCB* pcb)
{
    pcbTable.push_back(pcb);
}

// vector table - remove pcb
void PCBTable::removeFromTable(PCB* pcb)
{
    //find pcb position
    int it;
    for (it = pcbTable.begin(); it != pcbTable.end(); it++) {
       if (it*.getID() == pcb.getID()) { break; } 
    }
    pcbTable.erase(it);
}
*/
/*
// vector table - return a process given its priority
PCB* PCBTable::getProcess(unsigned int pcbPriority)
{ 
    //find pcb 
    auto it;
    for (it = pcbTable.begin(); it != pcbTable.end(); it++) {
        if (it*->priority == pcb->priority) 
        { 
            return &pcbTable[it];
        }
        else {
            printf("Priority not found");
        } 
    }
}
*/
