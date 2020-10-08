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
#include <typeinfo>

#include "Support.h"

#define MAX_LINE 80 /* The max length command */

using namespace support;

int main(void) {

        char* input;
        char** cmd[MAX_LINE/2 + 1]; /* command line arguments */
	bool should_run = true; /* flag to determine when to exit the program */

        show_header();
	std::cout << "This program simulates a shell.\n" ;
	std::cout << "Please input your command.\n" << std::endl;

	std::cout << "input type: " << typeid(input).name();
	printf("\n");
	std::cout << "cmd type: " << (typeid(cmd).name();
	printf("\n\n");

	do {

		printf("osh->");
		fflush(stdout);

                // parse command line. Get command, args, redirect
		input = get_input();
//		cmd = split_command(input);
//		should_run = execute(cmd);

		free(input);
		free(cmd);

	} while (should_run);

        std::cout << "---------- End of Program ----------" <<std::endl;

        return 0;
}
