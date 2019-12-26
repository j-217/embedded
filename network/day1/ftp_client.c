#include "my_ftp.h"

int main(int argc, char const *argv[])
{
    // init
    int skt_clt = -1,                       // client socket
        res = -1,                           // result
        fdw = -1;                           // fd: write

    char filename[BUF_SIZE] = {'\0'};       // filename backup
    info n_info;                            // receive data

    struct sockaddr_in clt_addr_s;          // client socketaddress_in
    int test_count = 0;
    
RECONNECT:
    // socket
    skt_clt = socket(AF_INET, SOCK_STREAM, 0);
    if(skt_clt == -1){
        printf("Client Socket Failed\n");
        return -1;
    }

    // connect
    memset(&clt_addr_s, 0, sizeof(struct sockaddr_in));
    clt_addr_s.sin_family = AF_INET;
    clt_addr_s.sin_port = htons(34567);
    clt_addr_s.sin_addr.s_addr = inet_addr("127.0.0.1");

    res = connect(skt_clt, (struct sockaddr *)&clt_addr_s, sizeof(struct sockaddr_in));
    if(res == -1){
        printf("Client Connect Failed\n");
        return -1;
    }
    printf("Client Connect to 127.0.0.1:34567\n");

    // send
    printf("Enter A Filename To Download(To Exit Use 'quit'): ");
    fgets(n_info.i_text, BUF_SIZE, stdin);
    if(strlen(n_info.i_text) <= 1){
        printf("Filename Is Too Short\n");
        goto RECONNECT;
    }
    n_info.i_text[strlen(n_info.i_text) - 1] = '\0';                    // remove '\n' from filename
    if(send(skt_clt, &n_info, sizeof(info), 0) == -1){
        printf("Network Error\n");
        return -1;
    }
    if(strcmp(n_info.i_text, "quit") == 0){                             // exit client process
        close(skt_clt);
        return 0;
    }

    // recv
    strcpy(filename, strcat(n_info.i_text, ".dl"));                     // backup the filename, delete it when it is not found
    fdw = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(fdw == -1){
        perror("Client Open File");
        return -1;
    }

    test_count = 0;

    printf("Downloading...\n");
    while(1){
        memset(&n_info, 0, sizeof(info));
        if(recv(skt_clt, &n_info, sizeof(info), 0) == -1){
            printf("Client Receive Failed\n");
            break;
        }

        printf("%d - len: %ld\n", test_count, n_info.i_len);

        if(strcmp(n_info.i_text, "Status: 404") == 0){                  // no file found in server
            printf("No File Found\n");
            close(fdw);
            remove(filename);
            goto RECONNECT;
        }

        res = write(fdw, n_info.i_text, n_info.i_len);
        

        if(res == 0){                                                   // 0 for end
            printf("File Download Complete\n");
            printf("Write_count: %d\n", test_count);
            close(fdw);
            goto RECONNECT;
        }

        test_count++;

        if(res < 0){                                                    // negative for error, then delete .dl file
            printf("File Write Failed\n");
            remove(filename);
            close(fdw);
            goto RECONNECT;
        }
    }

    // close
    close(skt_clt);

    return 0;
}
