/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.cpp
 */

#include <algorithm>
#include <array>
#include <chrono> // timer
#include <fstream> // file
#include <iostream>
#include <list>
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

PageTable::PageTable(Parameters p)
{
    this->size = p.page_table_size;
    this->count = 0;
    
    int logical = 0;    
    int page = 0;
 
    for (int i = 0; i < this->size; i++)
    {
        // TODO Calculate parameters to create  a new page entry
        //int logical = ;    
        //int page = ; 
        PageEntry page_entry(logical, page); 

        // populate the table
        this->page_table[i] = page_entry;
    }

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

int PageTable::get_index(int log_add)
{
    for (int i = 0; i < this->count; i++)
    { 
        if (page_table[i].logical_add == log_add)
        {
            return i;
        }
    } 
    return -1;  //if it is not in the table
}

// Open file, read logical address, create a page entry, and populate the table        
void PageTable::open_file(std::string file_name, Parameters p)
{
/*    std::ifstream fin;
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
*/
}


// Save entry into PageTable
void PageTable::save_to_table(int logical_add, Parameters p)
{
/*    if (this->count < this->size)
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
*/
}

// ------------------------------- Replacement Algorithms ----------------------------------
//
// FIFO algorithm
void PageTable::fifo(int index, int &frame, int free_frames, int &page_faults, std::list<PageEntry*> &list) 
{   
    // Check if page is already loaded in memory
    if (this->page_table[index].valid == true) 
    {
       return;
    }
    // Page is not loaded yet, this is a page faults
    page_faults++;    // increment page fault

    // Check if there are free frames
    if (frame <= free_frames) 
    {
        page_table[index].frame_num = frame; 	// get a free frame and set it to page
        page_table[index].valid = true; 	// change page valid bit
        frame++;  				//increment frame count 
        list.push_back(&page_table[index]);	// insert page at the end
    }
    else
    {   
        // Choose the first page in the list to be removed
        list.front()->valid = false;   		// change page entry valid bit
        list.front()->dirty = true;     		// change page entry dirty bit
        int new_free_frame = list.front()->frame_num;  // get this page frame number
        list.pop_front(); 			// remove the first page in the list
        
        // Save new page to the back of the list
        list.push_back(&page_table[index]);		
	page_table[index].frame_num = new_free_frame; 	// set the newly freed frame to the new page
        page_table[index].valid = true; 		// change valid bit of the new page 
    } 
} 


// -------------------------------------- Test 1 --------------------------------------------
// Perform Test 1
void PageTable::test1(std::string file_name, Parameters p)
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
    int refAddress;    	// hold the logical address listed on file
    int references = 0; // hold the number of references of the file
    int index; 		// hold the index of the page for the refered address
    int frame = 0; 	// frame counter
    int page_faults = 0;// page faults counter
    std::list<PageEntry*> list_pages;	// list of loeaded pages in memory

    while (fin >> input)
    {
        references++;
        refAddress = std::stoi(input); 
        index = PageTable::get_index(refAddress);
        
        if (index >= 0)
        {
            // Load into memory using FIFO algorithm 
            PageTable::fifo(index, frame, p.num_frames, page_faults, list_pages);       
        } 
        else 
        {
            std::cout << "Page not found in the table\n";
        }
    }
    fin.close(); // close file

    PageTable::print();
    
    std::cout << "\nTotal number of references: " << references << std::endl;
}

// ---------------------------------------- Test 2 ---------------------------------------------
// Perform test 2
void PageTable::test2(std::string file_name, Parameters p)
{
    std::cout << "Start timer for Test 2\n\n";
    auto start = std::chrono::steady_clock::now();

//   PageTable::open_file("large_refs.txt", p);

    std::cout << " \n*************************   Simulate FIFO replacement   *************************\n\n";
    // Calculate number of page faults using FIFO replacement algorithm
    int page_faults = 0;
     
    // Print the statistics and run-time

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
