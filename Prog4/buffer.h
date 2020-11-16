/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: buffer.h
 */

#ifndef BUFFER_H
#define BUFFER_H

typedef int buffer_item;
#define BUFFER_SIZE 5

#include <vector>

class Buffer
{
 
private:
   // buffer items
    std::vector<buffer_item> buffer;

public:
    // constructor
    Buffer();

    // Destructor
    ~Buffer();

    // Show buffer items
    void show_content();

    /* Insert item into buffer
     * return 0 if sucessful, otherwise
     * return -1 indicating an error condition
     */
    int insert_item(buffer_item item);

    /* Remove item from buffer
     * placing it in item
     * return 0 if sucessful, otherwise
     * return -1 indicating an error condition
     */
     int remove_item(buffer_item* item);

     void* producer(void *param);

     void* consumer(void *param);

};

#endif

