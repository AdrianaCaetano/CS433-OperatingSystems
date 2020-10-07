/*
 * Programming Assignment 2 - CS 433
 * Description: Unix Shell and History Feature
 * Author: Adriana Caetano and Ryan Pisuena
 * Date: 10/14/2020
 * File: Support.h
 */

#ifndef SUPPORT_H
#define SUPPORT_H

namespace support {

        // Show header with basic information about this program
        void show_header();

        // Take a string as input and parse it
        // @return array of commands
        char **get_input(char *input);
}

#endif
