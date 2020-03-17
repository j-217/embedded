#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct {
    char *words;
    int count;
}t_func_args;

sem_t g_sem_t1;
sem_t g_sem_t2;

void *t_func_1(void *arg)
{
    t_func_args * args = (t_func_args *)arg;
    while(args->count--){
        sem_wait(&g_sem_t1);
        printf("%s\n", args->words);
        sleep(1);
        sem_post(&g_sem_t2);
    }

    pthread_exit("Thread 1 stop");
}

void *t_func_2(void *arg)
{
    t_func_args * args = (t_func_args *)arg;
    while(args->count--){
        sem_wait(&g_sem_t2);
        printf("%s\n", args->words);
        sleep(1);
        sem_post(&g_sem_t1);
    }

    pthread_exit("Thread 2 stop");
}

int main(int argc, char const *argv[])
{
    pthread_t tid_1 = 0;
    pthread_t tid_2 = 0;

    t_func_args arg_t1 = {"Thread 1 running...", 5};
    t_func_args arg_t2 = {"Thread 2 running...", 5};

    // init semaphores
    if(sem_init(&g_sem_t1, 0, 1) != 0 || sem_init(&g_sem_t2, 0, 0) != 0){
        perror("Semaphore Init");
        return -1;
    }
    
    if(pthread_create(&tid_1, NULL, t_func_1, (void *)&arg_t1) != 0){
        perror("Thread Create");
        return -1;
    }

    if(pthread_create(&tid_2, NULL, t_func_2, (void *)&arg_t2) != 0){
        perror("Thread Create");
        return -1;
    }

    char *res_t1 = NULL;
    char *res_t2 = NULL;

    pthread_join(tid_1, (void *)&res_t1);
    pthread_join(tid_2, (void *)&res_t2);

    // print pthread_exit info
    printf("%s\n", res_t1);
    printf("%s\n", res_t2);

    printf("Process End\n");

    return 0;
}
