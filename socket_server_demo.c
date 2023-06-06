#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#define LISTEN_PORT 9212
int main() {
    const char* replay = "-s";
    unsigned int bufSize = 50000000+1024;
    char* buf = (char*)malloc(bufSize);
    int demoSocket = -1;
    int clientSocket = 0;
    demoSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(demoSocket < 0) {
        perror("create socket err\n");
        return -1;
    }
    struct sockaddr_in addr;

    memset(&addr,0,sizeof(addr));

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(LISTEN_PORT);
    addr.sin_family = AF_INET;
    if(bind(demoSocket, (struct sockaddr*)&addr, sizeof( struct sockaddr_in)) < 0) {
        perror("bind err\n");
        return -1;
    }
    if(listen(demoSocket, 1) < 0) {
        perror("listen err\n");
        return -1;    
    }
    clientSocket = accept(demoSocket, NULL, NULL);
    if(clientSocket < 0) {
        printf("accept err:%d\n", clientSocket);
        return -1;     
    }

    while(1) {
        int rdRet = 0;

        rdRet = read(clientSocket, buf, bufSize);
        if(rdRet > 0) {
            // printf("read data:%s\n", buf);
            memcpy(buf + rdRet, replay, strlen(replay));
            buf[strlen(buf) + 1] =  0;
            write(clientSocket, buf, strlen(buf));
        } else if(rdRet == 0) {
            printf("client exit\n");
            break;
        } else {
            break;
        }
    }
    close(clientSocket);
    close(demoSocket);
}