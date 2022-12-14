
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // using the termios.h library
#include <signal.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}



int main(){

    signal(SIGINT, intHandler);
   int fd, count;

   // Remove O_NDELAY to *wait* on serial read (blocking read)
   if ((fd= open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Failed to open the file.\n");
      return -1;
   }

   struct termios options;       // the termios structure is vital
   tcgetattr(fd, &options);    // sets the parameters for the file

   // Set up the communication options:
   // 57600 baud, 8-N-1, enable receiver, no modem control lines
   options.c_cflag = B57600 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;   // ignore partity errors
   tcflush(fd, TCIFLUSH);            // discard file information
   tcsetattr(fd, TCSANOW, &options); // changes occur immmediately
    
    char *line =NULL;
    size_t len = 0;

    ssize_t lineSize = 0;

    while (keepRunning)
    {
        lineSize = getline(&line, &len, stdin);
        // printf("You entered %s, which has %zu chars.\n", line, lineSize -1);

        if ((count = write(fd, line, lineSize-1))<0){         // transmit
            perror("Failed to write to the output\n");
            return -1;
        }

        usleep(100000);             // give the remote machine a chance to respond

        unsigned char receive[100] = {0}; //declare a buffer for receiving data

        if ((count = read(fd, (void*)receive, 100))<0){   //receive data
            perror("Failed to read from the input\n");
            return count;
        }

        if (count==0) printf("There was no data available to read!\n");
        // else printf("The following was read in [%d]: %s\n",count,receive);
        else printf("%s\n", receive);
    }

   close(fd);

   return 0;
}


