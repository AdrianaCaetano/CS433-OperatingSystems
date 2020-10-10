/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.cpp
 */

#include <cstdio> 	// fgets(), stdin
#include <cstring> 	// strcmp(), strtok()
#include <iostream> 	// exit(), cout
#include <sys/wait.h> 	// wait()
#include <unistd.h> 	// fork(), execvp()

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

// Split the instruction into commands/arguments
int support::split_command(char* input, char** cmd) {	
	char* temp;
	int num_cmd = 0;

	if (!input) { return num_cmd; }
	
	temp = strtok(input, " \t\r\a\n");
	while (temp != NULL) {
		cmd[num_cmd] = temp;
		num_cmd++;
		temp = strtok(NULL, " \t\r\a\n");
	}
	cmd[num_cmd] = NULL; // last element is null
	return num_cmd;
} 


/***********************************************************
 * PART II
 * Executing the command in a child process
 * (1) fork a child process using fork()
 * (2) the child process will invoke execvp()
 * (3) parent will invoke wait() unless command included &
*************************************************************/

// Check command before creating a new process
int support::execute_command(char** cmd, int num_arg) {
	bool concurrent = false; // flag for parent process wait for child process
	int run = 1; // flag if it should continue running

	if (cmd == NULL) { exit(0); }

	if (strcmp(cmd[0], "exit") == 0) { 
		printf("Good bye!\n");
		run = 0;
		return run;
	}

	if (strcmp(cmd[0], "!!") == 0) {
		printf("Execute previous command\n");
		//cmd = previous
	}

	int i = 0; //iterator 

	while (i < num_arg) {

		if (strcmp(cmd[i], "&") == 0 ) { 
			printf("Parent runs concurrently\n");  
			concurrent = true; 	// change flag
			cmd[i] = NULL;		// delete & character from command
		}	

		if (strcmp(cmd[i], "|") == 0) {
			printf("Create pipe\n"); 
		}
		if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], ">>") == 0) {
			printf("Output redirection\n");
		} 
		if (strcmp(cmd[i], "<") == 0 || strcmp(cmd[i], "<<") == 0) { 
			printf("Input redirection\n"); 
		}
		i++;
 	}

	run = support::execute(cmd, concurrent);
	return run;  
} // end of execute_command

// Execute command in a child process
int support::execute(char** cmd, bool concurrent) {
//	cout << "inside execute\n"; // DELETE
	//fork a child process
	pid_t pid = fork();
	int status;
	
	if (pid < 0 ) { 
		// fork failed
		printf("Error: Forked failed\n");
		exit(1);
	} 
	else if (pid == 0) {
		// Child process 
//		cout << "child process\n"; // DELETE
		if (execvp(*cmd, cmd) < 0) {
			printf("Error: Execution failed, command not known\n");
			exit(1);
		}
	} 
	else { 
		// Parent process
//		cout << "parent process\n";  // DELETE
		if (!concurrent) { 
			// Wait for child process to end
			while(wait(&status) != pid);
		}
	}
	return 1;
} // end of execute
	



/* PART III
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
