/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: main.cpp
 */

#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <typeinfo>

#include "Support.h"

#define MAX_LINE 80 /* The max length command */

using namespace std;
using namespace support;

int main(void) {

        char* input;
        char** cmd[MAX_LINE/2 + 1]; /* command line arguments */
	int should_run = 1; /* flag to determine when to exit the program */

        show_header();
	cout << "This program simulates a shell.\n" ;
	cout << "Please input your command.\n\n";

	do {

		printf("osh->");
		fflush(stdout);

                // parse command line. Get command, args, redirect
		input = get_input();
		cmd = split_command(*input);
		should_run = execute_command(cmd);

		free(input);
		free(cmd);

	} while (should_run);

        cout << "---------- End of Program ----------\n";

        return 0;
}
