/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.cpp
 */

// #include <algorithm>	// find()
#include <array>
#include <chrono> 	// timer
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "functions.h"
#include "pagetable.h"

// -------------------- PAGE TABLE --------------------------
// ----------- Constructors
PageTable::PageTable() {}

PageTable::PageTable(int size)
{
    this->size = size;  // max array size
    this->count = 0;    // num elements in the  array
    this->page_table = new PageEntry [this->size];

    while (this->count < this->size)
    {
        // Save a new PageEntry into the table
        this->page_table[this->count] = PageEntry(this->count);
        this->count++; 			// update table count
    }  
    std::cout << "PageTable ready with " << this->count << " entries.\n";

}

// ------------ Destructor
PageTable::~PageTable()
{
    delete [] page_table;
}

// ------------- Page Table Useful Methods

// Open file and return a integer vector with file inputs
std::vector<int> PageTable::open_file(std::string file_name)
{
    std::ifstream fin;
    fin.open(file_name, std::ifstream::in); // open file

    if ( fin.fail() )
    {
        std::cerr << "Could not open file " << file_name << std::endl;
        exit(1); // 1 indicates an error occurred
    }
        
    std::cout << "Opening file " << file_name << std::endl;

    std::vector <int> file_references;  // container to hold file values
    std::string input;			// variable to read from file
    int references;			// file input counter
    int refAddress; 			// variable to hold integer value


    while (fin >> input)
    {
        if (Functions::check_number(input))
        {
            refAddress = std::stoi(input); 
        }
        // push into vector
        file_references.push_back(refAddress);
        references++;

    }
    fin.close(); // close file

    file_references.shrink_to_fit(); // free unused memory

    std::cout << "Total number of references: " << file_references.size() << std::endl << std::endl;

    return file_references;
}

// Reset all pages in the table
void PageTable::reset_table()
{
    for (auto page = 0; page < this->size; page++)
    { 
        page_table[page].valid = false;
        page_table[page].logical_add = 0;
        page_table[page].frame_num = 0;
    }
}

// Print page info
void PageTable::print_page(int log_add, int page_num, int frame_num, bool fault)
{ 
    printf("Logical Address: %10d,  ", log_add);  
    printf("Page Number: %7d,  ", page_num); 
    printf("Frame Number: %3d,  ", frame_num); 
    printf("Page Fault? %4s  ", fault ? "No" : "Yes");
    printf("\n");
}


// Print test statistics
void PageTable::print_stats(int ref, int p_fault, int p_replace)
{
    std::cout << "Number of references:          " << ref << std::endl;
    std::cout << "Number of page faults:         " << p_fault << std::endl;
    std::cout << "Number of page replacements:   " << p_replace << std::endl;
}

// ------------------------------- REPLACEMENT ALGORITHMS ----------------------------------
//
// FIFO algorithm: replace the first loaded page ------------------------------------------- 
void PageTable::fifo(int index, std::list<int> &list) 
{
    int victim;         // to hold victim page

    // Choose the first page in the list to be removed = victim
    victim = list.back();				// save victim page_num
    list.pop_back(); 				// remove the first page in the list
    page_table[victim].valid = false;   		// change victim valid bit to false
    int new_free_frame = page_table[victim].frame_num;  // get victim frame number
        
    // Save new page on the list and update it
    list.push_front(index);
    page_table[index].frame_num = new_free_frame; 	// set the newly freed frame to the new page
    page_table[index].valid = true; 		// change valid bit of the new page 
} 

// RANDOM algorithm: choose a random page to be replaced --------------------------------------
void PageTable::random(int index)
{
    int victim;
    do 
    {
       victim = rand() % this->size;		// choose a random page to be the victim
    } while (!page_table[victim].valid); 	// check if it is loaded into memory

    //update victim parameters
    int free_frame = page_table[victim].frame_num; // get frame from victim
    page_table[victim].valid = false;
        
    // update new page
    page_table[index].frame_num = free_frame;
    page_table[index].valid = true;
}


// LRU algorithm: Replace the least recently used page -------------------------------- 
void PageTable::lru(int index, std::list<int> &list)
{
    int victim;
//    if (!list.empty())
    {
//        std::cout << "** Find a victim: ";
        victim = list.back();	// get the least used page to be the victim
//        std::cout << "** Remove victim from LRU list\n";
        list.pop_back();        // remove victim from lru list
//        std::cout << victim;

//        std::cout << " ** Update victim parameters ";
        int free_frame = page_table[victim].frame_num; // get frame from victim
        page_table[victim].valid = false;
 
//        std::cout << " ** Update new page " << index << std::endl;;
        page_table[index].frame_num = free_frame;
        page_table[index].valid = true;
        list.push_front(index);       // include this page in the list       
    }   
}


// -------------------------------------- TEST 1 --------------------------------------------
// Perform Test 1
void PageTable::test1(std::string file_name, Parameters p)
{
    std::vector<int> file_input = PageTable::open_file(file_name);
    
    int refAddress;    		// hold the logical address listed on file
    int references = 0; 	// hold the number of references of the file
    int page_index; 		// hold the index of the page for the refered address
    int frame = 0; 		// frame counter
    int page_faults = 0;	// page faults counter
    int page_replace = 0; 	// page repacement counter

    std::list<int> list_pages;	// list of loaded pages in memory

    while (references < file_input.size())
    {
        refAddress = file_input[references]; // get next address in the file_input
        page_index = refAddress / p.page_size;
        references++;

        if (page_table[page_index].valid == true)
        {
            // Page is already loaded into memory, not a page fault. Print page
            PageTable::print_page(refAddress, page_index, page_table[page_index].frame_num, true);
            continue;
        }
        else 
        {
            // This is a page fault
            page_faults++;		// increment page faults
            // Check if there are free frames
            if (frame <= p.num_frames) 
            {
                // Load page into memory using a free frame, change valid_bit, push into the list
                page_table[page_index].frame_num = frame; 	// get a free frame and set it to page 
                page_table[page_index].valid = true; 		// change page valid bit to true
                frame++;  					// increment frame count 
                list_pages.push_front(page_index);		// insert page on the list
            }
            else
            {    // Replace the page
                 page_replace++;	// increment page replacement counter
                 PageTable::fifo(page_index, list_pages);       
            }
            PageTable::print_page(refAddress, page_index, page_table[page_index].frame_num, false);
        }
    }
    std::cout << std::endl;
    PageTable::print_stats(references, page_faults, page_replace);
    list_pages.clear();
    PageTable::reset_table();
}

// ---------------------------------------- TEST 2 ---------------------------------------------
// Perform test 2
void PageTable::test2(std::string file_name, Parameters p)
{
    std::cout << "Start timer for Test 2\n";
    auto start = std::chrono::steady_clock::now();

    std::vector<int> large_input = PageTable::open_file("large_refs.txt");

    int refAddress;    		// hold the logical address listed on file
    int references = 0; 	// hold the number of references of the file
    int page_index; 		// hold the index of the page for the refered address
    int frame = 0; 		// frame counter
    int page_faults = 0;	// page faults counter
    int page_replace = 0; 	// page repacement counter

    std::cout << " *************************   Simulate FIFO replacement   *************************\n\n";
    // Calculate number of page faults using FIFO replacement algorithm
    // start timer for FIFO algorithm
    auto startFIFO = std::chrono::steady_clock::now();
 
    std::list<int> list;	// list of loaded pages in memory

    while (references < large_input.size())
    {
        refAddress = large_input[references]; // get next address in the large_refs file
        page_index = refAddress / p.page_size;
        references++;

        if (page_table[page_index].valid == true)
        { 
            // page is already loaded into memory
            continue;
        } 
        else 
        {
            page_faults++;	// this is a page fault   
        
            // Check if there are free frames
            if (frame <= p.num_frames) 
            {
                // Load page into memory using a free frame, change valid_bit, push into the list
                page_table[page_index].frame_num = frame; 	// get a free frame and set it to page 
                page_table[page_index].valid = true; 	// change page valid bit to true
                frame++;  				// increment frame count 
                list.push_front(page_index);			// insert page on the list
            }
            else
            {
                // replace page
                page_replace++;
                PageTable::fifo(page_index, list);       
            }
        }
    }
 
    auto endFIFO = std::chrono::steady_clock::now(); //end time measument for test 2
    std::chrono::duration<double> elapsed_seconds_FIFO = endFIFO - startFIFO;
	
    // Print the statistics and run-time
    PageTable::print_stats(references, page_faults, page_replace);
    
    std::cout << "Elapsed time (in seconds):     " << elapsed_seconds_FIFO.count() << std::endl;
     
    std::cout << " \n*************************   Simulate RANDOM replacement   ************************\n\n";
    // Calculate number of page faults using Random replacement algorithm

    // Reset all counters
    references = 0; 	// hold the number of references of the file
    frame = 0; 		// frame counter
    page_faults = 0;	// page faults counter
    page_replace = 0; 	// page repacement counter
    PageTable::reset_table();

    // Start timer for Random algorithm
    auto startRandom = std::chrono::steady_clock::now();

    while (references < large_input.size())
    {
        refAddress = large_input[references]; // get next address in the large_refs file
        page_index = refAddress / p.page_size;
        references++;

        if (page_table[page_index].valid == true)
        { 
            // page is already loaded into memory
            continue;
        } 
        else 
        {        
            page_faults++;	// this is a page fault   

            // Check if there are free frames
            if (frame <= p.num_frames) 
            {
                page_table[page_index].frame_num = frame; 	// get a free frame and set it to page
                page_table[page_index].valid = true;	 	// change page valid bit
                frame++;  					//increment frame count 
            }
            else 
            {
                // replace page
                page_replace++;
                PageTable::random(page_index);
            }
        }
    }
 
    auto endRandom = std::chrono::steady_clock::now(); //end time measument for Random Algorithm
    std::chrono::duration<double> elapsed_seconds_Random = endRandom - startRandom;
	
    // Print the statistics and run-time
    PageTable::print_stats(references, page_faults, page_replace);
    
    std::cout << "Elapsed time (in seconds):     " << elapsed_seconds_Random.count() << std::endl;

    std::cout << " \n***************************   Simulate LRU replacement   *************************\n\n";
    // Calculate number of page faults using LRU replacement algorithm

    // Reset all counters
    references = 0; 	// hold the number of references of the file
    frame = 0; 		// frame counter
    page_faults = 0;	// page faults counter
    page_replace = 0; 	// page repacement counter
    list.clear();	// hold lru order of pages
    PageTable::reset_table();

    // Start timer for Random algorithm
    auto startLRU = std::chrono::steady_clock::now();

    while (references < large_input.size())
    {
        refAddress = large_input[references]; // get next address in the large_refs file
        page_index = refAddress / p.page_size;
        references++;
        
//        std::cout << "Logical = " << refAddress << " Page = " << page_index;
//        std::cout << "Reference = " << refAddress  << std::endl;

        if (page_table[page_index].valid == true)
        { 
            // page is already loaded into memory
   //         std::cout << " Find the page in the LRU list: ";
   //
            for (auto it = list.begin(); it != list.end(); it++)
            {          
                if (*it == page_index)
                {
     //               std::cout << " It's a hit. ";
                    //  Move page to the front of the list
                    list.erase(it);
//                    std::cout << "Removed" ;
                    list.push_front(page_index);
//                    std::cout << " and placed in front\n";
                    break;   // Found! Go to the next in the list
                }
            }
       //     std::cout << "Out of for loop\n";
           continue;
       //     std::cout << "ERROR: It's not in the list\n";
        }
        else 
        {
       //     std::cout << " It's a miss. Page fault!";
            page_faults++;	// this is a page fault, update counter   

            // Check if there are free frames
            if (frame <= p.num_frames) 
            {
       //         std::cout << " Get a free frame.\n";
                // Insert page in the LRU list
                page_table[page_index].frame_num = frame; 	// get a free frame and set it to page
                page_table[page_index].valid = true; 		// change page valid bit
                frame++;  					// increment frame count
                list.push_front(page_index);			// include this page in the LRU list 
            }
            else 
            {   
 //             std::cout << " Replace page\n";
                page_replace++;		//update page replacement counter
                PageTable::lru(page_index, list);
            }
        }
 //       std::cout << "Get next reference\n";
    }
//    std::cout << "Out of while loop\n";
 
    auto endLRU = std::chrono::steady_clock::now(); //end time measument for Random Algorithm
    std::chrono::duration<double> elapsed_seconds_LRU = endLRU - startLRU;
	
    // Print the statistics and run-time
    PageTable::print_stats(references, page_faults, page_replace);
    
    std::cout << "Elapsed time (in seconds):     " << elapsed_seconds_LRU.count() << std::endl;

    // Print overall Test2 runtime
    auto end = std::chrono::steady_clock::now(); //end time measument for test 2
    std::chrono::duration<double> elapsed_seconds = end - start;	
    std::cout << "\nTest 2 runtime = " << elapsed_seconds.count() << " seconds\n\n";
}

// ----------------------------------------------------------------------------------------------
