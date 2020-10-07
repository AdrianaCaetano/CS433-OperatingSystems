/*
 * Programming Assignment 1 - CS 433
 * Description: ReadyQueue implementation to control processes and test performance
 * Author: Adriana Caetano
 * Date: 09/23/2020
 * File: PCB.cpp
 */

#include <stdlib.h> // rand()
#include <time.h>
#include <iostream>

#include "PCB.h"




//Constructors
PCBTable::PCBTable() { }

PCBTable::PCBTable(unsigned int size) 
{ 
	pcbTable = new PCB [size]; 
}

// Destructor
PCBTable::~PCBTable() {
	delete [] pcbTable  ;
}


// Useful Methods:

// Randomize priority of processes on the table
void PCBTable::randomize(bool randomize) {
	for (auto i = 0; i < size; i++) {
		pcbTable[i].id = (unsigned int) i+1;	// unique id starting at one, incremented one by one
		pcbTable[i].priority = pcbTable[i].id;  // same as id
	}
	if (randomize) {
		for (auto i = 0; i < size; i++) {
		pcbTable[i].priority = (unsigned int)rand() % 50 + 1; // random priority from 1 to 50
		}
	}
}

// Return a pointer to an element of the table
PCB* PCBTable::getProcess(unsigned int processID) {
	return &pcbTable[ processID - 1];    
}

// Check process state
bool PCBTable::checkState(unsigned int processID, ProcState state) {
	if (pcbTable[processID - 1].state == state) { return true; }
	return false;
}

// Show pcbTable
void PCBTable::displayPCBTable() {
	std::cout << "PCB Table:" << std::endl;
	for (auto i = 0; i < size; i++) {
		pcbTable[i].displayPCB();
		std::cout << std::endl;
	}
}

// Prints the the table with add/remove info for each process
void PCBTable::displayFullTable() {
	std::cout << "PCB Table Summary:" << std::endl;

	for (auto i = 0; i < size; i++) { 
	pcbTable[i].displayFullPCB(); 
		std::cout << std::endl; 
	}
	std::cout << std::endl;
}








