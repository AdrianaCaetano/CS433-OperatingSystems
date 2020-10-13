/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.cpp
 */

#include <cstring>	//strcmp(), strtok()
#include <fcntl.h>	// obtain O_* definitions
#include <iostream>	// exit(), cout
#include <sys/wait.h>	// wait()
#include <unistd.h>	// fork(), execvp()

#include "Support.h"

#define MAX_LINE 80 		/* The max input length */
#define BUFFER_SIZE 100 
using namespace std;

char support::last_cmd[MAX_LINE]; /* hold history command */
int support::last_command_size;  /*Hold size of last command */

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
int support::execute_command(char** cmd, int num_arg, char * last_cmd) {
	bool concurrent = false; // flag for parent process wait for child process
	int run = 1; // flag if it should continue running

	if (cmd == NULL) { return run; }

	if (strcmp(cmd[0], "exit") == 0) { 
		printf("Good bye!\n");
		run = 0; // change flag to stop running
		return run;
	}

	if (strcmp(cmd[0], "!!") == 0) {
	  if(last_cmd == NULL) {
	      cout << "No previous command found." << endl;
	      exit(0);
	    }
	    //cmd = previous
      num_arg = support::get_last_command(last_cmd, cmd);
	}
	
	int i = 0 ; // iterator
	int separator; // hold position of command separator 
	char* cmd1[MAX_LINE/4 + 1]; // first command up to separator
	char* cmd2[MAX_LINE/4 + 1]; // second command after separator
	
	while (i < num_arg) {

		if (strcmp(cmd[i], "&") == 0 ) { // Parent runs concurrently  
			concurrent = true;  	// change flaf
			cmd[i] = NULL; 		// delete & character from command
			num_arg--;		// decrement num_arg after deleting &
			run = support::execute(cmd, concurrent);
			return run;
		}

		if (strcmp(cmd[i], "|") == 0) { // Create pipe
			separator = i; // position of |
			support::separate_commands(cmd, num_arg, separator, cmd1, cmd2);
			if ((cmd1 != NULL) && (cmd2 != NULL)) {
				// Create the pipe
				support::pipe_cmd(cmd1, cmd2);
			} else {
				printf("ERROR: Parsing commands failed\n");
			}
			return run;
		}

		if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], "<") == 0) { // Redirection
			separator = i; // position of > or <

			run = support::redirect(cmd, num_arg, separator);
			return run;
		}
		i++;	// increment iterator
	}
	run = support::execute(cmd, concurrent);
	return run;  
	
} // end of execute_command

// Execute command in a child process
int support::execute(char** cmd, bool concurrent) {
	//fork a child process
	pid_t pid = fork();
	
	if (pid < 0 ) { 
		// fork failed
		printf("Error: Forked failed\n");
		exit(1);
	} 
	else if (pid == 0) {
		// Child process
		if (execvp(*cmd, cmd) < 0) {
			printf("Error: Execution failed, command not found\n");
			exit(1);
		}
	} 
	else { 
		// Parent process
		if (!concurrent) { 
			// Wait for child process to end
			wait(NULL);
		}
	}
	return 1;
}

// Separate commands before and after the separator character
void support::separate_commands(char** cmd, int num_arg, int separator, char** cmd1, char** cmd2) {
	for (int i = 0; i < separator; i++) { 
		cmd1[i] = cmd[i];
	}
	
	int index = 0;
	for (int i = separator + 1; i < num_arg; i++) { 
		cmd2[index] = cmd[i];
		index++;
	}
	cmd1[separator] = NULL; // last element is null
	cmd2[index] = NULL; 	// last element is null
}


/****************************************************
 * PART III
 * Creating a history feature
 * Execute the most recent command by entering !!
 ****************************************************/

int support::get_last_command(char* last_cmd, char** cmd)
{
  int numCommands = split_command(last_cmd, cmd);
  return numCommands;
}


/***************************************
 * PART IV
 * Redirecting Input and Output
 * Support < and > redirect commands
 ***************************************/

// Redirect input/output from/to file
int support::redirect(char** cmd, int num_arg, int separator) {
	char* cmd1[MAX_LINE/4 + 1];	// command 
	char* file[MAX_LINE/4 + 1];	// file name
	int fd_in; 	// input file descriptor
	int fd_out; 	// output file descriptor
	int run = 1; 	// flag to keep in the loop
	pid_t pid; 	

	// separate command and file name 
	support::separate_commands(cmd, num_arg, separator, cmd1, file);

	pid = fork();
	if (pid < 0) { 
		printf("ERROR: Fork failed\n");
		return run;
	}
	if (pid == 0) { // Child process
		if (strcmp(cmd[separator], "<") == 0) { // Redirect input
			// Open file read only
			if ((fd_in = open(file[0], O_RDONLY)) < 0) { 
				printf("ERROR: Cannot open this file\n");
				return run;
			}
			// Replace standard input with input file
			if (dup2(fd_in, 0) < 0) {
				printf("ERROR: Unnable to duplicate file descriptor");
				return run;
			}
		} 
		
		if (strcmp(cmd[separator], ">") == 0) { // Redirect output		
			// open file write only, create file with user/group write/read permission
			fd_out = open(file[0], O_WRONLY | O_CREAT, S_IWUSR | S_IWGRP | S_IRUSR | S_IRGRP);

			if (fd_out < 0) { 
				printf("ERROR: Cannot open this file\n");
				return run;
			}
			// Replace standad output with output file
			if (dup2(fd_out, 1) < 0) {
				printf("ERROR: Unable to duplicate file descriptor");
				return run;
			}	
		}

		//Child process runs the command
		if (execvp(cmd1[0], cmd1) < 0) { 
			printf("ERROR: Command execution failed.\n");
		}
	} else { 
		// parent waits
		wait(NULL);
	}	
	return run;
}


/*****************************************************************
 * PART V
 * Communication via a Pipe
 * Send the output of one command as the input to another command
 *****************************************************************/

// Creates a pipe to send output of cmd 1 to input of cmd 2
void support::pipe_cmd(char** cmd1, char** cmd2) {
	int pipefd[2]; 		// file descriptors
	pid_t pid1 = fork(); 	// child 1
	pid_t pid2;

	if (pipe(pipefd) < 0) { 
		printf("ERROR: Pipe failed\n");
		return;
	}
	if (pid1 < 0) { 
		printf("ERROR: Fork failed\n");
	}

	// Child process runs cmd 1
	if (pid1 == 0) {	
		// Child1 process writes to pipe 

		// fork another process to run cmd 2
		pid2 = fork();
		if (pid2 == 0) { 
			// Child2 process reads from pipe
			close( pipefd[1] ) ; 	// close unused write end
			dup2( pipefd[0], 0) ;

			// execute cmd2
			if (execvp(*cmd2, cmd2) < 0) {
				printf("Error: Command 2 execution failed\n");
			}
		} else { 

			close( pipefd[0] ) ; 	// close unused read end
			dup2( pipefd[1], 1) ;

			// execute cmd1
			if (execvp(*cmd1, cmd1) < 0) {
				printf("Error: Command 1 execution failed\n");
			}

			// Child 1 waits for child 2
			wait(NULL);
		}
	} else { 
		// Parent waits for child 1
		wait(NULL);
	}
}
