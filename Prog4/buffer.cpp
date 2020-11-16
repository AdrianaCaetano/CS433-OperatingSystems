/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: buffer.cpp
 */

#include <cstdio>   /* printf */
#include <iostream>
#include <stdlib.h> /* rand() */
#include <unistd.h> /* sleep() */ 

#include "buffer.h"

// Constructor
Buffer::Buffer() {}

// Destructor
Buffer::~Buffer() {}

// Show content
void Buffer::show_content()
{
    printf("The current content of the buffer is [");
    for (auto i : this->buffer)
    {
        if (i != this->buffer.back())
        {
            printf("%d, ", i); 
        }
        else 
        { 
            printf("%d", i);
        }
    }
    printf("]\n\n");
}

/* Insert item into buffer
 * return 0 if sucessful, otherwise
 * return -1 indicating an error condition
 */
int Buffer::insert_item(buffer_item item)
{
    //check if there is space
    if (this->buffer.size() < BUFFER_SIZE)
    { 
        //insert item
        this->buffer.push_back(item);
    }
    else 
    {
       return -1; //error condition
    }
    return 0;
}


/* Remove item from buffer
 * placing it in item
 * return 0 if sucessful, otherwise
 * return -1 indicating an error condition
 */
int Buffer::remove_item(buffer_item* item)
{
    // check if there is an item
    if (this->buffer.empty() == false) 
    {
        // remove item from the front (FIFO)
        this->buffer.erase(this->buffer.begin());
    }
    else 
    { 
        return -1; // error
    }
    return 0;
}

// PThread will produce item
void* Buffer::producer(void* param) 
{
    buffer_item item;

    while (true) 
    {
        /* sleep for a random period of time */
        sleep(rand()%10+1); // sleep beytween 1 to 10 seconds

        /* generate a random number */
        item = rand();

        if (Buffer::insert_item(item))
        {  
             std::cerr << "ERROR: Unable to insert item " << item << ".\n";
        }
        else
        {
            printf("Item %d inserted by a producer.\n",item);
            Buffer::show_content();
        }
    }
}  


// PThread will consume item  
void* Buffer::consumer(void* param) 
{
    buffer_item item;

    while (true) 
    {
        /* sleep for a random period of time */
        sleep(rand()%10+1); // sleep between 1 to 10 seconds

        if (Buffer::remove_item(&item))
        {
             std::cerr << "ERROR: unable to remove item " << &item << ".\n";
        }
        else
        {
            printf("Item %d removed by a consumer.\n",item);
            Buffer::show_content();
        }
    }
}
  
