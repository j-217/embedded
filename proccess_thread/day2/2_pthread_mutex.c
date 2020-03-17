#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define BUF_SIZE 10

pthread_mutex_t g_m_lock;

void *t_func(void *arg)
{
    if(arg == NULL){
        exit(-1);
    }

    char *str = (char *)arg;
    
// Use mutex and static variable
#if __USE_MUTEX 
    static char buf[BUF_SIZE] = {'\0'};
    pthread_mutex_lock(&g_m_lock);
    sleep(1);
    memset(buf, '\0', BUF_SIZE);
    for(int i = 0; i < strlen(str); i++){
        buf[i] = str[i];
        usleep(5000);
    }
    pthread_mutex_unlock(&g_m_lock);
#endif

// Use normal variable
#if __USE_NORMAL_VAR
    char buf[BUF_SIZE] = {'\0'};

    for(int i = 0; i < strlen(str); i++){
        buf[i] = str[i];
        usleep(5000);
    }
#endif

// Use malloc
#if __USE_MALLOC
    char *buf = (char *)malloc(BUF_SIZE);
    memset(buf, '\0', BUF_SIZE);

    for(int i = 0; i < strlen(str); i++){
        buf[i] = str[i];
        usleep(5000);
    }
#endif

    printf("Result: %s\n", buf);
}

int main(int argc, char const *argv[])
{
    pthread_t tid_1 = 0;
    pthread_t tid_2 = 0;

    char str_t1[] = "ABCDEFG",
         str_t2[] = "123456789";

    // init pthread_mutex
    if(pthread_mutex_init(&g_m_lock, NULL) != 0){
        perror("Mutex Init");
        return -1;
    }

    if(    
        pthread_create(&tid_1, NULL, t_func, (void *)str_t1) != 0
     || pthread_create(&tid_2, NULL, t_func, (void *)str_t2) != 0
    ){
        perror("Thread Create");
        return -1;
    }

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    printf("Main Function End\n");
    
    return 0;
}
