#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7777
#define BUF_SIZE 100

int main(void)
{
    // socket
    int skt_clt = socket(AF_INET, SOCK_DGRAM, 0);
    if(skt_clt == -1){
        perror("Socket");
        return -1;
    }
    // add membership
    struct ip_mreq mreq;
    memset(&mreq, 0, sizeof(struct ip_mreq));
    mreq.imr_multiaddr.s_addr = inet_addr("224.11.11.1");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    setsockopt(skt_clt, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    
    // sockaddr_in
    struct sockaddr_in serv_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    memset(&serv_addr, 0, addr_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serv_addr.sin_port = htons(PORT);

    // bind
    int opt = 1;
    setsockopt(skt_clt, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    bind(skt_clt, (struct sockaddr *)&serv_addr, addr_len);

    printf("Bind Successful\n");

    // recvfrom
    char buf[BUF_SIZE] = {'\0'};

    while(1){
        memset(buf, 0, BUF_SIZE);
        recvfrom(skt_clt, buf, BUF_SIZE, 0, (struct sockaddr *)&serv_addr, &addr_len);
        printf("recv: %s\n", buf);
    }
    
    // close
    close(skt_clt);

    return 0;
}
