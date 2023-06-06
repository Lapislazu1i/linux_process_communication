#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#define PIPE_FILE_PATH "./pipe.txt"


int test1() {
    printf("test1 start:\n");

    const char* tmp = "from test1\n";

    int fd = 0;
    fd = open(PIPE_FILE_PATH, O_WRONLY);
    if(fd == -1) {
        printf("open err\n");
        return -1;
    }
    write(fd, tmp, strlen(tmp));

    printf("test1 end:\n");
    close(fd);
    return 0;
}

int test2() {
    printf("test2 start:\n");


    char buf[1024] = {0};
    int fd = 0;
    fd = open(PIPE_FILE_PATH, O_RDONLY);
    if(fd == -1) {
        printf("open err\n");
        return -1;
    }
    read(fd, buf, 1024);
    printf("read buf:%s\n", buf);

    printf("test2 end\n");
    return 0;
}

int main() {
    int ret = 0;
    ret = mkfifo(PIPE_FILE_PATH, S_IFIFO | 0666);
    if(ret != 0) {
        printf("mkfifo err:%d\n", ret);
        return -1;
    }

    int status;
    int pc;

    pid_t id = fork();
    printf("pid:%d\n", id);
    if(id == 0) {
        sleep(1);
        test2();
    } else if(id > 0) {
        test1();
        pc=wait(&status);
        printf("status:%d\n", status);
        if(WIFEXITED(status))
        { 
            printf("我是父进程,我等待的子进程的id号=%d\n",pc); 
            printf("退出码是%d\n",WEXITSTATUS(status)); 
        } 

    } else {
        printf("fork err\b");
        return -1;
    }
    unlink(PIPE_FILE_PATH);//删除管道文件
    return 0;
}