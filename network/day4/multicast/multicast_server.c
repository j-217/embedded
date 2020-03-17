#include <stdio.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#define BUF_SIZE 100

int main(int argc, char const *argv[])
{
    // socket
    int skt_serv = socket(AF_INET, SOCK_DGRAM, 0);
    if(skt_serv == -1){
        perror("socket");
        return -1;
    }

    // sockaddr_in
    struct sockaddr_in mul_addr;
    socklen_t len = sizeof(struct sockaddr_in);
    memset(&mul_addr, 0, len);
    mul_addr.sin_family = AF_INET;
    mul_addr.sin_port = htons(7777);
    mul_addr.sin_addr.s_addr = inet_addr("224.11.11.1");

    // send
    char buf[BUF_SIZE] = {'\0'};

    while(1){
        memset(buf, 0, BUF_SIZE);
        printf("input something: ");
        fgets(buf, BUF_SIZE, stdin);

        sendto(skt_serv, buf, BUF_SIZE, 0, (struct sockaddr *)&mul_addr, len);
    }
    
    // close
    close(skt_serv);

    return 0;
}
