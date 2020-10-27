/*
 * Programming Assignment 3 - CS 433
 * Description: Scheduling Algorithms
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 11/04/2020
 * File: PCB.cpp
 */
using namespace std;

#include "PCB.h"

// TODO: Add your implementation here
PCB::PCB(unsigned int id, unsigned int priority, ProcState state)
  : id(id), priority(priority), state(state)
{

}

void PCBTable::pushToTable(PCB node)
{
  vectorOfPCB.push_back(node);
}

void PCBTable::removeFromTable(int priority)
{
  //PCB node;
  //vectorOfPCB.erase(node);
}
