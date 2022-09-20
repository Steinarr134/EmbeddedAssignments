#include "fifo2.h"

Fifo::Fifo()
{
    reset();
}

int Fifo::get()
{
    // get shouldn't be called on an empty queue but:
    if (is_empty())
    {
        return -1;
    }
    
    int ret = buffer[0]; // get the return item

    // move evrything down by one seat
    for (int i = 1; i<count; i++)
    {
        buffer[i-1] = buffer[i];
    }
    count--; // there will be one fewer items in the queue now
    return ret;
}

void Fifo::put(int item)
{  
    if (is_full())
    {
        get(); // throw one out to make room
        put(item); //recursive for the win!
        return;
    }
    // put the item in the queue and then increment count
    buffer[count++] = item;
}

bool Fifo::is_empty()
{
    return count == 0;
}

bool Fifo::is_full()
{
    return count==FIFO_SIZE;
}

void Fifo::reset()
{
    count = 0;
}
