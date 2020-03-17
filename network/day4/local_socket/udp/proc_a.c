#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <unistd.h>

#define BUF_SIZE 100

int main(int argc, char const *argv[])
{
    // socket
    int proc_a = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(proc_a == -1){
        perror("ProcA Socket");
        return -1;
    }

    // sockaddr_un
    struct sockaddr_un proc_a_addr;
    socklen_t addr_len = sizeof(struct sockaddr_un);
    bzero(&proc_a_addr, addr_len);
    proc_a_addr.sun_family = AF_UNIX;
    strcpy(proc_a_addr.sun_path, "UDP_LOCAL_SOCKET_A");

    // bind
    unlink("UDP_LOCAL_SOCKET_A");

    int res = bind(proc_a, (struct sockaddr *)&proc_a_addr, addr_len);
    if(res == -1){
        perror("ProcA Bind");
        return -1;
    }

    printf("ProcA Bind Successful\n");

    char buf[BUF_SIZE] = {0};
    struct sockaddr_un proc_b_addr;
    bzero(&proc_b_addr, addr_len);

    while(1){
        // recvfrom
        bzero(buf, BUF_SIZE);
        recvfrom(proc_a, buf, BUF_SIZE, 0, (struct sockaddr *)&proc_b_addr, &addr_len);
        printf("recv message: %s", buf);

        // sendto
        bzero(buf, BUF_SIZE);
        printf("send message: ");
        fgets(buf, BUF_SIZE, stdin);
        sendto(proc_a, buf, BUF_SIZE, 0, (struct sockaddr *)&proc_b_addr, addr_len);
    }


    return 0;
}
