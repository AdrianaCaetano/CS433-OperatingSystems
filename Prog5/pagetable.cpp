/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: pagetable.cpp
 */

#include <fstream> // file
#include <iostream>
#include <stack>
#include <string>

#include "functions.h"
#include "pagetable.h"

// TODO: Add your implementation of PageTable

// Constructors
PageTable::PageTable() {}

// Destructor
PageTable::~PageTable()
{
    while (!page_table.empty())
    {
        page_table.pop();
    }
}

// Return the size of the page table
int PageTable::get_size()
{
    return int(this->page_table.size());
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

    while (fin >> input)
    {
        refAddress = std::stoi(input);
        page_number = refAddress / page_size;
        PageEntry entry = PageEntry(refAddress,page_number);
        this->page_table.push(&entry);
    }

    fin.close(); // close file

    std::cout << "Total number of references: " << this->page_table.size() << std::endl;
}

// Perform Test 1
void PageTable::test1(Parameters p)
{
   PageTable::open_file("small_refs.txt", p.page_size);
}

// Perform test 2
void PageTable::test2(Parameters p)
{
   PageTable::open_file("large_refs.txt", p.page_size);
}
