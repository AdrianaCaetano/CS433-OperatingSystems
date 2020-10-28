/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: PCB.cpp
 */
using namespace std;

#include <string>
#include <vector>

#include "PCB.h"

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
unsigned int PCB::getPriority()    
{
    return ->priority;
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
    this->state = ProcState::RUNNIG;
}

void PCB::setWaiting() {
    this->state = ProcState::WAITING;
}

void PCB::setTerminated() {
    this->state = ProcState::TERMINATED;
}

void PCB::displayPCB() 
{
    printf("[", id, "] [", priority, "] [", cpuBurst, "]\n");
}

void PCB::displayPCBcomplete() 
{
    printf("ID: ", id, " - Priority: ", priority, " - CPU Burst: ", cpuBurst, " - State: ")
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
PCBTable::PCBTable() 
{}

PCBTable::~PCBTable() 
{ 
    for (auto &pcb : pcbTable) {
        delete pcb;
    }
}

void PCBTable::pushToTable(PCB* pcb)
{
    pcbTable.push_back(pcb);
}

void PCBTable::removeFromTable(PCB* pcb)
{
    //find pcb position
    auto it;
    for (it = pcbTable.begin(); it != pcbTable.end(); it++) {
       if (it*->id == pcb->id) { break; } 
    }
    pcbTable.erase(it);
}

PCB* PCBTable::getProcess(unsigned int pcbPriority)
{ 
    //find pcb 
    auto it;
    for (it = pcbTable.begin(); it != pcbTable.end(); it++) {
        if (it*->priority == pcb->priority) 
        { 
            return pcbTable[it];
        }
        else {
            printf("Priority not found");
        } 
    }
}
