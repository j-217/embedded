/*
 * @Description: A simple blog server based on epoll, just for practice
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2019-12-31 11:11:40
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-02 08:46:23
 */
#include "my_srv.h"

int main(void)
{
    // init variables
    int skt_serv = -1,                                          // server_socket
        skt_clt = -1,                                           // client_socket
        epfd = -1,                                              // epoll file description
        n_epwt = -1,                                            // epoll wait return
        res = -1,                                               // function result
        fd_flag = -1,                                           // fd flag
        n_rw = -1;                                              // read, write result

    struct sockaddr_in serv_addr_s, clt_addr_s;                 // server address struct, client address struct
    socklen_t addr_s_len = sizeof(struct sockaddr_in);          // length of struct sockaddr_in

    struct epoll_event ev, evs[EPOLL_EVS_SIZE];                 // epoll event, array events

    clt_data n_clt_data;                                        // struct client data
    unsigned long clt_data_len = sizeof(clt_data);              // length of struct client data
    bzero(&n_clt_data, clt_data_len);
    serv_data n_srv_data;                                       // struct server data
    unsigned long srv_data_len = sizeof(serv_data);             // length of struct server data
    bzero(&n_srv_data, srv_data_len);
    serv_data *p_srv_data = &n_srv_data;

    int range_flag = -1;                                        // display range flag
    
    
/*---------------------database------------------------------------------------*/

    // init variables
    sqlite3 *p_db = NULL;

    // init database and tables
    
    res = init_db(&p_db); 
    if(res == ERROR_S){
        return ERROR_S;
    }

/*---------------------database end--------------------------------------------*/

    // socket
    skt_serv = socket(AF_INET, SOCK_STREAM, 0);
    if(skt_serv == -1){
        perror("[ERROR] Server Socket");
        return ERROR_S;
    }

    // bind
    memset(&serv_addr_s, 0, addr_s_len);
    serv_addr_s.sin_family = AF_INET;
    serv_addr_s.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &serv_addr_s.sin_addr.s_addr);

    int skt_opt = 1;                                                                        // set reuse address and port
    setsockopt(skt_serv, SOL_SOCKET, SO_REUSEADDR, &skt_opt, sizeof(skt_opt));              

    // struct timeval tv = {10, 0};                                                            // set recv timeout
    // setsockopt(skt_serv, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));                         

    res = bind(skt_serv, (struct sockaddr *)&serv_addr_s, addr_s_len);
    if(res == -1){
        perror("[ERROR] Server Bind");
        return ERROR_S;
    }

    // listen
    res = listen(skt_serv, 100);
    if(res == -1){
        perror("[ERROR] Server Listen");
        return -1;
    }

    printf("[INFO] Server running in 127.0.0.1:56789...\n");

    // accept
    epfd = epoll_create(100);
    ev.data.fd = skt_serv;
    ev.events = EPOLLIN;
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, skt_serv, &ev);
    if(res == -1){
        perror("[ERROR] Server epoll_ctl");
        return ERROR_S;
    }
    
    while(1){
        n_epwt = epoll_wait(epfd, evs, EPOLL_EVS_SIZE, 0);
        if(n_epwt < 0){
            perror("[ERROR] Server epoll_wait");
            return ERROR_S;
        }
        
        if(n_epwt > 0){
            for(int i = 0; i<n_epwt; i++){
                if(evs[i].data.fd == skt_serv){                                              // event server socket
                    skt_clt = accept(skt_serv, (struct sockaddr *)&clt_addr_s, &addr_s_len);
                    if (skt_clt == -1){
                        perror("[ERROR] Server Accept");
                        continue;
                    }

                    fd_flag = fcntl(skt_clt, F_GETFL);                                       // set non-block
                    fd_flag |= O_NONBLOCK;
                    fcntl(skt_clt, F_SETFL, fd_flag);

                    ev.data.fd = skt_clt;
                    ev.events = EPOLLIN | EPOLLET;
                    res = epoll_ctl(epfd, EPOLL_CTL_ADD, skt_clt, &ev);
                    if(res == -1){
                        perror("[ERROR] Server epoll_ctl");
                        continue;
                    }
                }else if(evs[i].events & EPOLLIN){                                              // event epollin
                    printf("[INFO] Client [%d] Connected\n", evs[i].data.fd);
                    bzero(&n_clt_data, clt_data_len);                                           // reset client data
                    n_rw = read(evs[i].data.fd, &n_clt_data, clt_data_len);

                    if(n_rw == 0){
                        printf("[INFO] Receive Nothing, Disconnected Client[%d]\n", evs[i].data.fd);
                        close(evs[i].data.fd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                        continue;
                    }
                    if(n_rw < 0){
                        printf("[ERROR] Client [%d] Error\n", evs[i].data.fd);
                        close(evs[i].data.fd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                        continue;
                    }

/*-----------------------------------handle request-----------------------------------------------------------*/
                    switch(n_clt_data.opt)
                    {
                        case 1:
                            res = handle_login(p_db, &n_clt_data, &p_srv_data);
                            if(res == ERROR_S){
                                printf("[ERROR] Client [%d] Login Failed\n", evs[i].data.fd);
                                continue;
                            }
                            break;
                            
                        case 3:
                            res = handle_signup(p_db, &n_clt_data, &p_srv_data);
                            if(res == ERROR_S){
                                printf("[ERROR] Client [%d] Signup Failed\n", evs[i].data.fd);
                                continue;
                            }
                            break;

                        case 4:
                            range_flag = SH_ALL_FLG;
                            res = handle_show(p_db, &n_clt_data, &p_srv_data, range_flag);
                            if(res == ERROR_S){
                                printf("[ERROR] Client [%d] Signup Failed\n", evs[i].data.fd);
                                continue;
                            }
                            break;

                        case 5:
                            res = handle_publish(p_db, &n_clt_data, &p_srv_data);
                            if(res == ERROR_S){
                                printf("[ERROR] Client [%d] publish Failed\n", evs[i].data.fd);
                                continue;
                            }
                            break;

                        case 6:
                            range_flag = SH_MINE_FLG;
                            res = handle_show(p_db, &n_clt_data, &p_srv_data, range_flag);
                            if(res == ERROR_S){
                                printf("[ERROR] Client [%d] Signup Failed\n", evs[i].data.fd);
                                continue;
                            }
                            break;

                        default:
                            break;
                    }
                    
/*------------------------------------handle end--------------------------------------------------------------*/


                    ev.data.fd = evs[i].data.fd;                                               // modify fd to out
                    ev.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, evs[i].data.fd, &ev);

                }else if(evs[i].events & EPOLLOUT){                                            // event epollout
                    printf("[INFO]Client [%d] Connected\n", evs[i].data.fd);
                    
/*-----------------------------------handle response----------------------------------------------------------*/
                    

/*------------------------------------handle end--------------------------------------------------------------*/
                    n_rw = write(evs[i].data.fd, &n_srv_data, srv_data_len);
                    
                    bzero(&n_srv_data, srv_data_len);                                           // reset server data
                    if(n_rw == 0){
                        printf("[ERROR] Nothing To Send, Disconnected Client[%d]\n", evs[i].data.fd);
                        continue;
                    }

                    if(n_rw < 0){
                        printf("[ERROR] Client [%d] Error\n", evs[i].data.fd);
                        close(evs[i].data.fd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                        continue;
                    }
                    ev.data.fd = evs[i].data.fd;                                                // modify fd to in
                    ev.events = EPOLLIN | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, evs[i].data.fd, &ev);
                }
            }
        }
    }

    // close
    close(skt_serv);

    return 0;
}
