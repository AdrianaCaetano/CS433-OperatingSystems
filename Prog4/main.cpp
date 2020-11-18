/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: main.cpp
 */

#include <pthread.h>
#include <semaphore.h>

#include <iostream>
#include <unistd.h> 

#include "buffer.h"
#include "functions.h"

// Global Functions declaration
void* produce(void* parameter);
void* consume(void* parameter); 

// Semaphores and mutex for synchronization    
sem_t full;
sem_t empty;
pthread_mutex_t mutex; 

int main(int argc, char* argv[])
{
    Functions::show_header();

    // 1. Get command line arguments argv[1], argv[2], argv[3]
    // *****************************************************************
    // Parameters struct to hold argument's values
    Parameters p = Functions::get_parameters(argc, argv);

    printf("[# seconds] = %d\n", p.sleep_time);
    printf("[# producers] = %d\n", p.num_producers);
    printf("[# consumers] = %d\n", p.num_consumers);

    // initialize random seed
    srand(time(NULL));

    // 2. Initialize buffer
    // *****************************************************************
    show_content();

    // 3. Create producer thread(s)
    // *****************************************************************

    // initialize semaphores and mutex
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // array of producer's threads
    pthread_t producers[p.num_producers];
    
    printf("Creating producer threads "); 
 
    for (int i = 0; i < p.num_producers; i++)
    {
        // create the threads
        printf("p%d ", i);
        pthread_create(&producers[i], NULL, produce, NULL);
    }
    printf("\n");


    // 4. Create consumer thread(s)
    // *****************************************************************

    // array of consumer's threads
    pthread_t consumers[p.num_consumers];

    printf("Creating consumer threads ");
 
    for (int i = 0; i < p.num_consumers; i++) 
    {
        // create the thread
        printf("c%d ", i);
        pthread_create(&consumers[i], NULL, consume, NULL);
    }
    printf("\n\n");
    
    // *****************************************************************
    // Join with terminated threads

    for (int i = 0; i < p.num_producers; i++)
    {
        pthread_join(producers[i], NULL);
    }

    for (int i = 0; i < p.num_consumers; i++) 
    {
        pthread_join(consumers[i], NULL);
    }
    
    // 5. Sleep
    // *****************************************************************
    sleep(p.sleep_time);

    // 6. Exit
    // *****************************************************************
    exit(0);

    return 0;
}


// Global functions declaration
// *********************************************************************

// PThread will produce item
void* produce(void* param) 
{
    buffer_item item;

    while (true) 
    {
        // sleep for a random period of time 
        usleep(rand()%100000); // sleep up to 1 second

        // generate a random number 
        item = rand() % 100;

        // wait for semaphore and acquire lock
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex);

        if (insert_item(item))
        {  
             std::cerr << "ERROR: Unable to insert item " << item << ".\n";
        }
        else
        {
            printf("Item %d inserted by a producer.\n",item);
            show_content();
        }

        // release lock and signal semaphore
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    } 
    pthread_exit(0);
}  

// PThread will consume item  
void* consume(void* param) 
{
    buffer_item item;

    while (true) 
    {
        // sleep for a random period of time 
        usleep(rand()%1000000); // sleep thread 

        // wait for semaphore and acquire lock
        sem_wait(&full); 
        pthread_mutex_lock(&mutex);

        if (remove_item(&item))
        {
             std::cerr << "ERROR: unable to remove item " << &item << ".\n";
        }
        else
        {
            printf("Item %d removed by a consumer.\n",item);
            show_content();
        }

        // release lock and signal semaphore
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    pthread_exit(0);
}

