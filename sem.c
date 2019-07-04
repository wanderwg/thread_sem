//用来体会posix标准信号量的基本操作
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
int ticket=100;
sem_t sem;
void *thr_start(void*arg)
{
    while(1){
        //int sem_wait(sem_t *sem);
        sem_wait(&sem);
        if(ticket>0){
            printf("get a ticket:%d\n",ticket);
            ticket--;
        }
        else{
            sem_post(&sem);
            pthread_exit(NULL);
        }
        //int sem_post(sem_t *sem);计数+1，促使其它线程满足条件，然后唤醒所有等待线程
        sem_post(&sem);
    }
    return NULL;
}
int main()
{
    int i;
    pthread_t tid[4];
    //int sem_init(sem_t *sem,int pshared,unsigned int value);
    sem_init(&sem,0,1);
    for(i=0;i<4;++i){
        int ret=pthread_create(&tid[i],NULL,thr_start,NULL);
        if(ret!=0){
            printf("thread create error!\n");
            return -1;
        }
    }
    for(i=0;i<4;++i){
        pthread_join(tid[i],NULL);
    }
    //int sem_destroy(sem_t *sem);
    sem_destroy(&sem);
    return 0;
}
