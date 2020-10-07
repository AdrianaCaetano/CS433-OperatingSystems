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

#include "Support.h"


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

// Take a string as input to pase it
// @return command array
char* support::get_input(void) {
        string*  input;
	
	do { 
        	//Test if command is empty
		cin >> input;
	        cout << "No input detected. Please input again.\n";

        } while (input == NULL);

	return *input;
}

	
string* split_command(string* input) {
	vector <string>* cmd;	
        string* parsed;
        int index = 0;
  
        parsed = strtok(input, " ");
        while (parsed != NULL) {
                cmd.push_back(*parsed);
                index++;

                parsed = strtok(NULL, " ");
        }

        cmd[index] = NULL; // last element is null
        return cmd;
}
		
	int execute(char* cmd) {
}

