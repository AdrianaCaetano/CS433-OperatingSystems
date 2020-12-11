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

// Print page info
void PageTable::print_page(int log_add, int page_num, int frame_num, bool valid)
{ 
    printf("Logical Address: %10d,  ", log_add);  
    printf("Page Number: %7d,  ", page_num); 
    printf("Frame Number: %3d,  ", frame_num); 
    printf("Page Fault? %s", valid ? "No" : "Yes");
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
// FIFO algorithm: replace the first loaded page 
void PageTable::fifo(int index, int &frame, int free_frames, int &page_faults,
		int &page_replace, std::list<int> &list) 
{
    page_faults++;	// this is a page fault   
    int victim;         // to hold victim page

    // Check if there are free frames
    if (frame <= free_frames) 
    {
        page_table[index].frame_num = frame; 	// get a free frame and set it to page
        page_table[index].valid = true; 	// change page valid bit
        frame++;  				// increment frame count 
        list.push_back(index);			// insert page at the end
    }
    else
    {   
        // Choose the first page in the list to be removed = victim
        victim = list.front();				// save victim page_num
        list.pop_front(); 				// remove the first page in the list
        page_table[victim].valid = false;   		// change page entry valid bit
        page_table[victim].dirty = true;     		// change page entry dirty bit
        int new_free_frame = page_table[victim].frame_num;  // get this page frame number
        page_replace++;					// increment page replacement counter
        
        // Save new page to the back of the list
        list.push_back(index);		
	page_table[index].frame_num = new_free_frame; 	// set the newly freed frame to the new page
        page_table[index].valid = true; 		// change valid bit of the new page 
    } 
} 

// RANDOM algorithm: choose a random page to be replaced 
void PageTable::random(int index, int &frame, int free_frames, int &page_faults, int &page_replace)
{
    int victim;
    page_faults++;	// this is a page fault   

    // Check if there are free frames
    if (frame <= free_frames) 
    {
        page_table[index].frame_num = frame; 	// get a free frame and set it to page
        page_table[index].valid = true; 	// change page valid bit
        frame++;  				//increment frame count 
    }
    else 
    {
        do 
        {
           victim = rand() % this->size;// choose a random page to be the victim
        } while (!page_table[victim].valid); 	// check if it is loaded into memory

        //update victim parameters
        int free_frame = page_table[victim].frame_num; // get frame from victim
        page_table[victim].valid = false;
        page_table[victim].dirty = true;
        
        // update new page
        page_table[index].frame_num = free_frame;
        page_table[index].valid = true;
        
        page_replace++;   // increment counter
    }   
}


// LRU algorithm
void PageTable::lru(int index, int &frame, int free_frames, int &page_faults, 
		int &page_replace, std::list<int> &list)
{
    int victim;
    page_faults++;	// this is a page fault, update counter   

//    std::cout << "** Replace page\n";

    // Check if there are free frames
    if (frame <= free_frames) 
    {
//        std::cout << "** Insert page in the LRU list\n";
        page_table[index].frame_num = frame; 	// get a free frame and set it to page
        page_table[index].valid = true; 	// change page valid bit
        frame++;  				// increment frame count
        list.push_front(index);			// include this page in the LRU list 
    }
    else 
    {   
        if (!list.empty())
        {
//            std::cout << "** Find a victim\n";
            victim = list.back();	// get the least used page to be the victim
//            std::cout << "** Remove victim from LRU list\n";
            list.pop_back();        // remove victim from lru list

//            std::cout << "** Update victim parameters\n";
            int free_frame = page_table[victim].frame_num; // get frame from victim
            page_table[victim].valid = false;
            page_table[victim].dirty = true;
        
//            std::cout << "** Update new page\nu;
            page_table[index].frame_num = free_frame;
            page_table[index].valid = true;
        
            page_replace++;   // increment counter
        }
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
            // page is already loaded into memory
            PageTable::print_page(refAddress, page_index, page_table[page_index].frame_num, true);  	// print page
            continue;
        }
        // replace page
        PageTable::fifo(page_index, frame, p.num_frames, page_faults, page_replace, list_pages);       
        PageTable::print_page(refAddress, page_index, page_table[page_index].frame_num, false);
    }
    std::cout << std::endl;
    PageTable::print_stats(references, page_faults, page_replace);
    list_pages.clear();
}

// ---------------------------------------- TEST 2 ---------------------------------------------
// Perform test 2
void PageTable::test2(std::string file_name, Parameters p)
{
    std::cout << "Start timer for Test 2\n\n";
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
        // replace page
        PageTable::fifo(page_index, frame, p.num_frames, page_faults, page_replace, list);       
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
        // replace page
        PageTable::random(page_index, frame, p.num_frames, page_faults, page_replace);       
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
    list.clear();	// hold lru oreder of pages

    // Start timer for Random algorithm
    auto startLRU = std::chrono::steady_clock::now();

    while (references < large_input.size())
    {
        refAddress = large_input[references]; // get next address in the large_refs file
        page_index = refAddress / p.page_size;
        references++;

        if (page_table[page_index].valid == true)
        { 
            // page is already loaded into memory
//            std::cout << "__ Find the page in the LRU list and bring it to the front\n";
            auto it = std::find(list.begin(), list.end(), page_index);
            if (it != list.end())
            {
//               std::cout << "__ Remove page from LRU list\n";
                list.erase(it);   // remove from middle
            }
//            std::cout << "__ Bring page to the front\n";
            list.push_front(page_index); // bring to front
            continue;
        }
//        std::cout << "__ Replace page\n";
        PageTable::lru(page_index, frame, p.num_frames, page_faults, page_replace, list);
    }
 
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
