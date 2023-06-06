#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <signal.h> 

void sign_handle(int sign){
    printf("sign:%d\n", sign);
}
int test1() {
    printf("test1 start:\n");
    signal(SIGUSR1,sign_handle);
    printf("test1 end\n");
    return 0;
}

int test2() {
    pid_t fid = getppid();
    printf("father id:%d\n", fid);
    printf("test2 start:\n");
    printf("fid:%d\n", fid);
    kill(fid, SIGUSR1);
    printf("test2 end\n\n");
    return 0;
}

int main() {
    int status;
    int pc;
    pid_t id = fork();
    printf("pid:%d\n", id);
    if(id == 0) {
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