#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <sys/shm.h> 
int shmid;
struct shmid_ds buf;
int test1() {
    const char* tmp = "hello test2\n";
    int flag = 0;
    char* shp = NULL;
    printf("test1 start:\n");
    flag = shmctl(shmid, IPC_STAT, &buf);
    if(flag == -1) {
        perror("shmctl shm error\n");
        return -1;
    }
    printf("shm_segsz:%ld bytes\n", buf.shm_segsz);
    shp = (char*)shmat(shmid, NULL, 0);
    printf("shp:%s\n", shp);
    printf("test1 end\n");
    shmdt(shp);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

int test2() {
    char* shmaddr = NULL;
    printf("test2 start:\n");

    shmaddr = (char*)shmat(shmid, NULL, 0);
    if ((int)shmaddr == -1) {
        perror("shmat addr error") ;
        return -1 ;
    }
    strcpy(shmaddr, "Hi, I am child process!\n");
    shmdt(shmaddr) ;
    printf("test2 end\n\n");
    
    return 0;
}

int main() {
    shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT|0666 ) ;
    if ( shmid < 0 ) {
        perror("get shm  ipc_id error\n") ;
        return -1 ;
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

    return 0;
}