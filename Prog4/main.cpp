/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: main.cpp
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "functions.h"

int main(int argc, char* argv[])
{
    Functions::show_header();

    // 1. Get command line arguments argv[1], argv[2], argv[3]
    Parameters p = Functions::get_parameters(argc, argv);

    printf("[# seconds] = %d\n", p.sleep_time);
    printf("[# producers] = %d\n", p.num_producers);
    printf("[# consumers] = %d\n", p.num_consumers);


    // 2. Initialize buffer
    Buffer buffer;
    buffer.show_content();

/*
 *
    // 3. Create producer thread(s)
    pthread_t tid; 		// thread identifier 
    pthread_attr_t attr; 	// set of attributes 

    // set the default attributes of the thread (using default provided)
    pthread_attr_init(&attr);

    // create the thread
    pthread_create(&tid, &attr, Buffer::producer, p.sleep_time);

    // wait for the thread to exit
    pthread_join(tid, NULL);



    // 4. Create consumer thread(s)


    // 5. Sleep


    // 6. Exit
    pthread_exit(0);
*/
    return 0;
}
