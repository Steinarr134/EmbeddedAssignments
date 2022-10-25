/* Simple send and receive C example (line-mode terminal program with local echo) 
* for communicating with the Arduino using /dev/ttyS0. */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
   int file, count;

   if(argc!=3){
       printf("Invalid number of arguments, exiting!\n");
       return -2;
   }

   if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;

   tcgetattr(file, &options);

   cfmakeraw(&options);
   options.c_cflag |= B115200 | CS8 | CREAD | CLOCAL;
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);

   // send the string plus the null character
    const size_t MSG_LEN = 2;
   uint8_t msg[MSG_LEN];

   // populate the message with integer values in binary format
   msg[0] = atoi(argv[1]);
   msg[1] = atoi(argv[2]);

   if (count = write(file, msg, 2)<0){
      perror("Failed to write to the output\n");
      return -1;
   }

   printf("Successfully sent %i, %i\n", msg[0], msg[1]);

   close(file);
   return 0;
}
