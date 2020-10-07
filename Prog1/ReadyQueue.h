/*
 * Programming Assignment 1 - CS 433
 * Description: ReadyQueue implementation to control processes and test performance
 * Author: Adriana Caetano
 * Date: 09/23/2020
 * File: ReadyQueue.h
 */

#ifndef READYQUEUE_H
#define REDYQUEUE_H

#include "PCB.h"

/**
 * ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue here such that the process with the highest priority
 * can be selected next.
 */

//template <class T>
struct Node {
	PCB* data; 	// pointer to PCB process
	Node* next;	// pointer to the next node in the list
	
	//Constructors
	Node (): data{nullptr}, next {nullptr}  {}
	Node(PCB* d): data{d}, next{nullptr} {}
};

//template <class T>
class ReadyQueue {
private: 	
	Node* head; // pointer to the first node in the list
	Node* tail; // pointer to one beyond the last node in the list
public:
	// Constructor
	ReadyQueue(); 
	
	// Destructor
 	virtual ~ReadyQueue();

	// Check if ReadyQueue is empty. Return true if it is, False otherwise.
	bool isEmpty();
	
	// Create a node for a process
	Node* createNode(PCB (&process) );

	// Add a PCB representing a process into the ready queue.
	void add(Node*);
	
	// Add a node to the front of the list
	void insertFront(Node*);
	
	// Given a previous node, add after that
	void insertAfter(Node* prevNode, Node* newNode);
	
	// Add a node at the end of the list
	void insertEnd(Node*);

	//Include spefic elements from PCB Table into ReadyQueue
	void include(unsigned int elements[], unsigned int elemSize, PCBTable* table);

	// Remove and return the PCB with the highest priority from the queue
	void removeHighest();

	// Returns the number of elements in the queue.
	int getSize();

	// Prints the queue contents to standard output.
	void display(); 

	// Prints the queue contents with add/remove info for each process
	void displayFull();
 
	// Create a ReadyQueue. Add specific processes, remove the highest priority processes, 
	// and display queue elements. 
	void performTest1();
	
	// Evaluate performance of the queue implementation inserting and removing processes. 
	// Measure the time to do 1,000,000 iterations and present results.
	void performTest2(); 

};

#endif

