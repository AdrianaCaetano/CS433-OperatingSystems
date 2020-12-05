/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.h
 */

#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <array>
#include <string>

#include "functions.h"

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
    // dirty bit represents whether a page is changed
    bool dirty = false;

    // Contructor
    PageEntry() {};
    PageEntry(int logical, int page)
    {
        logical_add = logical;
        page_num = page;
        frame_num = 0;
    }
};


/**
 * A page table is like an array of page entries. 
 * The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
    private:
        int size;   // 32 MB = max virtual memory (128MB) / min page size (4MB)
        PageEntry** page_table;

    public:
        // Constructors
        PageTable();
        PageTable(int size);
        PageTable(int page_size, int num_pages);

        // Destructor
        ~PageTable();

        // Return the size of the page table
        int get_size();

        // Open file, read logical address, return a page entry
        void open_file(std::string file_name, int page_size);

        /* Perform test 1
         * In the first test, your program should read and run the simulation for a small list 
         * of logical addresses (“small_refs.txt”). Assuming an initial empty physical memory, 
         * for each logical address in the list, print out its logical page #, physical frame #, 
         * and whether it caused a page fault or not.
         */
         void test1(Parameters p);

        /* Perform test 2
         * In the second test, assuming an initial empty physical memory, your program should read 
         * and run the simulation for a large list of logical addresses (“large_refs.txt”), and 
         * collect and print the following statistics for different algorithms: 
         * – The total number of memory references.
         * – The total number of page faults.
         * – The total number of page replacements.
         * – The total time it took the simulator to produce the results.
         */
         void test2(Parameters p);

};

#endif
