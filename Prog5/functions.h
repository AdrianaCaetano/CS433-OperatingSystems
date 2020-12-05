/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement Algorithm
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: functions.h
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

// Structure to hold parameters
struct Parameters
{
    int page_size;
    int physical_memory_size;
    int num_pages;
    int num_frames;
    int page_table_size;
};

// General Functions
namespace Functions
{
    // Show header with program basic information
    void show_header();

    // Show error message
    void show_error(std::string message, char* name);

    // check if input is a number
    bool check_number(std::string input);

    // Show usage to the user
    std::string usage(char* name);

    // Check if number of parameters is correct
    void valid_parameters(int argc, char* argv);

    // parse command line and save parameters into a struct
    Parameters get_parameters(int argc, char** argv);

    // calculate parameters in bytes
    void calculate_parameters(Parameters* p);

    // check if x is an even number
    bool isPowerOfTwo(int x);
}

#endif

