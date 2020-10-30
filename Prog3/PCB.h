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

/*
 * Enumerator class of process' state
 */
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
        int priority; 	// Values between 1-50. Larger number represents higher priority
        int cpuBurst; 	// CPU burst = how much time the process needs to complete
        int runtime;    // Compute run time 
        int turnaround; // Compute how long it took to finish this process
        int wait;       // Compute how long it wait to run
        ProcState state; 	// The current state of the process.

    public:
	// Constructors and destructor
        PCB();
        PCB(string id, int priority, int cpuBurst);
        PCB(string id, int priority, int cpuBurst, int runtime, int turnaround, int wait, ProcState state);
        ~PCB();

        // Useful methods - getters, setters, and update values

        // set PCB ID/name
        void setID(string id);

        // get PCB id/name
        string getID();

        // Set PCB priority
        void setPriority(int priority);
 
	// Get PCB priority
        int getPriority(); 

        // set PCB cpu burst
	void setCpuBurst(int burst);

	// get PCB cpu burst
        int getCpuBurst();

        // get PCB runtime
        int getRuntime();

	// Update PCB runtime
        void updateRuntime(int timeSlice);

        // get PCB turnaround time
        int getTurnaround();

	// Update PCB turnaround time
        void updateTurnaround();

        // get PCB wait time
        int getWait();

	// Update PCB wait time
        void updateWait(int waited);

	// Get PCB state
        string getState();

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
 * General Functions
 */
namespace Functions 
{
    void show_header(string algorithm);

    //void run_task(PCB& p1, int time);
    void run_task(PCB* p1, int time);

    void calculateAverages(const vector<PCB> &table); //VECTOR

    //vector functions
    bool compareName(PCB* lhs, PCB* rhs);

    bool comparePriority(PCB* lhs, PCB* rhs);

    bool compareCpuBurst(PCB* lhs, PCB* rhs);
}

