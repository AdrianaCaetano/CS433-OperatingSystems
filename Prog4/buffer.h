/*
 * Programming Assignment 4 - CS 433
 * Description: Producer-Consumer Problem
 * Author: Adriana Caetano & Ryan Pisuena
 * Date: 11/25/2020
 * File: buffer.h
 */

#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 5
   
typedef int buffer_item;

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


#endif

