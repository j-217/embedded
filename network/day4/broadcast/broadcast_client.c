#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 7777
#define BUF_SIZE 100

int main(void)
{
    // socket
    int skt_clt = socket(AF_INET, SOCK_DGRAM, 0);
    if(skt_clt == -1){
        perror("Client Socket");
        return -1;
    }

    // bind
    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    memset(&serv_addr, 0, addr_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(PORT);

    int res = bind(skt_clt, (struct sockaddr *)&serv_addr, addr_len);
    if(res == -1){
        perror("Client Bind");
        return -1;
    }
    printf("Bind Successful\n");

    // recvfrom
    char buf[BUF_SIZE] = {'\0'};

    while(1){
        memset(buf, 0, BUF_SIZE);
        res = recvfrom(skt_clt, buf, BUF_SIZE, 0, (struct sockaddr *)&serv_addr, &addr_len);
        if(res < 0){
            printf("no more infos\n");
            return -1;
        }

        printf("Recv: %s", buf);
    }

    // close
    close(skt_clt);

    return 0;
}