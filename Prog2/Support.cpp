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

#define MAX_LINE 80 /* The max length command */
#define BUFFER_SIZE 100 
using namespace std;

char support::last_cmd[41][BUFFER_SIZE]; /* hold history command */
int support::last_command_size = 0;  /*Hold size of last command */

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
	
} // end of split_command


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
		run = 0; // change flag to stop running
		return run;
	}

	if (strcmp(cmd[0], "history") == 0) {
	  printf("Attempting to print history:\n");
//	  show_history(last_cmd, last_command_size);
//	  save_into_history(last_cmd, cmd, last_command_size);
//	  return run;
        }


	if (strcmp(cmd[0], "!!") == 0) {
		printf("Execute previous command\n");
		//cmd = previous
//		run = support::execute(cmd, concurrent);
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
			support::separate_commands(cmd, num_arg, separator, cmd1, cmd2);

			// cmd2 = file name				
			if ((cmd1 != NULL) && (cmd2 != NULL)) {
				if (strcmp(cmd[i], "<") == 0) { // Redirect input
					run = support::redirect_input(cmd1, cmd2, concurrent);
				} 
				else if (strcmp(cmd[i], ">") == 0) { // Redirect output
					run = support::redirect_output(cmd1, cmd2, concurrent);
				} 
				else { 
					printf("ERROR: Redirecting failed\n");
				}
			} else {
				printf("ERROR: Parsing commands failed\n");
			}
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
	int status;
	
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
			while(wait(&status) != pid);
		}
	}
	return 1;
}
	
// Separate commands before and after the separator character
void support::separate_commands(char** cmd, int num_arg, int separator, char** cmd1, char** cmd2) {
	cout << "Num_arg = " << num_arg << endl; // DELETE
	cout << "Command 1: " ; // DELETE
	for (int i = 0; i < separator; i++) { 
		cmd1[i] = cmd[i];
		cout << cmd1[i] << " position: " << i << "; " ;// DELETE
	}
	
	// DELETE
	cout << "\nSeparator charater: " << cmd[separator] << " Separator position: " << separator << endl;

	cout << "\nCommand 2: "; // DELETE
	int index = 0;
/*	for (int i = separator + 1; i < num_arg; i++) { 
		cout << "index= " << index << "; i= " << i ; 
		cmd2[index] = cmd[i];
		cout << cmd2[index] << " position: " << i << "; "; // DELETE
		index++;
	}
*/	
	int i = separator + 1;
	cout << "index= " << index << "; position i= " << i << endl;  // DELETE
	while ( i < num_arg) {  
		cmd2[index] = cmd[i];
		cout << cmd2[index] << " position: " << i << "; "; // DELETE
		index++;
		i++;
	}
	cmd1[separator] = NULL; // last element is null
	cmd2[index] = NULL; 	// last element is null
}



/****************************************************
 * PART III
 * Creating a history feature
 * Execute the most recent command by entering !!
 ****************************************************/

void support::show_history(char history[41][100], int size) {
/*  
  int historyCount = size;
  
  if(historyCount == 0)
    {
      printf("%s ", "Empty history");
      printf("\n");
    }
  else
    {
    for (int i = 0, j = 0; i<10;i++)
    {	
      printf("%d.  ", historyCount);
      while (history[i][j] != '\n' && history[i][j] != '\0')
	{
	  printf("%c", history[i][j]);
	  j++;
	}
      printf("\n");
      j = 0;
      historyCount--;
      if (historyCount ==  0)
	{
	  break;
	}
    }
    } // end of else statement 
*/
}

void support::save_into_history(char history[41][100], char** cmd, int size)
{
/* for(int historyIndex = 40; historyIndex > 0; historyIndex--)
    {
      strcpy(history[historyIndex], history[historyIndex-1]);
    }

   //The lines below give a null-terminated const char* for every character
   //string sym(1, **cmd);
   //cmd = sym.c_str();

  //strcpy(history[0], cmd);
  //size++;
*/
}

char** support::return_last_command(char history[41][100])
{
/* 
  //return *history[0].c_str();
  //return history[0];

  char** pointerChar;
  return pointerChar;
*/
}

/***************************************
 * PART IV
 * Redirecting Input and Output
 * Support < and > redirect commands
 ***************************************/

// Redirect file to be the command input
int support::redirect_input(char** cmd1, char** file, bool concurrent) {
	int fd_in;	// input file descriptor 
	int run = 1;	// flag to keep in the loop

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
	run = support::execute(cmd1, concurrent); // execute command in child process

	close(fd_in);
	return run;
}

// Redirect command output to a file
int support::redirect_output(char** cmd1, char** file, bool concurrent) {
	int fd_out; 	// output file descriptor
	int run = 1; // flag to keep in the loop

	// open file write only, create file with user/group write/read permission
	fd_out = open(file[0], O_WRONLY | O_CREAT, S_IWUSR | S_IWGRP | S_IRUSR | S_IRGRP);

	if (fd_out < 0) { 
		printf("ERROR: Cannot open this file\n");
		return run;
	}

	// Replace standad output with output file
	if (dup2(fd_out, 1) < 0) {
		printf("ERROR: Unable to duplicate fiel descriptor");
		return run;
	}
	run = support::execute(cmd1, concurrent); // execute command

	close(fd_out);
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
	
	// 1 CHILD PROCESS AND PARENT ALSO RUNS COMMAND
	if (pipe(pipefd) < 0) { 
		printf("ERROR: Pipe failed\n");
		return;
	}
	if (pid1 < 0) { 
		printf("ERROR: Fork failed\n");
	}
	if (pid1 == 0) {	
		// Child process
		sleep(0.1); // sleep for one milisecond to wait for parent process to finish

		// Child process reads from pipe 
		close( pipefd[1] ) ; 	// close unused write end
		dup2( pipefd[0], 0) ;
		
		if (execvp(*cmd2, cmd2) < 0) { // executes second command
			printf("Error: Command 2 execution failed\n");
		}
	} else { 
		// Parent process writes to pipe
		close( pipefd[0] ) ; 	// close unused read end
		dup2( pipefd[1], 1) ;
	
		if (execvp(*cmd1, cmd1) < 0) { // ecevutes first command
			printf("ERROR: Command 1 execution failed\n");
		}
	}

/*	2 CHILD PROCESSES (ONE FOR EACH COMMAND) WHILE PARENT WAITS
 
 	pid_t pid2 = fork(); 	//child 2

	if (pipe(pipefd) == -1) {
		printf("ERROR: Pipe failed\n");
		return;
	}

	if ((pid1 < 0) || (pid2 < 0)) { 
		printf("ERROR: Fork failed\n");
		return;		
	}

	if (pid1  == 0) { 
		sleep(0.1); // sleep for one milisecond to wait for process 2 to finish

		// Child process 1 reads from pipe 
		close( pipefd[1] ) ; 	// close unused write end
		dup2( pipefd[0], 0) ;
		
		if (execvp(*cmd2, cmd2) < 0) { // executes second command
			printf("Error: Command 2 execution failed\n");
		}
	} 
	else if ( pid2 == 0) {
		// Child process 2 writes to pipe
		close( pipefd[0] ) ; 	// close unused read end
		dup2( pipefd[1], 1) ;
	
		if (execvp(*cmd1, cmd1) < 0) { // ecevutes first command
			printf("ERROR: Command 1 execution failed\n");
		}
	} 
	else { 
		// Parent process
		waitpid(pid1, NULL, 0); 	// wait for child 1
		waitpid(pid2, NULL, 0); 	// wait for child 2
	}
*/ 

}

