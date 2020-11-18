/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: functions.h
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// Structure to hold parameters
struct Parameters
{
    int sleep_time;
    int num_producers;
    int num_consumers;
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

}

#endif
