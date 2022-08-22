#include <stdint.h> // Defines integer types of a particular size

////////   PART 1   ///////////
// default int:
// int a[1000];  // 97.7% (used 2000 bytes from 2048 bytes)

// 8 bit int: 
// uint8_t a[1000]; // 48.8% (used 1000 bytes from 2048 bytes)

// 16 bit int:
// uint16_t a[1000];  // 97.7% (used 2000 bytes from 2048 bytes)

// 32 bit int:
// uint32_t a[1000];  // 195.3 % (used 4000 bytes from 2048 bytes)

// 64 bit int:
// uint64_t a[1000]; // 390.6% (used 8000 bytes from 2048 bytes)

///////   PART 2   /////////////////
// global
// int a[10000];

// global constant
// const int a[10000];

int main()
{
  // local 
  // int a[1000];

  // local static
  // static int a[1000];

  // local constant
  // const int a[1000];

  // dynamic variable
  int *a = new int[1000];
  // int *b = new int[1000];
  // int *c = new int[1000];
  // int *d = new int[1000];

  return a[0] ;  //  + b[0] + c[0] + d[0];
}