/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: main.cpp
 */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <typeinfo>

#include "Support.h"

#define MAX_LINE 80 /* The max length command */

using namespace std;
using namespace support;

int main(void) {

        char input[MAX_LINE];
        char* commands[MAX_LINE/2 + 1]; /* command line arguments */
	char* last_cmd[MAX_LINE/2 + 1]; /* hold history command */
	int should_run = 1; /* flag to determine when to exit the program */

        show_header();
	cout << "This program simulates a shell.\n" ;
	cout << "Please input your command.\n\n";

	while(should_run) {
		printf("osh->");
		fflush(stdout);

		// get and parse command
		split_command(input, commands);
	
		should_run = execute_command(commands);
	}

        cout << "---------- End of Program ----------\n";

        return 0;
}
