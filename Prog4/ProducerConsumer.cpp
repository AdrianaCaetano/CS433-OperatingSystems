#include <stdlib.h> /* required for rand() */
#include "buffer.h"
#include "ProducerConsumer.h"

void *producer(void *param) 
{
  Buffer::buffer_item item;
  while (true) {
    /* sleep for a random period of time */
    sleep(rand()%10+1); // sleep beytween 1 to 10 seconds
    /* generate a random number */
    item = rand();
    if (Buffer::insert_item(item))
      fprintf("report error condition");
    else
      printf("producer produced %d∖n",item);
  }
  
  
void *consumer(void *param) 
{
  Buffer::buffer_item item;
  while (true) {
    /* sleep for a random period of time */
    sleep(rand()%10+1); // sleep between 1 to 10 seconds
    if (Buffer::remove_item(&item))
      fprintf("report error condition");
    else
      printf("consumer consumed %d∖n",item);
  }
  
