/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.cpp
 */

#include <cstring>	//strcmp(), strtok()
 #include <iostream>	// exit(), cout
#include <sys/wait.h>	// wait()
#include <unistd.h>	// fork(), execvp()


#include "Support.h"

#define MAX_LINE 80 /* The max length command */
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
	
} // end of split_command


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

	if (cmd == NULL) { exit(0); }
	if (strcmp(cmd[0], "exit") == 0) { 
	  printf("Good bye!\n");
	  run = 0; // change flag to stop running
	  return run;
	}
	
	
	if (strcmp(cmd[0], "!!") == 0) {
	  
	  if(last_cmd[0] == NULL)
	    {
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
	  }
	  
	  if (strcmp(cmd[i], "|") == 0) {// Create pipe
	    separator = i; // position of |
	    support::separate_commands(cmd, num_arg, separator, cmd1, cmd2);
	    
	    if ((cmd1 != NULL) && (cmd2 != NULL)) {
	      // Create the pipe
	      support::pipe_cmd(cmd1, cmd2);
	    } else {
	      printf("Parsing commands failed\n");
	    }
	    return run;
	  }
	  
	  if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], ">>") == 0) {
	    printf("Output redirection\n");
	    separator = i; // position of >
	    support::separate_commands(cmd, num_arg, separator, cmd1, cmd2);
	  }
	  
	  if (strcmp(cmd[i], "<") == 0 || strcmp(cmd[i], "<<") == 0) { 
	    printf("Input redirection\n"); 
	    separator = i; // position of <
	    support::separate_commands(cmd, num_arg, separator, cmd1, cmd2);
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
  
  for (int j = 0; j < separator; j++) { 
    cmd1[j] = cmd[j];
  }
  
  int index = 0;
  for (int j = separator + 1; j < num_arg; j++) { 
    cmd2[index] = cmd[j];
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

// TODO
void support::show_history()
  
{
  cout << support::last_cmd << endl;
  /*
  //cout << "show_history is causing the loop" << endl;
  int historyCount = last_command_size;
  
  if(historyCount == 0)
  {
  printf("%s ", "Empty history");
  printf("\n");
  }
  else
  {
  for(int i = 0; i < 80; i++)
  {
  printf("%d.  ", historyCount);
  while (last_cmd != '\n' && last_cmd != '\0')
  {
  printf("%c", support::last_cmd[i]);
  //j++;
  }
  printf("\n");
  historyCount--;
  if (historyCount ==  0)
  {
  break;
  }
  
  }
  
  
  }// end of else statement
  */
  
  /*
    else
    {
    for (int i = 0, j = 0; i<41;i++)
    {
    printf("%d.  ", historyCount);
    while (support::last_cmd[i][j] != '\n' && support::last_cmd[i][j] != '\0')
    {
    printf("%c", support::last_cmd[i][j]);
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
/*
void support::save_into_history(char * input)
{
  //for(int historyIndex = 80; historyIndex > 0; historyIndex--)
  //{
  //strcpy(&support::last_cmd[historyIndex],&support::last_cmd[historyIndex-1]);
  //}
  
  //The lines below give a null-terminated const char* for every character
  //string sym(1, cmd);
  //sym.c_str();
  
  //cout << "Bug identified: " << endl;
  cout << input << endl;
  strcpy(support::last_cmd, input); // <-- bug is here
  
  //cout << last_cmd[0][0] << endl; // outs for testing
  //cout << &cmd << endl; // outs for testing
  //cout << cmd << endl; // outs for testing
  
  support::last_command_size++;
}
*/

int support::get_last_command(char * last_cmd, char ** cmd)
{
  
  int numCommands = split_command(last_cmd, cmd);
  return numCommands;
  
}

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


// Creates a pipe to send output of cmd 1 to input of cmd 2
void support::pipe_cmd(char** cmd1, char** cmd2) {
  int pipefd[2]; 		// file descriptors
  pid_t pid1 = fork(); 	// child 1
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
    close( pipefd[0] ) ;
  } 
  else if ( pid2 == 0) {
    // Child process 2 writes to pipe
    close( pipefd[0] ) ; 	// close unused read end
    dup2( pipefd[1], 1) ;
    
    if (execvp(*cmd1, cmd1) < 0) { // ecevutes first command
      printf("ERROR: Command 1 execution failed\n");
    }
    close( pipefd[1] ) ; 	// reader will see EOF	
  } 
  else { 
    // Parent process
    waitpid(pid1, NULL, 0); 	// wait for child 1
    waitpid(pid2, NULL, 0); 	// wait for child 2
  }
}


// TODO
