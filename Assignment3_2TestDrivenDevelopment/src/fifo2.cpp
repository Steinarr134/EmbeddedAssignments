#include "fifo2.h"

Fifo::Fifo()
{
    count = 0;
}

int Fifo::get()
{
    if (is_empty())
    {
        return -1;
    }
    
    int ret = buffer[0];
    for (int i = 1; i<count; i++)
    {
        buffer[i-1] = buffer[i];
    }
    count--;
    return ret;
}

void Fifo::put(int item)
{  
    if (is_full())
    {
        get();
        // get(); // throw one out to make room
        this->put(item); //recursive for the win!
        return;
    }
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
