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

#define MSG_QUEUE_FILE_PATH "msg.txt"

typedef struct MsgQueue_st{ /*msgp定义的参照格式*/
    long type; /* 必须大于0,消息类型 */
    char mtext[256]; /*消息正文，可以是其他任何类型*/
} MsgQueue;


int main() {
    key_t fkey;
    MsgQueue ms;
    memset(ms.mtext, 0, 256);
    const char* tmp = "hello reader\n";
    memcpy(ms.mtext, tmp, strlen(tmp));
    ms.type = 3;
    fkey = ftok(MSG_QUEUE_FILE_PATH, 1);
    int msgId = msgget(fkey, 0660|IPC_CREAT);
    if(msgId < 0) {
        perror("msgget err\n");
        return -1;
    }
    msgsnd(msgId, &ms, strlen(tmp), 0);
    return 0;
}