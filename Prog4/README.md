# Producer-Consumer Problem (100 points)

Implement programming project 4 "The Producer-Consumer Problem" in chapter 7 of the textbook
(P43 to P45 of eTextbook)1. You should solve the producer-consumer problem using the Pthreads
API. Your program should allow creating multiple producer and consumer threads. Three
parameters are passed on the command line:

1. How long the main thread sleep before terminating (in seconds)
2. The number of producer threads
3. The number of consumer threads

In order to study the behaviors of concurrent threads, keep track and print out the content of the
shared buffer during the execution of the threads when an item is added or consumed. For example,
print message like:

> item 2 inserted by a producer. The current content of the buffer is [4, 5, 2].

The items should be removed in their order of being added, i.e. FIFO. Make sure the program works
correctly. You need to include <pthread.h> header file and link the pthread library using "-
lpthread".

The producer and consumer threads should sleep for some random time but probably shouldn’t
sleep more than one second. You may use the usleep() function like
“usleep(rand()%1000000);”, where usleep() function sleeps for some number of
microseconds.

## Extra Credits:
You may gain extra credits for this assignment by doing more work beyond the requirements, for
example implementing the bounded buffer as a monitor using mutex and condition variables or other
things interesting or creative. The extra credit depends on the amount of extra work you do but will
be no more than 10 points. Please clearly describe the additional work you do in the report if you
want to claim extra credits.
