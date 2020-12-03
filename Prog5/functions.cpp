/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: functions.cpp
 */

#include <cctype> //isdigit()
#include <cmath> //log2()
#include <iostream>
#include <string>

#include "functions.h"

// Show header with program basic information
void Functions::show_header()
{
    std::cout << "\n=================================================================================\n\n";
    std::cout << "CS 433 Programming Assignemnt 5\n";
    std::cout << "Author: Adriana Caetano and Ryan Pisuena\n";
    std::cout << "Date: 12/11/2020\n";
    std::cout << "Course: CS433 (Operating Systems)\n";
    std::cout << "Description: Analysis of Page Replacement\n";
    std::cout << "\n=================================================================================\n\n";

}

// Check if input is a number
bool Functions::check_number(std::string input)
{
    for (unsigned int i = 0; i < input.length(); i++)
    {
        if (isdigit(input[i]) == false) { return false; }
    }
    return true;
}

// Show usage to user
std::string Functions::usage (char* name)
{
    std::string input = name; //convert c-string to string
    std::string message = "Usage: " ;
    std::string parameters = " [# page size] [# physical memory size]\n\n";

    return message + input + parameters;
}

// Validate program to start running
void Functions::valid_parameters(int argc, char* name)
{
    // Check if number of parameters is correct
    if (argc != 3)
    {
        std::cerr << "You have entered too few parameters to run the program.\n";
        std::cerr << "You must enter two command-line arguments:\n";
        std::cerr << " [# page size] = between 256 and 8192, inclusively (in bytes)\n";
        std::cerr << " [# physical memory size] = between 4 and 64, inclusively (in megabytes)\n";

        std::cerr << Functions::usage(name);

        exit(1);
    }
    return;
}

void Functions::show_error(std::string message, char* name)
{
    std::cerr << message << std::endl;
    std::cerr << Functions::usage(name);
    exit(1);
}

// Parse command line and return a struct with integer values for the parameters
Parameters Functions::get_parameters(int argc, char** argv)
{
    // Check if number of parameters is correct
    Functions::valid_parameters(argc, argv[0]);

    Parameters p; // struct to hold parameters' values

    // argv[1] = the number of the page size(in bytes)
    std::string input = argv[1];
    if (Functions::check_number(input))
    {
        p.page_size = stoi(input);
        if (Functions::isPowerOfTwo(p.page_size))
        {
            if (p.page_size < 256 || p.page_size > 8192)
            {
                Functions::show_error("Page size must be a between 256 (2^8) and 8192 (2^13) bytes, inclusively.", argv[0]);
            }
        }
        else
        {
            Functions::show_error("Page size must be a power of 2", argv[0]);
        }
    }
    else
    {
        Functions::show_error("Page size input is not an integer.", argv[0]);
    }

    // argv[2] = the number of the physical memory (in MB)
    input = argv[2];
    if (Functions::check_number(input))
    {
        p.physical_memory_size = stoi(input);
        if (Functions::isPowerOfTwo(p.physical_memory_size))
        {
            if (p.physical_memory_size < 4 || p.physical_memory_size > 64)
            {
                Functions::show_error("Physical memory size must be between 4MB (2^22) and 64MB (2^26), inclusively.", argv[0]);
            }
        }
        else
        {
            Functions::show_error("Physical memory must be a power of 2", argv[0]);
        }
    }
    else
    {
        Functions::show_error("Physical memory size input is not an integer.", argv[0]);
    }

    // transform to bytes and calculate remain Parameter p members
    Functions::calculate_parameters(& p);

    std::cout << "Page size = " << p.page_size << " bytes" << std::endl;
    std::cout << "Physical Memory size = " << p.physical_memory_size << " bytes" << std::endl;
    std::cout << "Number of pages = " << p.num_pages << std::endl;
    std::cout << "Number of physical frames = " << p.num_frames << std::endl;

    return p;
}

// calculate frames in bytes
void Functions::calculate_parameters(Parameters* p)
{
    //convert physical memory size from MB to bytes (= 2^20)
    p->physical_memory_size = p->physical_memory_size << 20;

    // calculate number of pages and frames

    // 27-bit logical memory (128 MB logical memory assumed by the assignment)
    int logic_mem_bits = 27;

    // Num of bits for physical memory addresses, calculated from physical memory size
    // e.g. 24 bits for 16 MB memory
    int phys_mem_bits = std::log2(p->physical_memory_size);

    // Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
    int page_offset_bits = std::log2(p->page_size);

    // Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
    p->num_pages = 1 << (logic_mem_bits - page_offset_bits);

    // Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
    p->num_frames = 1 << (phys_mem_bits - page_offset_bits);

}

// Check if an integer is power of 2
bool Functions::isPowerOfTwo(int x)
{
        /* First x in the below expression is for the case when x is 0 */
        return x && (!(x & (x - 1)));
}


