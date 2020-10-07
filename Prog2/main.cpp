/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: main.cpp
 */

#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "Support.h"

#define MAX_LINE 80 /* The max length command */

using namespace support;

int main(void) {
        show_header();

        char* input;
        char* cmd; /* command line arguments */
        pid_t child_pid;
        int should_run; /* flag to determine when to exit the program */

	std::cout << "This program simulates a shell.\n" 
		  << "Please input your command." << std::endl;

	do {

		printf("osh>>");
		input = get_input();
		cmd = split_command(input);
		should_run = execute(cmd);

		free(input);
		free(cmd);
	} while (should_run);


/*       while (should_run) {
                printf("osh> ");
                fflush(stdout);

                // parse command line. Get command, args, redirect

                // if (cmd == exit) exit();

                /*
                 * After reading user input, the steps are:
                 * (1) fork a child process using fork()
                 * (2) the child process will invoke execvp()
                 * (3) parent will invoke wait() unless command included &
                 */
         /*
                p = fork();
                if (p == 0) {
                        execvp (cmd, args);
                } else {
                        if (cmd does not end with &) {
                                wait();
                }
        }
*/


        std::cout << "---------- End of Program ----------" <<std::endl;

        return 0;
}
