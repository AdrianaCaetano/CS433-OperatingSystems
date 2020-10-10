/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.h
 */

#ifndef SUPPORT_H
#define SUPPORT_H

#include <vector>
#include <string>
namespace support {

        // vector<string> history;
        // void showHistory();
        // void saveIntoHistory();
        // void showLastHistory();       


        // Show header with basic information about this program
        void show_header();

        // Take a string as input and parse it
        // @return array of commands
        char** get_input();

	      char** split_command(char* input);

	      bool execute(char** cmd);

}

#endif
