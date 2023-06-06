#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
int pipe_pair[2];
int test1() {
    printf("test1 start:\n");

    const char* tmp = "from test1\n";
    write(pipe_pair[1], tmp, strlen(tmp));
    printf("test1 end:\n");

    return 0;
}

int test2() {
    printf("test2 start:\n");

    char tmp[4096] = {0};
    int tmpLen = 0;
    tmpLen = read(pipe_pair[0], tmp, 4096);
    printf("read buf:%s\n", tmp);
    printf("test2 end\n");
    return 0;
}

int main() {
    int ret = 0;
    ret = pipe(pipe_pair);
    if(ret != 0) {
        printf("pipe err\n");
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

    return 0;
}