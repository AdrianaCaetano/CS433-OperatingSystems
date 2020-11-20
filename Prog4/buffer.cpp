/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: buffer.cpp
 */

#include <iostream>
#include <queue>

#include "buffer.h"

//int in = 0;
//int out = 0;

// Buffer container of buffer items
std::queue <buffer_item> buffer;

// Show content
void show_content()
{
    printf("The current content of the buffer is [ ");
    std::queue <buffer_item> temp_buffer = buffer;
    while (temp_buffer.empty() == false)
    {    
        printf("%d ", temp_buffer.front()); 
        temp_buffer.pop();
    }
    printf("]\n\n");
}

/* Insert item into buffer
 * return 0 if sucessful, otherwise
 * return -1 indicating an error condition
 */
int insert_item(buffer_item item)
{
    //check if there is space
    if (buffer.size() < BUFFER_SIZE)
    { 
        buffer.push(item);		//insert item
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
int remove_item(buffer_item* item)
{
    // check if there is an item
    if (buffer.empty() == false) 
    {
        *item = buffer.front();    		// get item 
        buffer.pop();       	//remove item
    }
    else 
    { 
        return -1; // error
    }
    return 0;
}
