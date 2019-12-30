#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>
#include <unistd.h>

#define BUF_SIZE 100

int main(void)
{
    // socket
    int skt_serv = socket(AF_UNIX, SOCK_STREAM, 0);
    if(skt_serv == -1){
        perror("Server Socket");
        return -1;
    }

    // sockaddr_un
    struct sockaddr_un clt_addr;
    socklen_t addr_len = sizeof(struct sockaddr_un);
    bzero(&clt_addr, addr_len);
    clt_addr.sun_family = AF_UNIX;
    strcpy(clt_addr.sun_path, "TCP_LOCAL_SOCKET");

    // bind
    unlink("TCP_LOCAL_SOCKET");

    int res = bind(skt_serv, (struct sockaddr *)&clt_addr, addr_len);
    if(res == -1){
        perror("Bind");
        return -1;
    }

    // listen
    res = listen(skt_serv, 20);
    if(res == -1){
        perror("Listen");
        return -1;
    }
    printf("Listen Successful\n");

    char buf[BUF_SIZE] = {0};

    // accept
    int skt_clt = accept(skt_serv, (struct sockaddr *)&clt_addr, &addr_len);
    if(skt_clt == -1){
        perror("Client Sockt");
        return -1;
    }
    while(1){
        // recv
        bzero(buf, BUF_SIZE);
        res = recv(skt_clt, buf, BUF_SIZE, 0);
        if(strcmp(buf, "quit\n") == 0){
            printf("Client Disconnected\n");
            close(skt_clt);
            break;
        }
        printf("recv message: %s", buf);
        
        // send
        bzero(buf, BUF_SIZE);
        printf("send message: ");
        fgets(buf, BUF_SIZE, stdin);
        if(strcmp(buf, "quit\n") == 0){
            printf("Server Disconnected\n");
            close(skt_clt);
            break;
        }

        res = send(skt_clt, buf, BUF_SIZE, 0);
    }

    return 0;
}
