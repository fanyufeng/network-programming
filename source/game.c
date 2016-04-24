//程序框架
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include"game_global.h"
#include"game_basic.h"
#include"game_process.h"

//#define BUFFER_SIZE 1024



typedef struct Transport{
		uint32_t  server_ip;
		uint16_t server_port;
		uint32_t client_ip;
		uint16_t client_port;
		
}TransportAddr,*TransportA;



int main(int argc ,char **argv)

{
	GAME_PARAM GameParam;

	TransportAddr cs;

	if(argc != 6)
	{
		printf("please input the ip message again !");
		return -1;
	}

	//初始化，主要是自身信息
	GameInit(&GameParam);

	GameParam.uId=atoi(argv[5]);

	cs.client_ip=inet_addr(argv[3]);
	cs.client_port=htons(atoi(argv[4]));
	cs.server_ip=inet_addr(argv[1]);
	cs.server_port=htons(atoi(argv[2]));

	

	
	
	
	// 创建socket，若成功，返回socket描述符

	client_socket_fd = socket(AF_INET,SOCK_STREAM,0);
	
	if(client_socket_fd < 0) 
	{ 
		perror("Create Socket Failed:"); 
		return -1; 
	} 

	// 声明并初始化一个客户端的socket地址结构 
	struct sockaddr_in client_addr; 
	bzero(&client_addr, sizeof(client_addr)); 
	client_addr.sin_family = AF_INET; 
	client_addr.sin_addr.s_addr = cs.client_ip; 
	client_addr.sin_port = cs.client_port;
	
	// 绑定客户端的socket和客户端的socket地址结构 
	if(-1 == (bind(client_socket_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)))) 
	{ 
		perror("Client Bind Failed:"); 
		return  -1; 
	} 

	

	
	// 声明一个服务器端的socket地址结构，并用服务器那边的IP地址及端口对其进行初始化，用于后面的连接 
	struct sockaddr_in server_addr; 
	bzero(&server_addr, sizeof(server_addr)); 
	server_addr.sin_family = AF_INET; 
	server_addr.sin_addr.s_addr =cs.server_ip;
	server_addr.sin_port = cs.server_port; 
	socklen_t server_addr_length = sizeof(server_addr); 

	// 向服务器发起连接，连接成功后client_socket_fd代表了客户端和服务器的一个socket连接 
	while(connect(client_socket_fd, (struct sockaddr*)&server_addr, server_addr_length) < 0) 
	{ 
		usleep(100*1000);
	} 

	printf("connect success !!!\n");
	//向server发送reg-msg，注册自己的id和name
	

	char BufferRegister[BUFFER_SIZE];                //发送注册消息缓冲区
	char BufferRecv[BUFFER_SIZE];					 //接收消息缓冲区
    

	
	int mn;
	char *namespace="ThreeStooges";
	strcpy(GameParam.Name,namespace);
	mn= sprintf(BufferRegister,"reg:%d %s need_notify \n",GameParam.uId,GameParam.Name);
	printf("%s\n",BufferRegister);  
    
	// 向服务器发送buffer中的数据 
	if(send(client_socket_fd,BufferRegister,BUFFER_SIZE, 0) < 0) 
	{ 
		perror("Send File Name Failed:"); 
		return -1; 
	} 
	bzero(BufferRegister,BUFFER_SIZE);
	bzero(BufferRecv,BUFFER_SIZE);
	printf("send success!!!\n");
  while( GameParam.uPlayerNum >= 2 && GameParam.uGameNum <= 600 )
  {
    	char *p2;
		bzero(BufferRecv,BUFFER_SIZE);
		int rec =recv(client_socket_fd,BufferRecv,BUFFER_SIZE,0);
		printf("recv sucess!!!\n");
		printf("%s\n",BufferRecv);
		
		if((p2=strstr(BufferRecv,"pot-win/ "))!=NULL)
		{
			p2 += strlen("pot-win/ ");
			DealPotwin(p2,&GameParam);                             //server 发布的谈拍消息
			GamePotwin(&GameParam);
			printf("pot-win success !!1");
		}
		
		if((p2=strstr(BufferRecv,"seat/ "))!=NULL)
		{
			p2 += strlen("seat/ ");
			DealSeat(p2,&GameParam);			//座位信息提取
			printf("DealSeat success !!!!");
			GameSeat(&GameParam);
			
			printf("seat success !!!\n");
			printf("%d\n",GameParam.button_message.pid);
		}
		
		
	    if((p2=strstr(BufferRecv,"blind/ "))!=NULL)
		{
			p2 += strlen("blind/ ");                    //server 发布盲注玩家自动扣除盲注金额
			DealBlind(p2,&GameParam);
			GameBlind(&GameParam);
			printf("blind recv sucess !!\n");
		}
	    if((p2=strstr(BufferRecv,"game-over "))!=NULL)
		{
			p2 += strlen("game-over ");
			GameParam.uGameState = GAME_END;                     
		}
		if((p2=strstr(BufferRecv,"hold/ "))!=NULL)
		{
			p2 += strlen("hold/ "); 
			DealHold(p2,&GameParam);                                 //服务器发布授牌消息
			GameHold(&GameParam);
			printf("hold recv sucesss!!!\n");
		}
		if((p2=strstr(BufferRecv,"flop/ "))!=NULL)     
		{
			if(GameParam.uGameState!=GAME_COMPLETE)
			{
				p2 += strlen("flop/ ");
				DealFlop(p2,&GameParam);                                //发放的公共排情况
				GameFlop(&GameParam);
			}
		}
		if((p2=strstr(BufferRecv,"turn/ "))!=NULL) 
		{
			if(GameParam.uGameState!=GAME_COMPLETE)
			{
				p2 += strlen("turn/ ");
				DealTurn(p2,&GameParam);                                 //server 发布的转牌消息
				GameTurn(&GameParam);
			}
		}
		if((p2=strstr(BufferRecv,"river/ "))!=NULL)
		{
			if(GameParam.uGameState!=GAME_COMPLETE)
			{
				p2 += strlen("river/ ");
				DealRiver(p2,&GameParam);                               //server 发布的河牌消息
				GameRiver(&GameParam);
			}
		}
		if((p2=strstr(BufferRecv,"inquire/ "))!=NULL)
		{
			p2 += strlen("inquire/ ");
			DealInquire(p2,&GameParam);                            //server 向player 询问行动决策包括其他玩家的决策情况
			GameInquire(&GameParam);
			printf("GameInquire sucess!!!!\n");
		}		
		if((p2=strstr(BufferRecv,"shutdown/ "))!=NULL)
		{

			p2 += strlen("shutdown/ ");
			//不用处理
			//DealShutdown(p2);                            //server 发布的谈拍消息
			GameShowdown(&GameParam);
		} 

		
		if( GameParam.uGameState == GAME_END )
		{
			printf("game_over close");
			break;
		}
		
	  }
  
 	close(client_socket_fd); 
	printf("socket close !!!!");

	
	return 0;
} 
