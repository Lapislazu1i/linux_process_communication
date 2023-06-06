#include <sys/ipc.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <sys/msg.h>

#define MSG_QUEUE_FILE_PATH "/home/srq/ipc_demo/memory-mapped_files_demo/build"

key_t fkey;
int MSG_ID = 0;
typedef struct MsgQueue_st{ /*msgp定义的参照格式*/
    long type; /* 必须大于0,消息类型 */
    char mtext[256]; /*消息正文，可以是其他任何类型*/
} MsgQueue;
int test1() {
    MsgQueue ms;
    memset(ms.mtext, 0, 256);
    const char* tmp = "hello test2\n";
    ms.type = 3;
    memcpy(ms.mtext, tmp, strlen(tmp));
    ms.mtext[(strlen(tmp) + 1)] = 0;

    
    msgsnd(MSG_ID, &ms, strlen(tmp), 0);
    printf("test1 end\n");

    return 0;
}

int test2() {
    int ret = 0;

    MsgQueue ms;
    memset(ms.mtext, 0, 256);

    printf("test2 start:\n");

    ret = msgrcv(MSG_ID, &ms, 256, 0, 0);
    printf("buf type:%ld\n", ms.type);
    printf("buf:%s\n", ms.mtext);
    printf("test2 end\n\n");
    
    return 0;
}

int main() {
    fkey = ftok(MSG_QUEUE_FILE_PATH, 0);
    MSG_ID = msgget(IPC_PRIVATE, 0666);
    if(MSG_ID < 0) {
      printf("msgget err\n");
      return 0;
    }
    int status;
    int pc;
    pid_t id = fork();
    printf("pid:%d\n", id);
    if(id == 0) {

        test2();
    } else if(id > 0) {
        sleep(1);
        test1();
        pc=wait(&status); //等待子进程结束; 得到子进程的ID
        printf("status:%d\n", status);
        if(WIFEXITED(status)) //子程序正常结束返回非0值，异常返回0
        { 
            printf("我是父进程,我等待的子进程的id号=%d\n",pc); 
            printf("退出码是%d\n",WEXITSTATUS(status)); 
        } 

    } else {
        printf("fork err\b");
        return -1;
    }
    msgctl(MSG_ID, IPC_RMID, NULL);
    return 0;
}