#include "comm.h"

int main(void)
{
    // init
    int skt_serv = -1,                                          // server_socket
        skt_clt = -1,                                           // client_socket
        epfd = -1,                                              // epoll file description
        n_epwt = -1,                                            // epoll wait return
        res = -1,                                               // function result
        fd_flag = -1;                                           // fd flag
    
    int n_rw = -1;
    char buf[BUF_SIZE] = {'\0'};                                // read, write buffer
    
    struct sockaddr_in serv_addr_s, clt_addr_s;                 // server address struct, client address struct
    socklen_t addr_s_len = sizeof(struct sockaddr_in);          // length of struct sockaddr_in

    struct epoll_event ev, evs[EPOLL_EVS_SIZE];                 // epoll event, array events

    // socket
    skt_serv = socket(AF_INET, SOCK_STREAM, 0);
    if(skt_serv == -1){
        perror("Server Socket");
        return ERROR_S;
    }

    // bind
    memset(&serv_addr_s, 0, addr_s_len);
    serv_addr_s.sin_family = AF_INET;
    serv_addr_s.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "0.0.0.0", &serv_addr_s.sin_addr.s_addr);

    int skt_opt = 1;
    setsockopt(skt_serv, SOL_SOCKET, SO_REUSEADDR, &skt_opt, sizeof(skt_opt));              // set reuse address

    // struct timeval tv = {10, 0};
    // setsockopt(skt_serv, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));                         // set recv timeout

    res = bind(skt_serv, (struct sockaddr *)&serv_addr_s, addr_s_len);
    if(res == -1){
        perror("Server Bind");
        return ERROR_S;
    }

    // listen
    res = listen(skt_serv, 100);
    if(res == -1){
        perror("Server Listen");
        return -1;
    }

    printf("Server running in 127.0.0.1:56789...\n");

    // accept
    epfd = epoll_create(100);
    ev.data.fd = skt_serv;
    ev.events = EPOLLIN;
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, skt_serv, &ev);
    if(res == -1){
        perror("Server epoll_ctl");
        return ERROR_S;
    }
    
    while(1){
        n_epwt = epoll_wait(epfd, evs, EPOLL_EVS_SIZE, 0);
        if(n_epwt < 0){
            perror("Server epoll_wait");
            return ERROR_S;
        }
        
        if(n_epwt > 0){
            printf("n_epwt: %d\n", n_epwt);
            for(int i = 0; i<n_epwt; i++){
                if(evs[i].data.fd == skt_serv){
                    skt_clt = accept(skt_serv, (struct sockaddr *)&clt_addr_s, &addr_s_len);
                    if (skt_clt == -1){
                        perror("Server Accept");
                        continue;
                    }

                    fd_flag = fcntl(skt_clt, F_GETFL);                      // set non-block
                    fd_flag |= O_NONBLOCK;
                    fcntl(skt_clt, F_SETFL, fd_flag);

                    ev.data.fd = skt_clt;
                    ev.events = EPOLLIN;
                    res = epoll_ctl(epfd, EPOLL_CTL_ADD, skt_clt, &ev);
                    if(res == -1){
                        perror("Server epoll_ctl");
                        continue;
                    }
                }else{
                    // recv/send
                    printf("Client [%d] Connected\n", evs[i].data.fd);
                    while(1){
                        memset(buf, 0, BUF_SIZE);
                        res = read(evs[i].data.fd, buf, BUF_SIZE);
                        if(res == 0){
                            printf("Read Finish\n");
                        }
                        if(res < 0){
                            printf("Client [%d] Disconnected\n", evs[i].data.fd);
                            close(evs[i].data.fd);
                            epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                            break;
                        }

                        ev.data.fd = evs[i].data.fd;
                        ev.events = EPOLLOUT | EPOLLET;
                        epoll_ctl(epfd, EPOLL_CTL_MOD, evs[i].data.fd, &ev);

                        printf("read n: %d %s\n", res, buf);
                        res = write(evs[i].data.fd, buf, res);

                        printf("write n: %d %s\n", res, buf);
                        if(res < 0){
                            printf("Write Failed\n");
                            close(evs[i].data.fd);
                            epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                            break;
                        }
                    }
                }
            }
        }
    }

    // close
    close(skt_serv);

    return 0;
}
