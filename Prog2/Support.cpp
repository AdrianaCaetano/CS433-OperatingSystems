/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.cpp
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Support.h"

// Show header with basic information about this program
void Support::show_header() {
        std::cout << std::endl;
        std::cout << "======================================================================" << std::endl << std::endl;
        std::cout << "CS 433 Programming assignment 2" << std::endl;
        std::cout << "Author: Adriana Caetano and Ryan Pisuena" << std::endl;
        std::cout << "Date: 10/14/2020" << std::endl;
        std::cout << "Course: CS433 (Operating Systems)" << std::endl;
        std::cout << "Description : Unix Shell and History Feature" << std::endl << std::endl;
        std::cout << "======================================================================" << std::endl << std::endl;
}

// Take a string as input to pase it
// @return command array
char** Support::get_input(char *input) {
        char** command = malloc(8 *sizeof(char*));
        char* separator = " ";
        char* parsed;
        int index = 0;

        //Test if you could allocate memmory for command
        if (command == NULL) {
                perror("malloc failed")'
                exit(1);
        }

        parsed = strtok(input, separator);
        while (parsed != NULL) {
                command[index] = parsed;
                index++;

                parsed = strtok(NULL, separator);
        }

        command[index] = NULL;
        return command;
}


~
~
"Support.cpp" 53L, 1443C                                      26,0-1 
