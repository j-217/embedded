#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 7777
#define BUF_SIZE 100

int main(void)
{
    // socket
    int skt_serv = socket(AF_INET, SOCK_DGRAM, 0);
    if (skt_serv == -1) {
        perror("Socket");
        return -1;
    }

    // setsockopt
    int opt = -1;
    setsockopt(skt_serv, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    // broadcast address
    struct sockaddr_in clt_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    memset(&clt_addr, 0, addr_len);
    clt_addr.sin_family = AF_INET;
    clt_addr.sin_port = htons(PORT);
    clt_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    printf("Broadcast Server Running...\n");

    // sendto
    char buf[BUF_SIZE] = {'\0'};
    int res = -1;

    while(1){
        memset(buf, 0, BUF_SIZE);
        printf("input infos: ");
        fgets(buf, BUF_SIZE, stdin);

        res = sendto(skt_serv, buf, BUF_SIZE, 0, (struct sockaddr *)&clt_addr, addr_len);
        if (res == -1) {
            perror("Sendto");
            return -1;
        }
    }

    // close
    close(skt_serv);

    return 0;
}
