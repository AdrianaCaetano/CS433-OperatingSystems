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

	// Parse the input to get commands
	int split_command(char*, char**);
	
	// Check command to execute
	int execute_command(char**, int);
	
	// Execute command in a child process
	int execute(char** cmd, bool concurrent);

}

#endif
