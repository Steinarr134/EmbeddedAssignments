#include "fifo3.h"

Fifo::Fifo()
{
    reset();
}

int* Fifo::incr_p(int* p){
    // this function increments the pointers in the ring buffer
    if (p + 1 == &buffer[0] + FIFO_SIZE)

    // if we're about to exit the buffer
        return &buffer[0]; // return to 0
    else
        return p+1;
}

int Fifo::get()
{
    // get shouldn't be called on an empty queue but:
    if (is_empty())
    {
        return -1;
    }
    
    int ret = *head; // get first item
    head = incr_p(head); // move the head by 1

    // if the queue is now empty:
    if (head == tail) it_is_empty = true; 

    return ret;
}

void Fifo::put(int item)
{  
    if (is_full())
    {
        get();  // throw one out to make room
        put(item); //recursive for the win!
        return;
    }
    *tail = item; // put uten into queue
    tail = incr_p(tail); // increment tail
    it_is_empty = false; // no longer empty
}

bool Fifo::is_empty()
{
    return it_is_empty;
}

bool Fifo::is_full()
{
    return (head == tail && !it_is_empty);
}

void Fifo::reset()
{
    tail = &buffer[0];
    head = &buffer[0];
    it_is_empty = true;
}