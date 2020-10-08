/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.cpp
 */

#include <iostream>
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
        cout << endl;
        cout << "======================================================================" << std::endl << endl;
        cout << "CS 433 Programming assignment 2" << endl;
        cout << "Author: Adriana Caetano and Ryan Pisuena" << endl;
        cout << "Date: 10/14/2020" << endl;
        cout << "Course: CS433 (Operating Systems)" << endl;
        cout << "Description : Unix Shell and History Feature" << endl << endl;
        cout << "======================================================================" << endl << endl;
}

/**********************************
 * PART I
 * In the new created Unix Shell
 * Read the User Input
 **********************************/

// Read the instruction
char* support::get_input(void) {
        char*  input = NULL;
	size_t inputSize;

	do {
		inputSize = getline(&input, &inputSize, stdin);

		//Test if command is empty
	        if (inputSize == -1 && inputSize < MAX_LINE) {
			printf("Error reading input.\n");
		}

        } while (input == NULL);

	return input;
}
/*
// Split the instruction into commands/arguments
char** split_command(char* input) {
	char** cmd[MAX_LINE/2 +1];
	char* temp;
	int num_cmd = 0;

	do {
  		temp = strtok(input, " \t\r\a\n");
		printf(typeid(temp).name());
//	 	cmd[num_cmd] = temp;
		num_cmd++;
	} while (temp != NULL);

	cmd[num_cmd] = NULL;

        return cmd;
}

*/

/***********************************************************
 * PART II
 * Executing the command in a child process
 * (1) fork a child process using fork()
 * (2) the child process will invoke execvp()
 * (3) parent will invoke wait() unless command included &
*************************************************************/

// Execute command in a child process
bool execute(char** cmd) {
	pid_t pid = fork();
	bool run = true;

	if (pid < 0) {
		printf("\nFork failed.\n");
		run = false;
	} else if (pid == 0) {
		if (cmd[0] == NULL) {
			printf("\nExecution failed.\n");
			run = false;
		} else {
/*
                	if (cmd == exit) { exit() };
			save cmd to history
			execvp (cmd, args);
                	if (cmd does not end with &) {
                		wait();
                	}
*/		}
	}
	return run;
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
