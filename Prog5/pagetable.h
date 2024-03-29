/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.h
 */

#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <algorithm> //find
#include <array>
#include <fstream>
#include <list>
#include <stdio.h> //printf()
#include <string>
#include <vector>

#include "functions.h"

// -------------------------- Page Entry ----------------------------------

// A page table entry
struct PageEntry
{
    // Logical address from file
    int logical_add;
    // Page Number
    int page_num;
    // Physical frame number for a given page
    int frame_num;
    // valid bit represents whether a page is in the physical memory
    bool valid = false;

    // Contructor
     PageEntry(): logical_add(0), page_num(0), frame_num(0) {} 

     PageEntry(int page): logical_add(0), page_num(page), frame_num(0) {} 

};

// ---------------------------- Page Table ---------------------------------

/**
 * A page table is like an array of page entries. 
 * The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
    private:
        int size;   // max capacity 32 MB = max virtual memory (128MB) / min page size (4MB)
        int count;  // number of entries in this table
        PageEntry* page_table;

    public:
        // Constructors
        PageTable();
        PageTable(int size);

        // Destructor
        ~PageTable();

        // -------------------- Page Table Useful Functions ----------------------------
        // Open file
        std::vector<int> open_file(std::string file_name);

        // Reset all pages in the table
        void reset_table();

        // Print page info
        void print_page(int log_add, int page_num, int fram_num, bool fault);

        // Print test statistics
        void print_stats(int ref, int p_fault, int p_replace);

        // ----------------------------- Replacement Algorithms ----------------------------
        void fifo(int index, std::list<int> &list);

        void random(int index);

        void lru(int index, std::list<int> &list);

        // ------------------------------------ Tests -------------------------------------

        /* Perform test 1
         * In the first test, your program should read and run the simulation for a small list 
         * of logical addresses (“small_refs.txt”). Assuming an initial empty physical memory, 
         * for each logical address in the list, print out its logical page #, physical frame #, 
         * and whether it caused a page fault or not.
         */
         void test1(std::string file_name, Parameters p);

        /* Perform test 2
         * In the second test, assuming an initial empty physical memory, your program should read 
         * and run the simulation for a large list of logical addresses (“large_refs.txt”), and 
         * collect and print the following statistics for different algorithms: 
         * – The total number of memory references.
         * – The total number of page faults.
         * – The total number of page replacements.
         * – The total time it took the simulator to produce the results.
         */
         void test2(std::string file_name, Parameters p);

};

#endif
