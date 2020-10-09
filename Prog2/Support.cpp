/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.cpp
 */

#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <typeinfo>
#include <unistd.h>

#include "Support.h"

#define MAX_LINE 80 /* The max length command */

using namespace std;

// Show header with basic information about this program
void support::show_header() {
        cout << "\n======================================================================\n\n";
        cout << "CS 433 Programming assignment 2\n";
        cout << "Author: Adriana Caetano and Ryan Pisuena\n";
        cout << "Date: 10/14/2020\n";
        cout << "Course: CS433 (Operating Systems)\n";
        cout << "Description : Unix Shell and History Feature\n";
        cout << "\n======================================================================\n\n";
}

/**********************************
 * PART I
 * In the new created Unix Shell
 * Read the User Input
 **********************************/

// Read the instruction
char support::get_input(void) {
        char* input;
	size_t inputSize;

	do {
		inputSize = getline(&input, &inputSize, stdin);

		//Test if command is empty
	        if (inputSize < 0) {
			printf("Error reading input.\n");
		}

        } while (input == NULL);

	return input;
}

// Split the instruction into commands/arguments
char** split_command(char* input) {
	char** cmd[MAX_LINE/2 +1]; 
	char* temp;
	int num_cmd = 0;

	do {
  		temp = strtok(input, " \t\r\a\n");
//		printf(typeid(temp).name());
	 	cmd[num_cmd] = temp;
		num_cmd++;
	} while (temp != NULL);

	cmd[num_cmd] = NULL;

        return cmd;
}


/***********************************************************
 * PART II
 * Executing the command in a child process
 * (1) fork a child process using fork()
 * (2) the child process will invoke execvp()
 * (3) parent will invoke wait() unless command included &
*************************************************************/

// Check command before creating a new process
int execute_command(char** cmd) {
	bool concurrent = false; // flag for parent process wait for child process
	int run = 1; // flag if it should continue running

	if (strcmp(cmd[0], "exit") { 
		run = 0;
		exit(0);
	}
	if (strcpm(cmd[0], "!!") {
		// run last command 
		cmd = get_history();
	} 

	for (auto i = 0; i < cmd.length(); i++) {
		if (strcpm(cmd[i], "&") { 
			// parent runs concurrently  
			concurrent = true;
		}
		if (strcpm(cmd[i], "|") {
			// create pipe 
		}
 	}
	run = execute(*cmd, concurrent);
	return run;  
}

// Execute command in a child process
int execute(char** cmd, bool concurrent) {
	//fork a child process
	pid_t pid = fork();

	if (pid < 0) {
		// error occurred
		printf("\nERROR: Fork failed.\n");
		exit(1);
	} 
	else if (pid == 0) { // child process
		//test command execution
		if (execvp(*cmd, cmd) < 0) {
			printf("\nERROR: Execution failed.\n");
			exit(1);
		} 
	else {	// parent process
		if (!concurrent) {
		 	//parent waits for child process to finish
		 	wait(NULL);
		}
	}
	return 0;
}



/****************************************************
 * PART III
 * Creating a history feature
 * Execute the most recent command by entering !!
 ****************************************************/

// TODO



/***************************************
 * PART IV
 * Redirecting Input and Output
 * Support < and > redirect commands
 ***************************************/

// TODO



/*****************************************************************
 * PART V
 * Communication via a Pipe
 * Send the output of one command as the input to another command
 *****************************************************************/

// TODO
