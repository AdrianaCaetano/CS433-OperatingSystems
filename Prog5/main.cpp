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


int main(int argc, char* argv[]) {
    // Print basic information about the program
    Functions::show_header();

    // Get and Validate parameters from cmd
    Parameters p = Functions::get_parameters(argc, argv);

    // Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
    std::cout <<"\n====================================  Test 1  ====================================\n\n";
    // TODO: Add your code here for test 1 that prints out logical page #, frame # and whether page fault for each logical address

    // Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
    std::cout <<"\n====================================  Test 2  ====================================\n\n";
    std::cout << " *************************   Simulate FIFO replacement   *************************\n\n";
    // TODO: Add your code to calculate number of page faults using FIFO replacement algorithm
    // TODO: print the statistics and run-time

    std::cout << " ************************   Simulate Random replacement   ************************\n\n";
    // TODO: Add your code to calculate number of page faults using Random replacement algorithm
    // TODO: print the statistics and run-time

    std::cout << " **************************   Simulate LRU replacement   *************************\n\n";
    // TODO: Add your code to calculate number of page faults using LRU replacement algorithm
    // TODO: print the statistics and run-time

}

