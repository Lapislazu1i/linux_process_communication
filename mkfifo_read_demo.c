#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE_PATH "testfifo"
#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
    int fd;
    char buf[BUF_SIZE];


    fd = open(FIFO_FILE_PATH, O_RDONLY);
    
    read(fd, buf, BUF_SIZE);

    printf("%s\n", buf);

    close(fd);

    return 0;    
}