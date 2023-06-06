#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#define MMAP_FILE_PATH "./tmp.txt"

int test1() {
    const char* tmp = "hello test2\n";
    void* mapIdx = NULL;
    int mapFd = -1;
    mapFd = open(MMAP_FILE_PATH, O_RDWR);
    if(mapFd == -1) {
        printf("open err\n");
        return -1;
    }
    mapIdx = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mapFd, 0);
    printf("test1 start:\n");

    memcpy(mapIdx, tmp, strlen(tmp));
    // msync(mapIdx, strlen(tmp), MS_SYNC);
    printf("test1 end\n");
    printf("munmap:%d\n", munmap(mapIdx, 4096));
    close(mapFd);
    return 0;
}

int test2() {
    void* mapIdx = NULL;
    int mapFd = -1;
    mapFd = open(MMAP_FILE_PATH, O_RDWR);
    if(mapFd == -1) {
        printf("open err\n");
        return -1;
    }
    mapIdx = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, mapFd, 0);
    printf("test2 start:\n");

    printf("test2 read from test1:%s\n", (char*)mapIdx);

    // msync(mapIdx, 4096, MS_SYNC);
    printf("test2 end\n\n");
    printf("munmap:%d\n", munmap(mapIdx, 4096));
    close(mapFd);
    return 0;
}

int main() {
    int status;
    int pc;
    FILE* fp = fopen(MMAP_FILE_PATH, "wb");
    char tmpBuf[4096] = {0};
    fwrite(tmpBuf, 4096, 1,  fp);
    fclose(fp);
    pid_t id = fork();
    printf("pid:%d\n", id);
    if(id == 0) {
        sleep(1);
        test2();
    } else if(id > 0) {
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

    return 0;
}