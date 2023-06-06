#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE_PATH "testfifo"

int main(int argc, char* argv[])
{
    int fd;
    char buf[]  = "from write";

    mkfifo(FIFO_FILE_PATH, S_IFIFO|0666);

    fd = open(FIFO_FILE_PATH, O_WRONLY);
    
    write(fd, buf, strlen(buf)+1);

    close(fd);
    unlink(FIFO_FILE_PATH);//删除管道文件

    sleep(1);
    return 0;    
}