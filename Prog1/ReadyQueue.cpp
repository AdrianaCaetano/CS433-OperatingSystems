/*
 * Programming Assignment 1 - CS 433
 * Description: ReadyQueue implementation to control processes and test performance
 * Author: Adriana Caetano
 * Date: 09/23/2020
 * File: ReadyQueue.cpp
 */

#include <chrono>
#include <iostream>

#include "PCB.h"
#include "ReadyQueue.h"

// Default Constructor: create empty list
ReadyQueue::ReadyQueue() {
	head = nullptr;
	tail = nullptr;
} 
	
// Destructor
ReadyQueue::~ReadyQueue() {
	while (head) {
		Node* next = head->next;
		delete head;
		head = next;
	}
}	

// Check if ReadyQueue is empty. Return true if it is, False otherwise.
bool ReadyQueue::isEmpty() {
	if (head == nullptr) { return true; }
	return false;
} 

//  ORIGINAL
// Create a node for a process
Node* ReadyQueue::createNode(PCB (&process)) {
	Node* newNode = new Node;
	newNode->data = &process;
	
	return newNode;
} 

// Add a PCB representing a process into the ready queue.
void ReadyQueue::add(Node* node) { 
	// Check process state
	if (node->data->state == ProcState::READY) {
		//This process is already on the list 
		return;
	}
	//Change process state to READY and increment added counter
	node->data->state = ProcState::READY;
	node->data->added++ ;

	if (isEmpty()) {
		// Insert first node
		head = node;
		tail = node;
	} 
	// Insert node accordingly to priority value
	else if (head->data->priority < node->data->priority) {
		insertFront(node);
	}
	else if (tail->data->priority > node->data->priority) {
		insertEnd(node);
	} 
	else if (true){ 
		// Iterate through the list to choose insertion point	
		Node* search = head;
		while( search->data->priority >  node->data->priority ) {   // TODO FIX HERE!
			search = search->next;
		}
		insertAfter(search, node);
	} else {
		std::cout << "Error adding process " ;
		node->data->displayPCB();
		std::cout << std::endl;
		node->data->added--; //return to original value
	}
}

// Add a node to the front of the list
void ReadyQueue::insertFront(Node* newNode) {
	if (head != nullptr) {
		newNode->next = head;
		head = newNode;
		return;
	} 
	std::cout << "Error inserting node in the front of the list." << std::endl;
}
	
// Given a previous node, add after that
void ReadyQueue::insertAfter(Node* prevNode, Node* newNode) {
	if (prevNode != nullptr) {
		newNode->next = prevNode->next;
		prevNode->next = newNode;
		return;
	}
	std::cout << "Previous node is NULL, error inserting node after." << std::endl; 
}

// Add a node at the end of the list
void ReadyQueue::insertEnd(Node* newNode) {
	if (tail != nullptr) {
		tail->next = newNode;
		tail = newNode;
		return;
	}
	std::cout << "Error inserting node at the end of the list."<<  std::endl;
}


//Include spefic elements from PCB Table into ReadyQueue
void ReadyQueue::include(unsigned int elements[], unsigned int elemSize, PCBTable* table) {
	// Get these "elements[]" from pcbTable "and add to the queue
	for (unsigned int i = 0; i < elemSize ; i++ ) {
		PCB* temp = table->getProcess(elements[i]) ;
		Node* node = createNode( *temp );
		add(node);
	}	
}

	
// Remove the PCB with the highest priority from the queue
void ReadyQueue::removeHighest() {
	if (isEmpty()) { return; }

	//Change state to RUNNING and increment removed counter
	head->data->state = ProcState::RUNNING;
	head->data->removed++ ;
	
	// Delete first node of the list 
	if (head != tail) {
		Node* next = head->next;
		delete head;
		head = next;
	} else { 
		// Delete last node on the list
		delete head;
		head = nullptr;
		tail = nullptr;
	}
}

// Return the number of elements in the queue.
int ReadyQueue::getSize() {
	unsigned int count = 0;
	Node* node = head;
	while (node != nullptr) {	
		count++;
		node = node->next;
	}
	return count;
}

// Prints the queue contents to standard output.
void ReadyQueue::display() {
	std::cout << "\nCurrent Processes in ReadyQueue:" << std::endl;
	
	if (isEmpty()) {
		std::cout << "List is empty." << std::endl;
		return;
	} 

	Node* node = head;
	while (node != nullptr) { 
		if (node != nullptr) { 
			node->data->displayPCB(); 
			node = node->next;
			std::cout << std::endl; 
		}
	}
	std::cout << std::endl;
} 

// Prints the queue contents with add/remove info for each process
void ReadyQueue::displayFull() {
	std::cout << "ReadyQueue Summary:" << std::endl;
	
	if (isEmpty()) {
		std::cout << "List is empty." << std::endl;
		return;
	} 
	Node* node = head;
	while (node != nullptr) { 
		node->data->displayFullPCB();
		node = node->next;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
 

// *************** TEST 1 **************

// Create a ReadyQueue. Add specific processes, remove the highest priority process, 
// and display queue elements. 
void ReadyQueue::performTest1() {
	//Create a PCB Table of size 30 and consecutive priority values
	unsigned int size = 30;
	bool randomize = false; 

	PCBTable  myTable(size) ;
	myTable.randomize(randomize);

	myTable.displayPCBTable();
	std::cout << std::endl;

	// 1. Add processes 15, 6, 23, 29, and 8 to q1. Change its state to READY in the PC table. Display q1.
	std::cout << "Adding PCB IDs = 15, 6, 23, 29, and 8 to q1" << std::endl;
	unsigned int incSize = 5;
	unsigned int toInclude [incSize] = {15, 6, 23, 29, 8};
	
	include(toInclude, incSize, &myTable); // FIX 
	display();
	
	// 2.and 3. Remove the process with the highest priority from q1. 
	// Change its state to RUNNING. Display q1.
	// Higher value priority means higher priority.
	int twice = 2;
	do {
		std::cout << "Remove the highest priority process from the ReadyQueue." << std::endl;	
		removeHighest();

		display();
		std::cout << std::endl;

		twice--;
	} while (twice != 0);

	// 4. add processes 3, 17, 22, 12, and 19 to q1. Change its state to READY. Display q1.
	std::cout << "Adding PCB IDs = 3, 17, 22, 12, znd 19 to q1" << std::endl;
	unsigned int toIncludeMore[incSize] = {3, 17, 22, 12, 19};		
	
	include(toIncludeMore, incSize, &myTable);  // FIX
	display();

	// 5. One by one, remove the processes with the highest priority from q1. 
	// Display q1 after each removal.
	while (!isEmpty()) {
		std::cout << "Remove the highest priority process from the ReadyQueue." << std::endl;	
		removeHighest();
		display();
	}	
	std::cout << std::endl;
//	myTable.displayFullTable();
}


// **************** TEST 2 ****************
	
// Evaluate performance of the ReadyQueue implementation inserting and removing processes. 
// Measure the time to do 1,000,000 iterations and present results.
void ReadyQueue::performTest2() {
	// Create a new table with 30 process with random priority values
	unsigned int size = 30;
	bool randomize = true;

	PCBTable myTable = PCBTable(size);
	myTable.randomize(randomize);

	myTable.displayPCBTable();

	std::cout << std::endl;

	// Randomly select 15 processes from table to insert in the ReadyQueue.
	unsigned int incSize = 15;
	unsigned int pick [incSize];
	unsigned int value;
	
	unsigned int count = 0;   //  process counter inside pick[]. There is one already
	bool notFound;
	while (incSize > count ) {
		notFound = true;
		
		// Check if process is already in the list
		for (unsigned int i = 0; i < incSize; i++ ) {
			value = (unsigned int) rand() % size + 1; // get a random process number
			if (value == pick[i]) { 
			// It is already in the list
				notFound = false;
			}	 
			if (notFound) {
				pick[i] = value;
				count++;
			}
		}
			
	}
	
	std::cout << std::endl;
	
	// Include processes in the ReadyQueue
	include(pick, incSize,& myTable);  
	std::cout << std::endl;

	// Repeat next steps 1,000,000 times and measure the time of running the loop
	// 1. With equal probability (50%), ramdomly decide to add or remove a process to/from the ReadyQueue
	// 1a. Removing a process. Check if empty, choose highest priority to remove.Change state to RUNNING.
	// 1b. Insert a process. Choose a process that is NOT currently in the ReadyQueue. 
	// If all processes are already in the ReadyQueue, there is no process to add. 
	
	std::cout << std::endl << "Start timer for Test 2" << std::endl << std::endl;
	auto start = std::chrono::steady_clock::now();	

	int insert = rand() % 2;   // True(1) add a process, False(0) removes a process  
	unsigned int processID;

	std::cout << "Start a million loops. " << std::endl ;

	unsigned int million = 1000000;
	for ( unsigned int i = 0 ; i < million; i++ ) {
		insert = rand() % 2;   // True(1) add a process, False(0) removes a process  
		processID = (unsigned int)rand() % size + 1; // Choose process to include	

		if (insert) {
			// Check process state
			//Only add a node if it is not yet on the list
			if ( !myTable.checkState(processID, ProcState::READY) ) {
				// Process State is not READY. Create a node 
				PCB* temp = myTable.getProcess( processID );
				Node* node = createNode( *temp );

				// add to the ReadyQueue
				add(node);
			}
		} else { 
			removeHighest();		
		}
	}
	
	auto end = std::chrono::steady_clock::now(); //end time measument for test 2
	std::chrono::duration<double> elapsed_seconds = end - start;
	
	std::cout << std::endl;
	std::cout << " Test 2 runtime = " << elapsed_seconds.count() << " seconds" << std::endl; 
	std::cout << std::endl;

	myTable.displayFullTable();
	displayFull(); // show processes currently in the ReadyQueue

} 
	

