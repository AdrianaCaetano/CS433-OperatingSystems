/*
 * Programming Assignment 1 - CS 433
 * Description: ReadyQueue implementation to control processes and test performance
 * Author: Adriana Caetano
 * Date: 09/23/2020
 * File: PCB.h
 */

#ifndef PCB_H
#define PCB_H

// enum class of process state
// A process (PCB) in ready queue should be in READY state
enum class ProcState {
	NEW = 0, 
	READY, 
	RUNNING, 
	WAITING, 
	TERMINATED
};

/* 
 * Process control block (PCB) is a data structure representing a process in the system.
 * A process should have at least an ID and a state(i.e.NEW, READY, RUNNING, WAITING or TERMINATED).
 * It may also have other attributes, such as scheduling information (e.g. priority)
 */

struct PCB 
{	
	//initialized members
	unsigned int id = 1;			// unique process ID
	unsigned int priority = 1;		// priority value to execute the process. 
	unsigned int added = 1;			// Counter for added times to ReadyQueue
	unsigned int removed = 1;		// Counter for removed times from ReadyQueue
	ProcState state = ProcState::NEW;	// The current state of the process.

	// Useful Method
	void displayPCB() 
	{
		std::cout << "PCB ID: " << id << " - Priority: " << priority;
	}

	void displayFullPCB() {
		displayPCB();	
		std::cout << " - State: ";
		switch(state) {
			case ProcState::NEW: 
				std::cout << "NEW" ; 
				break;
			case ProcState::READY: 	
				std::cout << "READY"; 
				break;
			case ProcState::RUNNING:
				std::cout << "RUNNING";
				break;
			case ProcState::WAITING: 
				std::cout << "WAITING";
				break;
			case ProcState::TERMINATED: 
				std::cout << "TERMINATED";
		}
		std::cout << " - Added " << added << " times - Removed " << removed << " times";
	}	
};

/*
// Overload ostream to display process from pointer
std::ostream& operator<<(std::ostream& os, PCB* pcb) {
	os<< pcb->displayPCB();
	return os;
}
*/

class PCBTable 
{
	private:
		unsigned int size = 30;		//default value
		PCB* pcbTable;

	public:

	//Constructors
	PCBTable();
	PCBTable(unsigned int size);

	//Destructor
	~PCBTable();
 	
	// Randomize priority of processes on the table
	void randomize(bool randomize);

	// Return a pointer to an element of the table
	PCB* getProcess(unsigned int processID);

	// Check process state
	bool checkState(unsigned int processID, ProcState state);

	//Print the whole table
	void displayPCBTable();
	
	//Print the whole table with summary of added/removed for each process
	void displayFullTable();
};

# endif
