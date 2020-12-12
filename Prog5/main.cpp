/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: main.cpp
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime> 
#include <vector>

#include "functions.h"
#include "pagetable.h"

int main(int argc, char* argv[]) {
    // Print basic information about the program
    Functions::show_header();

    // Get and Validate parameters from cmd
    Parameters p = Functions::get_parameters(argc, argv);

    // Create a page table with page entries
    PageTable pageTable(p.page_table_size);

    // Use current time as seed to random generator 
    std::srand(std::time(nullptr));
 
    // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
    std::cout <<"\n====================================  Test 1  ====================================\n\n";
    // Test 1 prints out logical page #, frame # and whether page fault for each logical address

    pageTable.test1("small_refs.txt", p);   // Perform test 1

    // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
    std::cout <<"\n====================================  Test 2  ====================================\n\n";

    pageTable.test2("large_refs.txt", p);   // Perform test 2

}
