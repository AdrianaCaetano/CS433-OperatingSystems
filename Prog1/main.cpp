/*
 * Programming Assignment 1 - CS 433
 * Description: ReadyQueue implementation to control processes and test performance
 * Author: Adriana Caetano
 * Date: 09/23/2020
 * File: main.cpp
 */


#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>

#include "PCB.h"
#include "ReadyQueue.h"

int main(int argc, char* argv[]) {
        //Print basic information about the program
        std::cout << std::endl;
        std::cout << "======================================================================" << std::endl << std::endl;
        std::cout << "CS 433 Programming assignment 1" << std::endl;
        std::cout << "Author: Adriana Caetano" << std::endl;
        std::cout << "Date: 09/23/2020" << std::endl;
        std::cout << "Course: CS433 (Operating Systems)" << std::endl;
        std::cout << "Description : Program to implement a priority ready queue of processes" << std::endl << std::endl;
        std::cout << "======================================================================" << std::endl << std::endl;


        // Code for Test 1
        std::cout << "---------- Performing Test 1 ----------" << std::endl << std::endl;

        std::cout << std::endl;

        // seed time for rand()
        srand(time(NULL));

        //Create a ReadyQueue
        ReadyQueue q1;


        /* Perform test 1
         * Create a ReadyQueue. Add specific processes, remove the highest priority process,
         * and display queue elements after each removal.
         */
        q1.performTest1();
        std::cout << std::endl;

        // Code for Test 2
        std::cout << "---------- Performing Test 2 ----------" << std::endl << std::endl;
        std::cout << std::endl;

        /* Perform test 2
         * Evaluate performance of the ReadyQueue implementation inserting and removing processes.
         * Measure the time to do 1,000,000 iterations and present results.
         */
        q1.performTest2();
        std::cout << std::endl;

        std::cout << "---------- End of Program ----------" <<std::endl;

        return 0;
}
