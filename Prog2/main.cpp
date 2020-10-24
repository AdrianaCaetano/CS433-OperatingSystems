  
/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: main.cpp
 */


#include <cstdio>  	// printf(), fflush(), fgets()
#include <cstring>	// strcpy()
#include <string.h>	// strcmp()
#include <iostream>

#include "Support.h"

#define MAX_LINE 80 	/* The max input length */

using namespace std;
using namespace support;



// main function used to faciliate running functions that simulate a UNIX shell
int main(void) {
  
  char input[MAX_LINE];           /* user input */
  char* commands[MAX_LINE/2 + 1]; /* command line arguments */
  char last_cmd[MAX_LINE]; 	    /* hold history command */
  int num_args = 0;               /* hold number of command arguments */
  int should_run = 1;             /* flag to determine when to exit the program */
  
  show_header(); // show_header is used to showcase information about the program

  // The times lines below prompt the user to enter a shell command
  printf("This program simulates a shell.\n") ;
  printf("Please input your command.\n\n") ;
  
  // while the program is running
  while(should_run) {
    
    printf("osh->");
    fflush(stdout);
    
    // get input
    fgets(input, MAX_LINE, stdin);
    
    // Check input before parsing the command
    if (strcmp(input, "\0") == 0) 
      { 
	continue; 
      }
    
    // If the input is equal to exit, exit the program
    if (strncmp(input, "exit", 4) == 0) 
      {
	printf("Good bye!\n");
	break;
      }
    //save or retrieve last command
    if (strncmp(input, "!!", 2 ) == 0) 
      { 
	if (strlen(last_cmd) == 0) 
	  { 
	    printf("No previous command in history\n");
	    continue;
	  } 
	else // run the command contained in last command
	  {
	    // input = last_cmd
	    strcpy(input, last_cmd);
	  }
      } 
    else // Store the entered command into the last command
      {
	//last_cmd = input	
	strcpy(last_cmd, input);
      }
    
    // parse command
    num_args = split_command(input, commands);
    
    if (num_args != 0) 	
      { 	
	// execute command
	should_run = execute_command(commands, num_args);
      }	
  }
  
  printf("---------- End of Program ----------\n");
  
  return 0;
  
}
