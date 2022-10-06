#include<fcntl.h>
#include<unistd.h>
#include <stdio.h>

int main(){
    int fd = open("/dev/mydev1", O_RDWR);
    int count = 0;
    int max_count = 25;
    char buffer[30] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
    while (1){
        count = (count % max_count) + 1;
        write(fd, buffer, count);
        sleep(1);
    }
}