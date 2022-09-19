
#ifndef FIFO_H
#define FIFO_H

const int FIFO_SIZE = 5;

class Fifo
{
public:
    Fifo();
    int get();
    void put(int item);
    bool is_empty();
    bool is_full();
    void reset();

private:
    int buffer[FIFO_SIZE];
    int* head;
    int* tail;
    int* incr_p(int* p); // for incrementing the pointers
    bool it_is_empty;
    // add variables pointing to the front and back of the buffer
};

#endif // FIFO_H
