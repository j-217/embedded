/*
 * @Description: A simple blog client
 * @version: 1.0.0
 * @Author: ru_j
 * @Date: 2019-12-31 11:27:20
 * @LastEditors  : ru_j
 * @LastEditTime : 2020-01-02 10:18:43
 */
#include "my_clt.h"

int main(void)
{
    // init variables
    int skt_clt = -1;                                           // client socket
    int res = -1;                                               // result
    struct sockaddr_in serv_addr_s;                             // server address struct
    socklen_t addr_s_len = sizeof(struct sockaddr_in);          // length of struct server address

    int opt = -1;                                               // client option
    clt_data n_clt_data;                                        // client data
    unsigned long clt_data_len = sizeof(clt_data);              // length of struct client data
    bzero(&n_clt_data, clt_data_len);                       
    serv_data n_srv_data;                                       // struct server data
    unsigned long srv_data_len = sizeof(serv_data);             // length of struct server data
    bzero(&n_srv_data, srv_data_len);

    int logged_flag = 0;                                        // login flag
    struct termios n_term_setting, bakup_term_setting;          // new termios setting, backup termios setting

/*------------------------set hidden and display input------------------------------------------------*/

    res = tcgetattr(0, &bakup_term_setting);
    if(res == -1){
        perror("[ERROR] Getting Termios Attr");
        return ERROR_S;
    }
    n_term_setting = bakup_term_setting;
    n_term_setting.c_lflag &= ~ECHO;                            // hidden input 


/*------------------------set end---------------------------------------------------------------------*/


    // socket
    skt_clt = socket(AF_INET, SOCK_STREAM, 0);
    if(skt_clt == -1){
        perror("[ERROR] Client Socket");
        return ERROR_S;
    }

    // server sockaddr_in
    bzero(&serv_addr_s, addr_s_len);
    serv_addr_s.sin_family = AF_INET;
    serv_addr_s.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_ADDR, &serv_addr_s.sin_addr.s_addr);

    // connect
    res = connect(skt_clt, (struct sockaddr *)&serv_addr_s, addr_s_len);
    if(res == -1){
        perror("[ERROR] Client Connect");
        return ERROR_S;
    }

    printf("[INFO] Connect Successful\n");

    while(1){        
        printf("+--------MENU--------+\n");
        printf("|  1: Login          |\n");
        printf("|  2: Logout         |\n");
        printf("|  3: Signup         |\n");
        printf("|  4: Show           |\n");
        printf("|  5: Publish        |\n");
        printf("|  6: ShowMine       |\n");
        printf("| -1: Exit           |\n");
        printf("+--------------------+\n");
        printf("| Choose One Option  |\n");
        printf("+--------------------+\n");        
        scanf("%d", &opt);
        while(getchar() != '\n'){
            continue;
        }
        switch(opt){
/*--------------------------------handle login----------------------------------------------------*/
            case 1:
                if(logged_flag){
                    printf("[INFO] Already Logged In\n");
                    continue;
                }

                bzero(&n_clt_data, clt_data_len);
                n_clt_data.opt = 1;                                             // set client data
                printf("[INFO] Username: ");
                scanf("%s", n_clt_data.username);
                while(getchar() != '\n'){
                    continue;
                }

                res = tcsetattr(0, TCSANOW, &n_term_setting);                   // set hidden input
                if(res == -1){
                    perror("[ERROR] Setting Termios Attr Hidden");
                    return ERROR_S;
                }

                printf("[INFO] Password: ");
                scanf("%s", n_clt_data.password);
                while(getchar() != '\n'){
                    continue;
                }

                printf("\n");
                res = tcsetattr(0, TCSANOW, &bakup_term_setting);               // reset display input
                if(res == -1){
                    perror("[ERROR] Setting Termios Attr Display");
                    return ERROR_S;
                }

                clt_send_recv(skt_clt, &n_clt_data, &n_srv_data);

                if(n_srv_data.status == LOGIN_OK){                              // login
                    logged_flag = 1;
                }
                
                break;

/*--------------------------------handle end------------------------------------------------------*/

/*--------------------------------handle logout---------------------------------------------------*/ 
            case 2:
                logged_flag = 0;
                printf("[INFO] Logout\n");
                
                break;
/*--------------------------------handle end------------------------------------------------------*/

/*--------------------------------handle signup---------------------------------------------------*/ 
            case 3:
                if(logged_flag){
                    printf("[INFO] Logout First\n");
                    continue;
                }
                bzero(&n_clt_data, clt_data_len);
                n_clt_data.opt = 3;                                                 // set client data

AGAIN_USERNAME:
                printf("[INFO] New Username: ");
                scanf("%s", n_clt_data.username);
                while(getchar() != '\n'){
                    continue;
                }

                if(strlen(n_clt_data.username) < 3){
                    printf("[ERROR] Username must have at least three charactors\n");
                    goto AGAIN_USERNAME;
                }

                res = tcsetattr(0, TCSANOW, &n_term_setting);                       // set hidden input
                if(res == -1){
                    perror("[ERROR] Setting Termios Attr Hidden");
                    return ERROR_S;
                }
AGAIN_PASSWORD:
                printf("[INFO] New Password: ");
                scanf("%s", n_clt_data.password);
                while(getchar() != '\n'){
                    continue;
                }

                if(strlen(n_clt_data.password) < 1){
                    printf("[ERROR] Username must have at least one single charactor\n");
                    goto AGAIN_PASSWORD;
                }

                printf("\n");
                res = tcsetattr(0, TCSANOW, &bakup_term_setting);                   // reset display input
                if(res == -1){
                    perror("[ERROR] Setting Termios Attr Display");
                    return ERROR_S;
                }

                clt_send_recv(skt_clt, &n_clt_data, &n_srv_data);                   // send and receive
                
                break;
/*--------------------------------handle end------------------------------------------------------*/

/*--------------------------------handle show-----------------------------------------------------*/ 
            case 4:
                if(!logged_flag){
                    printf("[INFO] Please Login\n");
                    continue;
                }
                n_clt_data.opt = 4;

                clt_send_recv(skt_clt, &n_clt_data, &n_srv_data);                   // send and receive

                print_tbl_res(&n_srv_data);
                
                break;
/*--------------------------------handle end------------------------------------------------------*/

/*--------------------------------handle publish--------------------------------------------------*/ 
            case 5:
                if(!logged_flag){
                    printf("[INFO] Please Login\n");
                    continue;
                }
                n_clt_data.opt = 5;

                bzero(n_clt_data.title, TITLE_SIZE);                                // reset title, content buffer
                bzero(n_clt_data.content, CONTENT_SIZE);

AGAIN_TITLE:
                printf("[INFO] Title: ");
                scanf("%s", n_clt_data.title);
                while(getchar() != '\n'){
                    continue;
                }

                if(strlen(n_clt_data.title) < 1 || strlen(n_clt_data.title) >100){
                    printf("[ERROR] Length of title is 1-100\n");
                    goto AGAIN_TITLE;
                }

AGAIN_CONTENT:
                printf("[INFO] Content: \n");
                fflush(stdin);
                fgets(n_clt_data.content, CONTENT_SIZE, stdin);
                n_clt_data.content[strlen(n_clt_data.content) - 1] = '\0';

                if(strlen(n_clt_data.content) < 1 || strlen(n_clt_data.content) > 1000){
                    printf("[ERROR] Length of content is 1-1000\n");
                    goto AGAIN_CONTENT;
                }

                clt_send_recv(skt_clt, &n_clt_data, &n_srv_data);                   // send and receive
                
                break;
/*--------------------------------handle end------------------------------------------------------*/

/*--------------------------------handle show mine------------------------------------------------*/ 
            case 6:
                if(!logged_flag){
                    printf("[INFO] Please Login\n");
                    continue;
                }
                n_clt_data.opt = 6;

                clt_send_recv(skt_clt, &n_clt_data, &n_srv_data);                   // send and receive

                print_tbl_res(&n_srv_data);
                
                break;
/*--------------------------------handle end------------------------------------------------------*/

            case -1:
                printf("[INFO] Client Disconnected\n");
                close(skt_clt);
                return 0;
                break;

            default:
                printf("[ERROR] Invalid Option, Try Again\n");
                continue;
                break;
        }
    }
    // close
    close(skt_clt);

    return 0;
}
