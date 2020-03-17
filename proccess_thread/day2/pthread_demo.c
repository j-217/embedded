#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_fun_1(void *arg)
{
    printf("Thread 1 running...\n");
    sleep(2);
    // pthread_exit("Thread 1 exit");

    // test pthread_detach
    printf("Thread 1 end\n");
}

void *thread_fun_2(void *arg)
{
    printf("Thread 2 running...\n");

    // pthread_exit("Thread 2 exit");
    // test pthread_detach
    printf("Thread 2 end\n");
}

int main(void)
{
    pthread_t tid_1 = 0;
    pthread_t tid_2 = 0;

    if(pthread_create(&tid_1, NULL, thread_fun_1, NULL) != 0){
        exit(1);
    }
    if(pthread_create(&tid_2, NULL, thread_fun_2, NULL) != 0){
        exit(1);
    }
    
    // test pthread_join
#if 0
    char *res_t1 = NULL;
    char *res_t2 = NULL;
    printf("%p %p\n", res_t1, res_t2);
    pthread_join(tid_1, (void *)&res_t1);
    pthread_join(tid_2, (void *)&res_t2);
    printf("%p %p\n", res_t1, res_t2);
    
    printf("Tread 1 result: %s\n", res_t1);
    printf("Tread 2 result: %s\n", res_t2);
#endif

    // test pthread_detach
#if 1
    pthread_detach(tid_1);
    pthread_detach(tid_2);

    sleep(5);
#endif

    printf("main end\n");

    return 0;
}
