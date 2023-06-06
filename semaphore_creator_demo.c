#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h> 
key_t SEM_KEY = 1;
int SEM_ID = 0;
union semun{
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};
void getkey(int semid)//得到钥匙
{
    struct sembuf sop;
    sop.sem_num = 0;//控制第一个信号量
    sop.sem_op  = -1;//钥匙数量减一
    sop.sem_flg = SEM_UNDO;
    semop(semid,&sop,1);
}
 
void backkey(int semid)//放回钥匙
{
    struct sembuf sop;
    sop.sem_num = 0;
    sop.sem_op  = 1;
    sop.sem_flg = SEM_UNDO;
    semop(semid,&sop,1);
}

int i = 0;
int main() {
    SEM_KEY = ftok(".",1);
    int status;
    int pc;
    SEM_ID = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if(SEM_ID < 0) {
        perror("semget err\n");
        return -1;
    }

    union semun set;
    set.val = 1;//钥匙数量为0
    semctl(SEM_ID,0,SETVAL,set);//对信号量进行控制，第0个信号量，SETVAL将初始化信号量为一个已知的值，set为联合共用体，设置初始钥匙数量
    while(1) {
        sleep(1);
        ++i;
        backkey(SEM_ID);
        printf("father put a key\n");
        if(i > 10) {
            break;
        }
    }
    semctl(SEM_ID, 0, IPC_RMID);
    return 0;
}