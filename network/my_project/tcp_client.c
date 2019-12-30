/*************************************************************************
    > File Name: tcp_client.c
    > Author: shxh
    > Mail: shxh@hqyj.com 
    > Created Time: Wed 25 Dec 2019 04:21:22 PM CST
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define BUF_SIZE 5
int main()
{
	//socket
	int iClient=socket(AF_INET,SOCK_STREAM,0);
	if(-1==iClient)
	{
		return -1;
	}
	printf("socket ok\r\n");
	//connect
	struct sockaddr_in stServer;
	stServer.sin_family=AF_INET;
	stServer.sin_port=htons(56789);
	stServer.sin_addr.s_addr=inet_addr("127.0.0.1");
	int ret=connect(iClient,(struct sockaddr *)&stServer,sizeof(struct sockaddr_in));
	if(-1==ret)
	{
		return -1;
	}
	printf("connect ok\r\n");
	//send
	while(1){
		char buf[BUF_SIZE]={0};

		memset(buf, 0, BUF_SIZE);
		fgets(buf,BUF_SIZE,stdin);
		buf[strlen(buf)-1] = '\0';
		ret=write(iClient,buf,BUF_SIZE);
		if(-1==ret)
		{
			printf("send data error\r\n");
		}
		printf("send ok,ret=%d\r\n",ret);
		//recv
		char r_buf[BUF_SIZE] = {0};
		memset(r_buf,0,BUF_SIZE);
		ret=recv(iClient,r_buf,strlen(r_buf), 0);
		if(-1==ret)
		{
			printf("recv error\r\n");
		}
		printf("recv ok,ret=%d %s\r\n",ret,r_buf);
	}
	
	close(iClient);
	return 0;
}
