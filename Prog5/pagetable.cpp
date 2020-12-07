/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.cpp
 */

#include <array>
#include <chrono> // timer
#include <fstream> // file
#include <iostream>
#include <string>

#include "functions.h"
#include "pagetable.h"

// TODO: Add your implementation of PageTable

// Constructors
PageTable::PageTable() {}

PageTable::PageTable(int size)
{
    this->size = size;  // max array size
    this->count = 0;    // num elements in the  array
    this->page_table = new PageEntry [this->size];
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
    this->count = 0;
    this->page_table = new PageEntry[this->size];
}

// Destructor
PageTable::~PageTable()
{
    delete [] page_table;
}

// Return the size of the page table
int PageTable::get_max_size()
{
    // max capacity
    return this->size;
}

// Return number of saved entries
int PageTable::get_count()
{
    // total number of elements in the table
    return this->count;
}

void PageTable::print()
{
    std::cout << "PageTable with " << this->count << " page entries.\n";
    for (auto it = 0; it < this->count; it++)
    {
        // print each entry
        this->page_table[it].print_entry();
        std::cout << std::endl;
    }
}

// Open file, read logical address, create a page entry, and populate the table        
void PageTable::open_file(std::string file_name, Parameters p)
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
    int references = 0;
    std::cout << "Save into table\n";

    while (fin >> input)
    {
        references++;
        refAddress = std::stoi(input);
        PageTable::save_to_table(refAddress, p);
    }

    fin.close(); // close file

    PageTable::print();
    
    std::cout << "\nTotal number of references: " << references << std::endl;
}


// Save entry into PageTable
void PageTable::save_to_table(int logical_add, Parameters p)
{
    if (this->count < this->size)
    {
        for (auto it = 0; it < this->count; it++)
        { 
            // Check if it's already in the table   
            if (this->page_table[it].logical_add == logical_add) 
            {  
                return; // address found, don't save it
            }
        }
        // Save a new PageEntry into the table
        int page_number = logical_add / p.page_size;
        this->page_table[this->count] = PageEntry(logical_add, page_number);
        this->count++; // update table count
    } 
    else 
    { 
        std::cout << "Reached max page table size\n";
        exit(0);
    }
}


// ----------------------------------------------------------------------------------------------
// Perform Test 1
void PageTable::test1(Parameters p)
{
    PageTable::open_file("small_refs.txt", p);
//    PageTable::print();
}

// ----------------------------------------------------------------------------------------------
// Perform test 2
void PageTable::test2(Parameters p)
{
    std::cout << "Start timer for Test 2\n\n";
    auto start = std::chrono::steady_clock::now();

//   PageTable::open_file("large_refs.txt", p);

    std::cout << " \n*************************   Simulate FIFO replacement   *************************\n\n";
    // TODO: Calculate number of page faults using FIFO replacement algorithm
    // TODO: Print the statistics and run-time

    std::cout << " \n************************   Simulate Random replacement   ************************\n\n";
    // TODO: Calculate number of page faults using Random replacement algorithm
    // TODO: Print the statistics and run-time

    std::cout << " \n**************************   Simulate LRU replacement   *************************\n\n";
    // TODO: Calculate number of page faults using LRU replacement algorithm
    // TODO: Print the statistics and run-time

    auto end = std::chrono::steady_clock::now(); //end time measument for test 2
    std::chrono::duration<double> elapsed_seconds = end - start;	
    std::cout << "\nTest 2 runtime = " << elapsed_seconds.count() << " seconds\n\n";
}

// ----------------------------------------------------------------------------------------------
