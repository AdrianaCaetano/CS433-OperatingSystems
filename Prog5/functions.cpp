/*
 * Programming Assignment 5 - CS 433
 * Description: Analysis of Page Replacement
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 12/11/2020
 * File: functions.cpp
 */

#include <cctype> //isdigit()
#include <iostream>
#include <string>

#include "functions.h"

using namespace std;

// Show header with program basic information
void Functions::show_header()
{
    cout << "\n=================================================================================\n\n";
    cout << "CS 433 Programming Assignemnt 5\n";
    cout << "Author: Adriana Caetano and Ryan Pisuena\n";
    cout << "Date: 12/11/2020\n";
    cout << "Course: CS433 (Operating Systems)\n";
    cout << "Description: Analysis of Page Replacement\n";
    cout << "\n=================================================================================\n\n";
}


// Check if input is a number
bool Functions::check_number(string input)
{
    for (int i = 0; i < input.length(); i++)
    { 
        if (isdigit(input[i]) == false) { return false; }
    }
    return true;
}

// Show usage to user
string Functions::usage (char* name)
{
    string input = name; //convert c-string to string
    string message = "Usage: " ;
    string parameters = " [# page size] [# physical memory size]\n\n";

    return message + input + parameters;
}

// Validate program to start running
void Functions::valid_parameters(int argc, char* name)
{
    // Check if number of parameters is correct
    if (argc != 3) 
    { 
        cerr << "You have entered too few parameters to run the program.\n";
        cerr << "You must enter two command-line arguments:\n";
        cerr << " [# page size] = between 256 and 8192, inclusive (in bytes)\n";
        cerr << " [# physical memory size] = between 4 and 64, inclusive (in megabytes)\n";
        
        cerr << Functions::usage(name);

        exit(0);
    }
    return;    
}

void Functions::show_error(string message, char* name)
{
    cerr << message << endl;
    cerr << Functions::usage(name);
    exit(0);
}

// TODO FIX FROM HERE FOR PROG 5

// Parse command line and return a struct with integer values for the parameters
Parameters Functions::get_parameters(int argc, char** argv)
{
    // Check if number of parameters is correct
    Functions::valid_parameters(argc, argv[0]);

    Parameters p; // struct to hold parameters' values
    
    // argv[1] = how long the main thread sleep before terminating(in seconds)
    string input = argv[1];
    if (Functions::check_number(input))
    { 
        p.sleep_time = stoi(input);
        if (p.sleep_time < 1) 
        { 
            Functions::show_error("Sleep time must be a positive nonzero integer.", argv[0]);
        }
    }
    else 
    { 
        Functions::show_error("Sleep time input is not an integer.", argv[0]);
    } 

    // argv[2] = the number of producer threads
    input = argv[2];
    if (Functions::check_number(input))
    { 
        p.num_producers = stoi(input);
        if (p.num_producers < 0) 
        {
            Functions::show_error("Number of producer threads must be zero or a positive integer.", argv[0]);
        }
    }
    else 
    {    
        Functions::show_error("Number of producer threads is not an integer.", argv[0]);
    }
    
    // argv[3] = the number of consumer threads
    input = argv[3];
    if (Functions::check_number(input))
    { 
        p.num_consumers = stoi(input);
        if (p.num_consumers < 0) 
        {
            Functions::show_error("Number of consumer threads must be zero or a positive integer.", argv[0]);
        }
    }
    else 
    {    
        Functions::show_error("Number of consumer threads is not an integer.", argv[0]);
    }

    return p;
}
