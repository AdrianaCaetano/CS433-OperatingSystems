/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: main.cpp
 */

#include <cstdio>  	// printf(), fflush(), fgets()
#include <cstring>

#include "Support.h"


#define MAX_LINE 80 /* The max length command */
#define BUFFER_SIZE 100 
using namespace std;
using namespace support;

int main(void) {


        char input[MAX_LINE];
        char* commands[MAX_LINE]; /* command line arguments */
	char last_cmd[MAX_LINE]; /* hold history command */
	//int last_command_size;  /*Hold size of last command */
	int num_args = 0; 		/* hold number of command arguments */
	int should_run = 1; /* flag to determine when to exit the program */

        show_header();
	printf("This program simulates a shell.\n") ;
	printf("Please input your command.\n\n") ;
	
	//	fgets(input, MAX_LINE, stdin);
	//strcpy(last_cmd, input);
	
	
	while(should_run) {
	  printf("osh->");
	  fflush(stdout);

	  //save_into_history(input);
	  strcpy(last_cmd, input);

	  // get input
	  fgets(input, MAX_LINE, stdin);
	  
	  // parse command
	  num_args = split_command(input, commands);
	  
	  // save history
	  // save_into_history(input);
	  
	  // execute command
	  should_run = execute_command(commands, num_args, last_cmd);
	}
	
        printf("---------- End of Program ----------\n");
	
        return 0;
}

	
