/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: main.cpp
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "functions.h"
#include "pagetable.h"

int main(int argc, char* argv[]) {
    // Print basic information about the program
    Functions::show_header();

    // Get and Validate parameters from cmd
    Parameters p = Functions::get_parameters(argc, argv);


    // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
    std::cout <<"\n====================================  Test 1  ====================================\n\n";
    // Test 1 prints out logical page #, frame # and whether page fault for each logical address

    PageTable pageTable1(p.page_table_size);
//    PageTable pageTable1(p.page_size, p.num_pages);  // Create object to hold page table 1
    pageTable1.test1(p);   // Perform test 1

    // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
    std::cout <<"\n====================================  Test 2  ====================================\n\n";

    PageTable pageTable2(p.page_table_size); 
//    PageTable pageTable2(p.page_size, p.num_pages);  // Create object to hold page table 2
    pageTable2.test2(p);   // Perform test 2

}
