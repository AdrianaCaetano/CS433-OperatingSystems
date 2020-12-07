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
#include <stdio.h> //printf()
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
    PageEntry(int logical)
    {
        logical_add = logical;
        page_num = 0;
        frame_num = 0; 
    }
    PageEntry(int logical, int page)
    {
        logical_add = logical;
        page_num = page;
        frame_num = 0;
    }

    // Useful functions
    void print_entry()
    {
        printf("Logical Address: %11d,", logical_add); 
        printf("Page Number: %8d,", page_num); 
        printf("Frame Number: %4d,", frame_num); 
    }
};


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
        PageTable(int page_size, int num_pages);

        // Destructor
        ~PageTable();

        // Return the max capacity size of the page table
        int get_max_size();

        // Return the actual size of the page table
        int get_count();

        // Open file, read the logical address, return the logical address
        void open_file(std::string file_name, Parameters p);

        // Save entry into PageTable
        void save_to_table(int logical_add, Parameters p);

        // Print all entries of this table
        void print();

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
