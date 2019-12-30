#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <strings.h>

#define BUF_SIZE 100

int main(int argc, char const *argv[])
{
    // socket
    int skt_clt = socket(AF_UNIX, SOCK_STREAM, 0);
    if(skt_clt == -1){
        perror("Client Socket");
        return -1;
    }

    // sockaddr_un
    struct sockaddr_un serv_addr;
    socklen_t addr_len = sizeof(struct sockaddr_un);
    bzero(&serv_addr, addr_len);
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, "TCP_LOCAL_SOCKET");

    // connect
    int res = connect(skt_clt, (struct sockaddr *)&serv_addr, addr_len);
    if(res == -1){
        perror("Connect");
        return -1;
    }

    char buf[BUF_SIZE] = {0};

    while(1){
        bzero(buf, BUF_SIZE);

        // send
        printf("send message: ");
        fgets(buf, BUF_SIZE, stdin);
        send(skt_clt, buf, BUF_SIZE, 0);
        
        // recv
        bzero(buf, BUF_SIZE);
        recv(skt_clt, buf, BUF_SIZE, 0);
        printf("recv message: %s", buf);

    };

    return 0;
}
