/* 
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: ProducerConsumer.cpp
 */

#include <cstdio>
#include <stdlib.h> /* required for rand() */
#include <unistd.h>

#include "buffer.h"
#include "ProducerConsumer.h"

using namespace std;

//typedef int buffer_item; 

void* ProducerConsumer::producer(void *param) 
{
    buffer_item item;

    while (true) 
    {
        /* sleep for a random period of time */
        sleep(rand()%10+1); // sleep beytween 1 to 10 seconds

        /* generate a random number */
        item = rand();
        if (insert_item(item))
        {  
             printf("report error condition");
        }
        else
        {
            printf("producer produced %d∖n",item);
        }
    }
}  
  
void* ProducerConsumer::consumer(void *param) 
{
    buffer_item item;

    while (true) 
    {
        /* sleep for a random period of time */
        sleep(rand()%10+1); // sleep between 1 to 10 seconds
        if (remove_item(&item))
        {
             printf("report error condition");
        }
        else
        {
            printf("consumer consumed %d∖n",item);
        }
    }
}
  
