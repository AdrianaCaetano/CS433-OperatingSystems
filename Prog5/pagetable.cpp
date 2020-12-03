/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.cpp
 */


#include "pagetable.h"

// TODO: Add your implementation of PageTable

// Constructors
PageTable::PageTable() {} 

PageTable::PageTable(int size)
{
    page_table = new PageEntry [size];
}

// Destructor
PageTable::~PageTable()
{
    delete [] page_table;
}
