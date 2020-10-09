/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.h
 */

#ifndef SUPPORT_H
#define SUPPORT_H

namespace support {

        // Show header with basic information about this program
        void show_header();

        // Take a string as input
        char* get_input();
	
	// Parse the input to get commands
	char** split_command(char* input);
	
	// Check command to execute
	int execute_command(char** cmd);
	
	// Execute command in a child process
	int execute(char** cmd, bool concurrent);

}

#endif
