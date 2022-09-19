#include "fifo3.h"

Fifo::Fifo()
{
    reset();
}

int* Fifo::incr_p(int* p){
    if (p + 1 == &buffer[0] + FIFO_SIZE)
        return &buffer[0];
    else
        return p+1;
}

int Fifo::get()
{
    if (is_empty())
    {
        return -1;
    }
    int ret = *head;
    head = incr_p(head);
    if (head == tail) it_is_empty = true;
    return ret;
}

void Fifo::put(int item)
{  
    if (is_full())
    {
        get();// throw one out to make room
        this->put(item); //recursive for the win!
        return;
    }
    *tail = item;
    tail = incr_p(tail);
    it_is_empty = false;
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