/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: PCB.h
 */

#pragma once

#include <string>
#include <vector>

using namespace std;

// enum class of process state
enum class ProcState {NEW, READY, RUNNING, WAITING, TERMINATED};

/* 
 * Process control block(PCB) is a data structure representing a process in the system.
 * A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
 * A process in the ReadyQueue should be in READY state
 * It may also have other attributes, such as scheduling information (e.g. priority)
 */
class PCB 
{
    private:
        string id;  	// The unique process name/ID
        unsigned int priority; 	// Values between 1-50. Larger number represents higher priority
        unsigned int cpuBurst; 	// CPU burst = how much time the process needs to complete
        ProcState state; 	// The current state of the process.

    public:
	// Constructors and destructor
        PCB();
        PCB(string id, unsigned int priority, unsigned int cpuBurst);
        PCB(string id, unsigned int priority, unsigned int cpuBurst, ProcState state);
        ~PCB();

        // Useful methods

        // set PCB ID/name
        void setID(string id);

        // get PCB id/name
        string getID();

        // Set PCB priority
        void setPriority(unsigned int priority);
 
	// Get PCB priority
        unsigned int getPriority(); 

        // set PCB cpu burst
	void setCpuBurst(unsigned int burst);

	// get PCB cpu burst
        unsigned int getCpuBurst();

	// Update PCB cpu burst
        void updateCpuBurst(unsigned int usedTime);

	// Get PCB state
        ProcState getState();

	// Update PCB state passing a new state as a paramenter
        void updateState(ProcState state);

	// Set PCB state to READY
        void setReady();

	// Set PCB state to RUNNING
        void setRunning();

	// Set PCB state to WAITING
        void setWaiting();

	// Set PCB state to TERMINATED
        void setTerminated();

	// Display summarized PCB information
        void displayPCB();

	// Display complete PCB information
	void displayCompletePCB();
};

/*
 * A container of all PCB elements in the system.
 */
class PCBTable 
{
    private:
        vector<PCB*> pcbTable;
        unsigned int size = 10; 	// default value
        PCB* tablePCB;			// PCB array

    public:
	// Constructor and Destructor
	PCBTable();
        PCBTable(unsigned int size);
        ~PCBTable();

        // Print all table's elements
        void showTable();
/*
	// Include a PCB into the table
        void pushToTable(PCB* pcb);

	// Remove a PCB from the table
        void removeFromTable(PCB* pcb);
*/
	// Get a PCB from the table
        PCB* getProcess(unsigned int pcbPriority);
};
