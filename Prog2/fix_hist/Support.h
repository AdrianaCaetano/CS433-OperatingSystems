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

    // Parse the input to get commands
    int split_command(char* input, char** cmd);

    // Check command to execute
    int execute_command(char** cmd, int num_arg, char* last_cmd);

    // Execute command in a child process
    int execute(char** cmd, bool concurrent);

    // Separate commands before and after the separator character
    void separate_commands(char** cmd, int num_arg, int separator, char** cmd1, char** cmd2);

    // Returns the last command used
    int get_last_command(char* last_cmd, char** cmd);

    // redirect input/output
    int redirect(char** cmd, int num_arg, int separator); 

    // Create a pipe and send output of cmd1 to input of cmd2
    void pipe_cmd(char** cmd1, char** cmd2);

}
#endif
