/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.cpp
 */

#include <array>
#include <fstream> // file
#include <iostream>
#include <stack>
#include <string>

#include "functions.h"
#include "pagetable.h"

// TODO: Add your implementation of PageTable

// Constructors
PageTable::PageTable() {}

PageTable::PageTable(int size)
{
    this->size = size;
    this->page_table = new PageEntry* [this->size];
}

PageTable::PageTable(int page_size, int num_pages)
{
    // max size of virtual memory is 128MB
    //convert virtual memory size from MB to bytes (= 2^20)
    int max_virtual = 128 << 20;

    // max page table size
    int max_table_sz = max_virtual / page_size;

    if (num_pages < max_table_sz) 
    { 
        this->size = num_pages;
    } 
    else 
    { 
        this->size = max_table_sz;
    }
//    std::cout << "Page Table size = " << this->size << std::endl;
    this->page_table = new PageEntry*[this->size];
}


// Destructor
PageTable::~PageTable()
{
    delete [] page_table;
}

// Return the size of the page table
int PageTable::get_size()
{
    return this->size;
}

// Open file, read logical address, create a page entry, and populate the table        
void PageTable::open_file(std::string file_name, int page_size)
{
    std::ifstream fin;
    fin.open(file_name, std::ifstream::in); // open file

    if ( fin.fail() )
    {
        std::cerr << "Could not open file " << file_name << std::endl;
        exit(1); // 1 indicates an error occurred
    }
    else
    {
        std::cout << "Opening file " << file_name << std::endl;
    }

    std::string input;
    int refAddress;
    int page_number;
    int references = 0;

    while (fin >> input)
    {
        refAddress = std::stoi(input);
        page_number = refAddress / page_size;
        PageEntry entry = PageEntry(refAddress,page_number);
        if ( references < PageTable::get_size() )
        {      
            this->page_table[references] = &entry;
            references++;
        } 
        else 
        { 
            std::cout << "Reached max page table size\n";
            exit(0);
        }
    }

    fin.close(); // close file

    std::cout << "Total number of references: " << references << std::endl;
}

// ----------------------------------------------------------------------------------------------
// Perform Test 1
void PageTable::test1(Parameters p)
{
   PageTable::open_file("small_refs.txt", p.page_size);
}

// ----------------------------------------------------------------------------------------------
// Perform test 2
void PageTable::test2(Parameters p)
{
   PageTable::open_file("large_refs.txt", p.page_size);

    std::cout << " \n*************************   Simulate FIFO replacement   *************************\n\n";
    // TODO: Calculate number of page faults using FIFO replacement algorithm
    // TODO: Print the statistics and run-time

    std::cout << " \n************************   Simulate Random replacement   ************************\n\n";
    // TODO: Calculate number of page faults using Random replacement algorithm
    // TODO: Print the statistics and run-time

    std::cout << " \n**************************   Simulate LRU replacement   *************************\n\n";
    // TODO: Calculate number of page faults using LRU replacement algorithm
    // TODO: Print the statistics and run-time

}

// ----------------------------------------------------------------------------------------------
