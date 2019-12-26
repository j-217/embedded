#include "my_ftp.h"

int main(int argc, char const *argv[])
{
    int test_count = 0;
    // socket
    int skt_serv = socket(AF_INET, SOCK_STREAM, 0);
    if(skt_serv == -1){
        printf("Server Socket Create Failed\n");
        return -1;
    }

    // bind
    struct sockaddr_in serv_addr_s;
    memset(&serv_addr_s, 0, sizeof(struct sockaddr_in));
    serv_addr_s.sin_family = AF_INET;
    serv_addr_s.sin_port = htons(34567);
    serv_addr_s.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int res = bind(skt_serv, (struct sockaddr *)&serv_addr_s, sizeof(struct sockaddr_in));
    if(res == -1){
        printf("Server Bind Failed\n");
        return -1;
    }

    // listen
    res = listen(skt_serv, 5);
    if(res == -1){
        printf("Server Listen Failed\n");
        return -1;
    }
    printf("Server listening in 127.0.0.1:34567\n");

    // accept
    struct sockaddr_in clt_addr_s;
    socklen_t clt_len = sizeof(struct sockaddr_in);
    int skt_clt = -1,                               // fd: client socket
        fdr = -1;                                   // fd: file to send
    ssize_t read_num = -1;                          // the number which read from file
    info n_info;                                    // transmit data
    memset(&n_info, 0, sizeof(info));           
    
    while(1){
        test_count = 0;
        memset(&clt_addr_s, 0, clt_len);

        skt_clt = accept(skt_serv, (struct sockaddr *)&clt_addr_s, &clt_len);
        if(skt_clt == -1){
            printf("Server Accept Failed\n");
            return -1;
        }

        memset(n_info.i_text, 0, sizeof(info));
        // recv
        if(recv(skt_clt, &n_info, sizeof(info), 0) == -1){
            printf("Server Receive Failed\n");
            close(skt_clt);
            continue;
        }
        if(strcmp(n_info.i_text, "quit") == 0){
            printf("Process Client %d Exit\n", skt_clt);
            close(skt_clt);
            continue;
        }

        fdr = open(n_info.i_text, O_RDONLY, 0666);
        if(fdr == -1){
            printf("File Not Found\n");
            strcpy(n_info.i_text, "Status: 404");
            n_info.i_len = strlen(n_info.i_text);
            send(skt_clt, &n_info, sizeof(info), 0);
            close(skt_clt);
            continue;
        }

        // send
        printf("Sending File: [%s]\n", n_info.i_text);
        while(1){
            usleep(500);                                                // set delay 500us
            memset(&n_info, 0, sizeof(info));
            read_num = read(fdr, n_info.i_text, BUF_SIZE);              // set transmit data text
            if(read_num < 0){
                printf("Server Read Failed\n");
                close(fdr);
                close(skt_clt);
                break;
            }

            n_info.i_len = read_num;                                    // read_num >=0 set to transmit data length
            printf("%d - len: %ld\n", test_count, n_info.i_len);

            if(read_num == 0){
                printf("Send_count: %d\n", test_count);
                printf("Sending File: Done\n");
                close(fdr);
                close(skt_clt);
                break;
            }
            if(send(skt_clt, &n_info, sizeof(info), 0) == -1){
                printf("Network Error\n");
                close(fdr);
                close(skt_clt);
                break;
            }
            test_count++;
        }
    }
    // close
    close(skt_clt);
    close(skt_serv);

    return 0;
}
