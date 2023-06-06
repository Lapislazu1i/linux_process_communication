#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h> 
key_t SEM_KEY = 1;
int SEM_ID = 0;

void getkey(int semid)//得到钥匙
{
    struct sembuf sop;
    sop.sem_num = 0;//控制第一个信号量
    sop.sem_op  = -1;//钥匙数量减一6
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

    while(1) {
        getkey(SEM_ID);
        printf("chlid get a key\n");
        i = i + 1;
        printf("child:%d\n", i);
        if(i > 10) {
            break;
        }
    }
    return 0;
}