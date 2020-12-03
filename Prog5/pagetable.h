/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.h
 */

#ifndef PAGETABLE_H
#define PAGETABLE_H


// Remember to add comments to your code

// A page table entry
struct PageEntry
{

    // Physical frame number for a given page
    int frame_num;
    // valid bit represents whether a page is in the physical memory
    bool valid = false;
    // dirty bit represents whether a page is changed
    bool dirty = false;
};


/**
 * A page table is like an array of page entries. 
 * The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
    private:
        int size;
        PageEntry* page_table;

    public:
        // Constructors
        PageTable();
        PageTable(int size);

        // Destructor
        ~PageTable();

};

#endif

