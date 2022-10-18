#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include <signal.h>
#include <stdint.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}



int main(){

    signal(SIGINT, intHandler);
   int fd, count;

   // Remove O_NDELAY to *wait* on serial read (blocking read)
   if ((fd= open("/dev/ttyS0", O_RDONLY | O_NOCTTY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;       // the termios structure is vital
   tcgetattr(fd, &options);    // sets the parameters for the file

    cfmakeraw(&options); // set as raw

   // 57600 baud, 8-N-1, enable receiver, no modem control lines
   options.c_cflag |= B57600 | CS8 | CREAD | CLOCAL;
   
   tcflush(fd, TCIFLUSH);            // discard file information
   tcsetattr(fd, TCSANOW, &options); // changes occur immmediately
    
    uint32_t counter = 0;
    while (keepRunning)
    {

        if ((count = read(fd, &counter, 4))<0){   //receive data
            perror("Failed to read from the input\n");
            return count;
        }

        if (count==0){} // printf("There was no data available to read!\n");
        
        else printf("%d\n", counter);
    }

   close(fd);

   return 0;
}


