/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: main.cpp
 */

#include <cstdio>  	// printf(), fflush(), fgets()

#include "Support.h"


#define MAX_LINE 80 /* The max length command */

using namespace std;
using namespace support;

int main(void) {


        char input[MAX_LINE];
        char* commands[MAX_LINE/2 + 1]; /* command line arguments */
	char* last_cmd[MAX_LINE/2 + 1]; /* hold history command */
	int num_args = 0; 		/* hold number of command arguments */
	int should_run = 1; /* flag to determine when to exit the program */

        show_header();
	printf("This program simulates a shell.\n") ;
	printf("Please input your command.\n\n") ;

	while(should_run) {
		printf("osh->");
		fflush(stdout);


		// get input
		fgets(input, MAX_LINE, stdin);
		
		// parse command
		num_args = split_command(input, commands);
		
		// execute command
		should_run = execute_command(commands, num_args);
	}

        printf("---------- End of Program ----------\n");

        return 0;
}

	
