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

class Buffer
{
    private:
        // buffer array with 5 buffer items
        buffer_item buffer[BUFFER_SIZE];

    public:
        // Constructor
        Buffer();

        // Destructor
        ~Buffer();

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
        int remove_item(buffer_item item);
};

#endif

