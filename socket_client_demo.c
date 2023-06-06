#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#define LISTEN_PORT 9212
int main() {
    int ret = 0;
    char buf[4096] = {0};
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
    ret = connect(demoSocket, (struct sockaddr*)&addr, sizeof( struct sockaddr_in));
    if(ret < 0) {
        printf("connect err\n");
        return -1;
    }

    while(1) {
        char sdbuf[1024];
        char rvbuf[1024];
        int rdlen, sdlen, i;
        i = 0;
        while((sdbuf[i] = getchar()) != '\n') {
            ++i;
            if(i == 0) {
                continue;
            }
        }
        sdlen = write(demoSocket, sdbuf, i);
        rdlen = 0;
        while(rdlen < sdlen) {
            int rdcnt = read(demoSocket, &rvbuf[rdlen], sizeof(rvbuf));
            if(rdcnt == -1) {
                perror(NULL);
                continue;
            }
            rdlen += rdcnt;
        }
        if(rdlen) {
            rvbuf[rdlen] = 0;
            printf("recv:%s\n", rvbuf);
        } else {
            printf("exit\n");
            break;
        }

    }
    close(demoSocket);
    return 0;
}