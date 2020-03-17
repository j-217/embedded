#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sig_handler(int signno)
{
    if(signno == SIGUSR1){
        printf("Receive SIGUSR1\n");
        return ;
    }
    if(signno == SIGUSR2){
        printf("Receive SIGUSR2\n");
    } 

}

int main(int argc, char const *argv[])
{
    printf("%d is running...\n", getpid());
    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    while(1){
        pause();
    }

    return 0;
}
