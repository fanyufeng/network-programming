#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "game_global.h"
#include "game_basic.h"
#include "game_process.h"



#define BUFFER_SIZE1 1024
#define BUFFER_SIZE2 100

void GameInit( PGAME_PARAM pGameParam )
{
	pGameParam->uPlayerNum = 8;
	pGameParam->uGameNum = 0;
	pGameParam->uGameState = GAME_START;
	memset(pGameParam->uCard,0,sizeof(pGameParam->uCard));
}

//处理座次消息
void DealSeat(char *ptr,PGAME_PARAM pGameParam)
{
	char *p1;
	char str[128]={0};
	int i=0;

	pGameParam->uPlayerNum=0;

	memset(&pGameParam->button_message,0,sizeof(pGameParam->button_message));
	memset(&pGameParam->small_blind_message,0,sizeof(pGameParam->small_blind_message));
	memset(&pGameParam->big_blind_message,0,sizeof(pGameParam->big_blind_message));
	memset(&pGameParam->common_message1,0,sizeof(pGameParam->common_message1));
	memset(&pGameParam->common_message2,0,sizeof(pGameParam->common_message2));
	memset(&pGameParam->common_message3,0,sizeof(pGameParam->common_message3));
	memset(&pGameParam->common_message4,0,sizeof(pGameParam->common_message4));
	memset(&pGameParam->common_message5,0,sizeof(pGameParam->common_message5));


	//提取庄家信息
	if ((p1=strstr(ptr,"button: "))!=NULL)
	{

		p1 += strlen("button: ");
		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->button_message.pid=atoi(str);
		pGameParam->uPlayerNum++;
		printf("button pid %d\n",pGameParam->button_message.pid);

		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->button_message.jetton=atoi(str);
		printf("button jetton %d\n",pGameParam->button_message.jetton);

		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->button_message.money=atoi(str);
		printf("button money %d\n",pGameParam->button_message.money);
		bzero(str,128);
		i=0;
	}
	//提取小盲注玩家信息

	if ((p1=strstr(ptr,"small blind: "))!=NULL)
	{
		p1 += strlen("small blind: ");

		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		str[i]='\0';
		pGameParam->small_blind_message.pid=atoi(str);
		pGameParam->uPlayerNum++;
		printf("small blind pid %d\n",pGameParam->small_blind_message.pid);

		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->small_blind_message.jetton=atoi(str);
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->small_blind_message.money=atoi(str);
		bzero(str,128);
		i=0;
		p1+=2;
	}	
	if(*p1=='/')
	{
		return;
	}
	printf("small_blind_message  !!!!!!\n");
	//提取大盲注玩家信息


	if ((p1=strstr(ptr,"big blind: "))!=NULL)
	{
		p1 += strlen("big blind: ");

		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->big_blind_message.pid=atoi(str);
		pGameParam->uPlayerNum++;
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->big_blind_message.jetton=atoi(str);
		bzero(str,128);
		p1 +=1;
		i=0;
		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->big_blind_message.money=atoi(str);
		bzero(str,128);
		i=0;
		p1+=2;
	}	
	// 提取普通玩家1 信息
	if( *p1 != '/')
	{
		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message1.pid=atoi(str);
		pGameParam->uPlayerNum++;
		//printf("%d\n",pGameParam->common_message1.pid);

		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message1.jetton=atoi(str);
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message1.money=atoi(str);
		bzero(str,128);
		i=0;
		p1+=2;

	}
	//提取普通玩家2 信息
	if(*p1!='/')
	{

		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message2.pid=atoi(str);
		pGameParam->uPlayerNum++;
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message2.jetton=atoi(str);
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message2.money=atoi(str);
		bzero(str,128);
		i=0;
		p1+=2;
	}
	//提取普通玩家3 信息
	if(*p1!='/')
	{

		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message3.pid=atoi(str);
		pGameParam->uPlayerNum++;
		//printf("%d\n",pGameParam->common_message3.pid);
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message3.jetton=atoi(str);
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message3.money=atoi(str);
		//printf("%d\n",pGameParam->common_message3.money);
		bzero(str,128);
		i=0;
		p1+=2;

	}	
	//提取普通玩家4 信息
	if(*p1!= '/')
	{

		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message4.pid=atoi(str);
		pGameParam->uPlayerNum++;
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message4.jetton=atoi(str);;
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message4.money=atoi(str);
		//printf("%d\n",pGameParam->common_message4.money);
		bzero(str,128);
		i=0;
		p1+=2;

	}

	//提取普通玩家5 信息	
	if(*p1!='/')
	{

		while(*p1 != ' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message5.pid=atoi(str);
		pGameParam->uPlayerNum++;
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message5.jetton=atoi(str);
		bzero(str,128);
		p1 +=1;
		i=0;

		while(*p1 !=' ')
		{
			str[i]=*p1;
			i++;
			p1++;
		}
		pGameParam->common_message5.money=atoi(str);
		printf("last one money %d\n",pGameParam->common_message5.money);
		bzero(str,128);
		i=0;
		p1+=2;

	}
}


void DealBlind(char *ptrpdb,PGAME_PARAM pGameParam)
{
	pGameParam->sblind_msg.pid = 0;
	pGameParam->bblind_msg.pid = 0;

	char strpdb[128]={0};
	int i=0;
	ptrpdb +=1;
	if( *ptrpdb !='/')
	{
		while(*ptrpdb !=':')
		{
			strpdb[i]=*ptrpdb;
			i++;
			ptrpdb ++;
		}
		pGameParam->sblind_msg.pid=atoi(strpdb);

		bzero(strpdb,128);
		ptrpdb+=2;
		i=0;
		while (*ptrpdb !=' ')
		{
			strpdb[i]=*ptrpdb;
			i++;
			ptrpdb ++;
		}
		pGameParam->sblind_msg.bet=atoi(strpdb);
		bzero(strpdb,128);
		ptrpdb+=2;
		i=0;

	}

	if( *ptrpdb !='/')
	{
		while(*ptrpdb !=':')
		{
			strpdb[i]=*ptrpdb;
			i++;
			ptrpdb ++;	
		}
		pGameParam->bblind_msg.pid=atoi(strpdb);
		bzero(strpdb,128);
		ptrpdb +=2;
		i=0;
		while (*ptrpdb !=' ')
		{
			strpdb[i]=*ptrpdb;
			i++;
			ptrpdb ++;
		}
		pGameParam->bblind_msg.bet=atoi(strpdb);
		printf("big blind bet %d\n",pGameParam->bblind_msg.bet);
	}

}

int  PukePipei(char  color1,char point1 )
{

	int pain;
	switch(point1)
	{

		case 'A':  if(color1=='S') pain=0x11;
				   else if(color1=='H') pain=0x21;
				   else if(color1=='C') pain=0x31;
				   else  pain=0x41;
				   break;
		case '2':  if(color1=='S') pain=0x12;
				   else if(color1=='H') pain=0x22;
				   else if(color1=='C') pain=0x32;
				   else  pain=0x42;
				   break;
		case '3':  if(color1=='S') pain=0x13;
				   else if(color1=='H') pain=0x23;
				   else if(color1=='C') pain=0x33;
				   else  pain=0x43;
				   break;		   
		case '4':  if(color1=='S') pain=0x14;
				   else if(color1=='H') pain=0x24;
				   else if(color1=='C') pain=0x34;
				   else  pain=0x44;
				   break;
		case '5':  if(color1=='S') pain=0x15;
				   else if(color1=='H') pain=0x25;
				   else if(color1=='C') pain=0x35;
				   else  pain=0x45;
				   break;
		case '6':  if(color1=='S') pain=0x16;
				   else if(color1=='H') pain=0x26;
				   else if(color1=='C') pain=0x36;
				   else  pain=0x46;
				   break;
		case '7':  if(color1=='S') pain=0x17;
				   else if(color1=='H') pain=0x27;
				   else if(color1=='C') pain=0x37;
				   else  pain=0x47;
				   break;
		case '8':  if(color1=='S') pain=0x18;
				   else if(color1=='H') pain=0x28;
				   else if(color1=='C') pain=0x38;
				   else  pain=0x48;
				   break;
		case '9':  if(color1=='S') pain=0x19;
				   else if(color1=='H') pain=0x29;
				   else if(color1=='C') pain=0x39;
				   else  pain=0x49;
				   break;
		case '1':	if(color1=='S') pain=0x1A;
					else if(color1=='H') pain=0x2A;
					else if(color1=='C') pain=0x3A;
					else  pain=0x4A;
					break;
		case 'J':  if(color1=='S') pain=0x1B;
				   else if(color1=='H') pain=0x2B;
				   else if(color1=='C') pain=0x3B;
				   else  pain=0x4B;
				   break;
		case 'Q':  if(color1=='S') pain=0x1C;
				   else if(color1=='H') pain=0x2C;
				   else if(color1=='C') pain=0x3C;
				   else  pain=0x4C;
				   break;
		case 'K':  if(color1=='S') pain=0x1D;
				   else if(color1=='H') pain=0x2D;
				   else if(color1=='C') pain=0x3D;
				   else  pain=0x4D;
				   break;	
	}

	return pain;

}


void DealHold(char *phold,PGAME_PARAM pGameParam)
{

	HoldPa player1;
	HoldPa player2;
	char strhold[126] ={0};
	int i=0;
	phold +=1;
	if(*phold !='/')
	{
		while(*phold !=' ')
		{
			strhold[i]=*phold;
			phold++;
			i++;
		}
		player1.color=strhold[0];
		phold ++;
		i=0;

		bzero(strhold,126);
		while(*phold !=' ')
		{
			strhold[i]=*phold;
			phold++;
			i++;
		}
		player1.point=strhold[0];
		player1.pai=PukePipei(player1.color,player1.point);
		//printf("%x\n",player1.pai);
		pGameParam->hold_msg[0].card=player1.pai;
		printf("player1 pai== %x\n",pGameParam->hold_msg[0].card);
		phold +=2;
		i=0;
		bzero(strhold,126); 
	}
	if(*phold !='/')
	{
		while(*phold !=' ')
		{
			strhold[i]=*phold;
			phold++;
			i++;
		}
		player2.color=strhold[0];
		phold ++;
		i=0;

		bzero(strhold,126);
		while(*phold !=' ')
		{
			strhold[i]=*phold;
			phold++;
			i++;
		}
		player2.point=strhold[0];

		player2.pai=PukePipei(player2.color,player2.point);
		//printf("%x\n",player2.pai);
		pGameParam->hold_msg[1].card=player2.pai;
		printf("hold 2 = %x\n",pGameParam->hold_msg[1].card);
		phold +=2;
		i=0;
		bzero(strhold,126);

	}

	printf("DealHold Success\n");
}

void Stringcompare(PGAME_PARAM pGameParam,char *StringInquire,int countout)
{
	char *Stratecall="call";
	char *Stratefold="fold";
	char *Stratecheck="check";
	char *Strateallin="all_in";
	char *Strateraise="raise";
	char *Strateblind="blind";

	if((strcmp(StringInquire,Stratecall))==0)
	{
		pGameParam->inquire_msg[countout].strategy = STRATEGY_CALL;
	}
	else if((strcmp(StringInquire,Stratefold))==0)
	{
		pGameParam->inquire_msg[countout].strategy = STRATEGY_FOLD;
	}
	else if((strcmp(StringInquire,Stratecheck))==0)
	{
		pGameParam->inquire_msg[countout].strategy = STRATEGY_CHECK;
	}
	else if((strcmp(StringInquire,Strateraise))==0)
	{
		pGameParam->inquire_msg[countout].strategy = STRATEGY_RAISE;
	}
	else if((strcmp(StringInquire,Strateallin))==0)
	{
		pGameParam->inquire_msg[countout].strategy = STRATEGY_ALLIN;
	}
	else 
	{
		pGameParam->inquire_msg[countout].strategy = STRATEGY_BLIND;
	}


}	

void DealInquire(char *pask,PGAME_PARAM pGameParam)
{
	memset(pGameParam->inquire_msg,0,sizeof(pGameParam->inquire_msg));
	int CountInquire;
	char  strask[128]={0};
	int i=0;
	pask +=1;
	if (*pask !='/' && *pask != 't')
	{
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[0].pid = atoi(strask);
		printf("inquire msg 1 pid == %d\n",pGameParam->inquire_msg[0].pid);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++; 
		}
		pGameParam->inquire_msg[0].jetton= atoi(strask);
		printf("inquire 1 message %d\n",pGameParam->inquire_msg[0].jetton);

		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[0].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[0].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire=0;
		//			inquiremessage1.strategy=strcpy(strask;
		Stringcompare(pGameParam,strask,CountInquire);
		printf("inquire 1 messagestrategy %d\n",pGameParam->inquire_msg[0].strategy);
		//strcpy(pGameParam->inquire_msg[0].strategy,strask);

		//printf("%s\n",inquiremessage1.strategy);
		i=0;	
		pask +=2;		
	}
	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[1].pid = atoi(strask);
		printf("inquire 2  pid %d\n",pGameParam->inquire_msg[1].pid);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[1].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[1].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[1].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//strcpy(pGameParam->inquire_msg[1].strategy,strask);
		//			inquiremessage2.strategy= strask;
		//printf("inquire 2 strategy %s\n",pGameParam->inquire_msg[1].strategy);
		i=0;	
		pask +=2;		
	}
	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[2].pid = atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[2].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[2].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[2].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//		strcpy(pGameParam->inquire_msg[2].strategy,strask);
		//		inquiremessage3.strategy= strask;
		i=0;	
		pask +=2;		
	}
	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[3].pid = atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[3].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[3].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[3].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//strcpy(pGameParam->inquire_msg[3].strategy,strask);
		//inquiremessage4.strategy= strask;
		i=0;	
		pask +=2;		
	}

	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[4].pid = atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[4].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[4].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[4].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//	strcpy(pGameParam->inquire_msg[4].strategy,strask);
		//	inquiremessage5.strategy= strask;
		i=0;	
		pask +=2;		
	}
	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[5].pid = atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[5].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[5].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[5].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//strcpy(pGameParam->inquire_msg[5].strategy,strask);
		//inquiremessage6.strategy= strask;
		i=0;	
		pask +=2;		
	}

	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[6].pid = atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[6].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[6].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[6].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//	strcpy(pGameParam->inquire_msg[6].strategy,strask);
		//	inquiremessage7.strategy= strask;
		i=0;	
		pask +=2;		
	}
	if (*pask !='/' && *pask != 't')
	{
		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[7].pid = atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[7].jetton= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[7].money= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		pGameParam->inquire_msg[7].bet= atoi(strask);
		pask ++;
		i=0;

		bzero(strask,128);
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask ++;
			i++;
		}
		CountInquire ++;
		Stringcompare(pGameParam,strask,CountInquire);
		//	strcpy(pGameParam->inquire_msg[7].strategy,strask);
		//	inquiremessage8.strategy= strask;
		i=0;	
		pask +=2;	
	}

	if(*pask=='t')
	{
		bzero(strask,128);
		while(*pask !=':')
		{
			pask ++;
		}
		pask +=2;
		while(*pask !=' ')
		{
			strask[i]=*pask;
			pask++;
			i++;
		}
		pGameParam->total_num =atoi(strask);
		//printf("%d\n",total_num);
		pask +=2;
	}

	printf("DealInquire Success\n");


}


void DealFlop(char *pflop,PGAME_PARAM pGameParam)
{
	FlopPa flop_player1;
	FlopPa flop_player2;
	FlopPa flop_player3;
	char strflop[126] ={0};
	int i=0;
	pflop +=1;
	if(*pflop !='/')
	{
		while(*pflop !=' ')
		{
			strflop[i]=*pflop;
			pflop++;
			i++;
		}
		flop_player1.flop_color=strflop[0];
		pflop ++;
		i=0;

		bzero(strflop,126);
		while(*pflop !=' ')
		{
			strflop[i]=*pflop;
			pflop++;
			i++;
		}
		flop_player1.flop_point=strflop[0];
		flop_player1.flop_pai=PukePipei(flop_player1.flop_color,flop_player1.flop_point);
		pGameParam->flop_msg[0].card=flop_player1.flop_pai;
		printf("flop_player1flop_pai === %x\n",pGameParam->flop_msg[0].card);
		pflop +=2;
		i=0;
		bzero(strflop,126);	
	}
	if(*pflop !='/')
	{
		while(*pflop !=' ')
		{
			strflop[i]=*pflop;
			pflop ++;
			i++;
		}
		flop_player2.flop_color=strflop[0];
		pflop ++;
		i=0;

		bzero(strflop,126);
		while(*pflop !=' ')
		{
			strflop[i]=*pflop;
			pflop++;
			i++;
		}
		flop_player2.flop_point=strflop[0];

		flop_player2.flop_pai=PukePipei(flop_player2.flop_color,flop_player2.flop_point);
		pGameParam->flop_msg[1].card=flop_player1.flop_pai;
		printf("flop 2 %x\n",pGameParam->flop_msg[1].card);
		pflop +=2;
		i=0;
		bzero(strflop,126);

	}

	if(*pflop !='/')
	{
		while(*pflop !=' ')
		{
			strflop[i]=*pflop;
			pflop ++;
			i++;
		}
		flop_player3.flop_color=strflop[0];
		pflop ++;
		i=0;

		bzero(strflop,126);
		while(*pflop !=' ')
		{
			strflop[i]=*pflop;
			pflop++;
			i++;
		}
		flop_player3.flop_point=strflop[0];
		flop_player3.flop_pai=PukePipei(flop_player3.flop_color,flop_player3.flop_point);
		pGameParam->flop_msg[2].card=flop_player3.flop_pai;
		printf("flop 3 %x\n",pGameParam->flop_msg[2].card);
		pflop +=2;
		i=0;
		bzero(strflop,126);

	}	


}

void DealTurn(char *ptrturn,PGAME_PARAM pGameParam)
{
	FlopPa turn_player;
	char strturn[126]={0};
	int i=0;
	ptrturn +=1;
	if(*ptrturn !='/')
	{
		while(*ptrturn !=' ')
		{
			strturn[i]=*ptrturn;
			ptrturn ++;
			i++;
		}
		turn_player.flop_color = strturn[0];
		ptrturn ++;
		i=0;

		bzero(strturn,128);
		while(*ptrturn != ' ')
		{
			strturn[i]=*ptrturn;
			ptrturn ++;
			i++;
		}
		turn_player.flop_point = strturn[0];
		turn_player.flop_pai=PukePipei(turn_player.flop_color,turn_player.flop_point);
		pGameParam->turn_msg.card=turn_player.flop_pai;
		printf("turn_msg ==%x\n",pGameParam->turn_msg.card);
	}


}

void DealRiver(char *ptrriver,PGAME_PARAM pGameParam)
{


	FlopPa river_player;
	char strri[126]={0};
	int i=0;
	ptrriver +=1;
	if(*ptrriver !='/')
	{
		while(*ptrriver !=' ')
		{
			strri[i]=*ptrriver;
			ptrriver ++;
			i++;
		}
		river_player.flop_color = strri[0];
		ptrriver ++;
		i=0;

		bzero(strri,126);
		while(*ptrriver != ' ')
		{
			strri[i]=*ptrriver;
			ptrriver ++;
			i++;
		}
		river_player.flop_point = strri[0];
		river_player.flop_pai=PukePipei(river_player.flop_color,river_player.flop_point);
		pGameParam->river_msg.card=river_player.flop_pai;
		printf("river_player ==%x\n",pGameParam->river_msg.card);
	}

}

void DealPotwin(char *ptrpot,PGAME_PARAM pGameParam)
{
	char strpot[126]={0};
	int i=0;
	ptrpot +=1;
	
	printf("pot-win deal success!!!!!!!!!!!!!\n");
	if(*ptrpot =='/')
	{
		return;
	}
	
	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[0].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[0].num=atoi(strpot);
		printf("potwin_msg == %d\n",pGameParam->potwin_msg[0].num);
		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}


	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[1].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[1].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}

	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[2].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[2].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}

	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[3].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[3].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}

	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[4].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[4].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}

	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[5].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[5].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}
	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[6].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[6].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}

	if(*ptrpot !='/')
	{
		while(*ptrpot != ':')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;	
		}
		pGameParam->potwin_msg[7].pid=atoi(strpot);
		ptrpot +=2;
		i=0;	
		bzero(strpot,126);
		while(*ptrpot !=' ')
		{
			strpot[i]=*ptrpot;
			ptrpot ++;
			i++;
		}
		pGameParam->potwin_msg[7].num=atoi(strpot);

		ptrpot +=2;
		i=0;
		bzero(strpot,126);
	}
}

//处理seat-info-msg
void GameSeat(PGAME_PARAM pGameParam)
{
	pGameParam->uGameNum++;
	pGameParam->uCardNum = 0;
	memset(pGameParam->uStraight,0,sizeof(pGameParam->uStraight));
	memset(pGameParam->uFlushStraight,0,sizeof(pGameParam->uFlushStraight));

	pGameParam->uZhahuFlag = 0;
	pGameParam->uZhahuCarefulFlag = 0;
	pGameParam->uMustWinFlag = 0;
	pGameParam->uProbWinMaxFlag = 0;
	pGameParam->uWholeChip = 0;
	pGameParam->uLastChip = 0;
	pGameParam->uNextActiveFlag = 0;
	memset(pGameParam->uCard,0,sizeof(pGameParam->uCard));

	if(pGameParam->button_message.pid == pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->button_message.money;
		pGameParam->uSelfChip = pGameParam->button_message.jetton;
		if( pGameParam->uPlayerNum > 2 )
			pGameParam->uSeatNum = pGameParam->uPlayerNum - 2;
		else if( pGameParam->uPlayerNum == 2 )
			pGameParam->uSeatNum = pGameParam->uPlayerNum - 1;
	}
	else if(pGameParam->small_blind_message.pid ==pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->small_blind_message.money;
		pGameParam->uSelfChip = pGameParam->small_blind_message.jetton;
		if( pGameParam->uPlayerNum > 2 )
			pGameParam->uSeatNum = pGameParam->uPlayerNum - 1;
		else if( pGameParam->uPlayerNum == 2 )
			pGameParam->uSeatNum = pGameParam->uPlayerNum;
	}
	else if(pGameParam->big_blind_message.pid == pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->big_blind_message.money;
		pGameParam->uSelfChip = pGameParam->big_blind_message.jetton;
		pGameParam->uSeatNum = pGameParam->uPlayerNum;
	}
	else if(pGameParam->common_message1.pid ==pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->common_message1.money;
		pGameParam->uSelfChip = pGameParam->common_message1.jetton;
		pGameParam->uSeatNum = 1;
	}
	else if(pGameParam->common_message2.pid ==pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->common_message2.money;
		pGameParam->uSelfChip = pGameParam->common_message2.jetton;
		pGameParam->uSeatNum = 2;
	}
	else if(pGameParam->common_message3.pid ==pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->common_message3.money;
		pGameParam->uSelfChip = pGameParam->common_message3.jetton;
		pGameParam->uSeatNum = 3;
	}
	else if(pGameParam->common_message4.pid ==pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->common_message4.money;
		pGameParam->uSelfChip = pGameParam->common_message4.jetton;
		pGameParam->uSeatNum = 4;
	}
	else if(pGameParam->common_message5.pid ==pGameParam->uId)
	{
		pGameParam->uSelfGold = pGameParam->common_message5.money;
		pGameParam->uSelfChip = pGameParam->common_message5.jetton;
		pGameParam->uSeatNum = 5;
	}
	else
	{
		pGameParam->uGameState = GAME_END;
	}
	// break;	
}



//处理blind-msg
void GameBlind(PGAME_PARAM pGameParam)
{
	Uint32 Blind;

	if( pGameParam->bblind_msg.pid == 0 )
	{
		Blind = pGameParam->sblind_msg.bet;
	}
	else
	{
		Blind = pGameParam->bblind_msg.bet;
	}

	if( pGameParam->uId == pGameParam->sblind_msg.pid )
	{
		pGameParam->uLastChip = pGameParam->sblind_msg.bet;
	}
	else if( pGameParam->uId == pGameParam->bblind_msg.pid )
	{
		pGameParam->uLastChip = pGameParam->bblind_msg.bet;
	}

	pGameParam->uWholeChip += pGameParam->uLastChip;

	if( pGameParam->uSelfChip < Blind )
	{
		//如果自身金币不足以将筹码加到最大进场筹码，但我没找到最大进场筹码是哪里给的
		if( pGameParam->uSelfGold < MAX_ACCESS_JETTON - pGameParam->uSelfChip )
		{
			pGameParam->uSelfChip += pGameParam->uSelfGold;
			pGameParam->uSelfGold = 0;
		}
		//如果足够
		else
		{
			pGameParam->uSelfChip = MAX_ACCESS_JETTON;
			pGameParam->uSelfGold -= ( MAX_ACCESS_JETTON - pGameParam->uSelfChip );
		}
	}

	//如果增加筹码后仍不足盲注
	if( pGameParam->uSelfChip < Blind )
	{
		pGameParam->uGameState = GAME_END;
		return;
	}	

	//检查自身是否是大小盲注
	if( pGameParam->sblind_msg.pid == pGameParam->uId )
		pGameParam->uSelfChip -= pGameParam->sblind_msg.bet;
	else if( pGameParam->bblind_msg.pid == pGameParam->uId )
		pGameParam->uSelfChip -= pGameParam->bblind_msg.bet;
	return;
}

//处理hold-cards-msg
void GameHold(PGAME_PARAM pGameParam)
{
	Uint8 i;
	Uint8 card1,card2;

	for( i=0; i<2; i++ )
	{
		NewAddToCard(pGameParam->hold_msg[i].card,pGameParam);
	}

	card1=GetValue(pGameParam->hold_msg[0].card)==1?pGameParam->hold_msg[0].card+13:pGameParam->hold_msg[0].card;
	card2=GetValue(pGameParam->hold_msg[1].card)==1?pGameParam->hold_msg[1].card+13:pGameParam->hold_msg[1].card;

	if(card1>=card2)
	{
		pGameParam->uSelfCard[0] = card1;
		pGameParam->uSelfCard[1] = card2;
	}
	else
	{
		pGameParam->uSelfCard[1] = card2;
		pGameParam->uSelfCard[0] = card1;		
	}

	CardStatByValue(pGameParam);
	CardStatByFlush(pGameParam);
	CardStatByStraight(pGameParam);

	pGameParam->uGameState = GAME_PRE;
	pGameParam->uStakeTime = 0;
	pGameParam->uWholeChip += pGameParam->uLastChip;

	return;
}

//处理flop-msg
void GameFlop(PGAME_PARAM pGameParam)
{
	Uint8 i;

	for( i=0; i<3; i++ )
	{
		NewAddToCard(pGameParam->flop_msg[i].card,pGameParam);
	}

	CardStatByValue(pGameParam);
	CardStatByFlush(pGameParam);
	CardStatByStraight(pGameParam);

	pGameParam->uWholeChip += pGameParam->uLastChip;
	pGameParam->uLastChip = 0;
	pGameParam->uGameState = GAME_FLOP;
	pGameParam->uStakeTime = 0;
	pGameParam->uZhahuFlag = 0;
	pGameParam->uNextActiveFlag = 0;

	return;
}

//处理turn-msg
void GameTurn(PGAME_PARAM pGameParam)
{
	Uint8 i;

	NewAddToCard(pGameParam->turn_msg.card,pGameParam);

	CardStatByValue(pGameParam);
	CardStatByFlush(pGameParam);
	CardStatByStraight(pGameParam);

	pGameParam->uWholeChip += pGameParam->uLastChip;
	pGameParam->uLastChip = 0;
	pGameParam->uGameState = GAME_TURN;
	pGameParam->uStakeTime = 0;
	pGameParam->uNextActiveFlag = 0;

	return;
}

//处理river-msg
void GameRiver(PGAME_PARAM pGameParam)
{
	NewAddToCard(pGameParam->river_msg.card,pGameParam);

	CardStatByValue(pGameParam);
	CardStatByFlush(pGameParam);
	CardStatByStraight(pGameParam);

	pGameParam->uWholeChip += pGameParam->uLastChip;
	pGameParam->uLastChip = 0;
	pGameParam->uGameState = GAME_RIVER;
	pGameParam->uStakeTime = 0;
	pGameParam->uNextActiveFlag = 0;

	return;
}
void SendActionMsg(char *sendbuf,int number)
{
	char BufferSendDec[BUFFER_SIZE2];                 //发送决策消息缓冲区
	bzero(BufferSendDec,BUFFER_SIZE2);
	char *sendf ="raise";
	if((strcmp(sendbuf,sendf))==0 )
	{
		int mnt;
		mnt= sprintf(BufferSendDec,"%s %d \n",sendbuf,number);		
		// 向服务器发送buffer中的数据 
		printf("sendbuf = %s\n",sendbuf);
		if(send(client_socket_fd,BufferSendDec,BUFFER_SIZE2, 0) < 0) 
		{ 
			printf("Send File Name Failed:"); 
			//return -1; 
		} 
		printf("BufferSendDec = %s\n",BufferSendDec);

	}
	else
	{
		int mnt;
		mnt= sprintf(BufferSendDec,"%s \n",sendbuf);
		printf("send neirong %s\n",sendbuf);
		//printf("sendbuf = %s\n",sendbuf);
		// 向服务器发送buffer中的数据 
		if(send(client_socket_fd,BufferSendDec,BUFFER_SIZE2, 0) < 0) 
		{ 
			printf("Send File Name Failed:");  
		} 
		printf("BufferSendDec = %s\n",BufferSendDec);
		//printf("huiying success !!!!");
		//memset(BufferSendDec,0,BUFFER_SIZE);
	}

}
void Strategy_Action(PGAME_PARAM pGameParam,Uint32 maxchip,Uint8 rivalnum)
{
	Uint32 uRaiseJetton;
	printf("strategy_action!!!!!!!!!!!!!!!!!!!!\n");

	if(pGameParam->uRaiseNum<maxchip)  //判断一下   弥补已经压了很多却又要弃掉的情况
	{ 
		if(pGameParam->uMustWinFlag==1)//一般情况下 这里不会是this_chip<maxchip， 但还是排除一下
		{
			pGameParam->uRaiseNum=maxchip;
		}

		if(pGameParam->uProbWinMaxFlag==1)//一般情况下 这里不会是this_chip<maxchip， 但还是排除一下
		{
			if( random_rate(103,pGameParam->uModelValue/72) )
				pGameParam->uRaiseNum=maxchip;
		}

		if( pGameParam->uZhahuFlag==1  ) //是不是不用判断I_am_Alive 因为能够近来判断就证明之前没有弃牌    一般情况下 这里不会是this_chip<maxchip， 但还是排除一下 
		{
			if( (maxchip-pGameParam->uLastChip< pGameParam->uSelfChip*12/100) || (    pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*90/100    )   )
			{
				pGameParam->uRaiseNum=maxchip;
			}
			else if(maxchip-pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //概率加和的关系 所以定的小一些吧
				// if( random_fun(77,100) )
				// this_chip=maxchip;
				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
					// if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(100,57) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 202,7)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(7));//概率很低的
					}
				}
			}
			else 
			{  
				if(random_rate(103,pGameParam->uModelValue/72))//pGameParam->uModelValue这里也应该能调用！！
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //概率加和的关系
				//if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(100,37) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 520,7)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(7));//概率很低的
					}
				}
			}
		}

		if( pGameParam->uZhahuCarefulFlag==1 ) //是不是不用判断I_am_Alive 因为能够近来判断就证明之前没有弃牌    一般情况下 这里不会是this_chip<maxchip， 但还是排除一下 
		{      //pGameParam->uLastChip < pGameParam->uSelfChip
			if( (maxchip-pGameParam->uLastChip< pGameParam->uSelfChip*12/100) || (    pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*90/100    )   )
			{
				pGameParam->uRaiseNum=maxchip;
			}
			else if(maxchip-pGameParam->uLastChip < pGameParam->uSelfChip*25/100 )
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //概率加和的关系 所以定的小一些吧
				// if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(103,pGameParam->uModelValue/72) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 520,1)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1; 
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(7));//概率很低的
					}
				}
			}

		}








		if(  pGameParam->uWholeChip>(pGameParam->uWholeChip + pGameParam->uSelfChip)*90/100 )  //maxchip指的是这一压注圈增加的最大的那笔钱 my_chip_in也指的是这一圈压了的多少钱
		{
			if(maxchip - pGameParam->uLastChip < pGameParam->uSelfChip*12/100)    // || (    my_chip_in_whole>(my_chip_in_whole+my_chip_left)*90/100    )
			{
				pGameParam->uRaiseNum=maxchip;
			}
			else if( maxchip- pGameParam->uLastChip < pGameParam->uSelfChip* 25/100)
			{  
				if( random_rate(maxchip+1,pGameParam->uLastChip+21) )
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //概率加和的关系 所以定的小一些吧
				// if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(100,57) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 127,5)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(5));//概率很低的
					}
				}
			}
			else 
			{  
				if(  random_rate(maxchip+1,pGameParam->uLastChip+7 ) )
					pGameParam->uRaiseNum=maxchip;

				//if( rival_alive<=2 )    //概率加和的关系
				//if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(100,27) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 277,5)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{ 
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(5));//概率很低的
					}
				}
			}
		}  


		if(  pGameParam->uWholeChip >(pGameParam->uWholeChip + pGameParam->uSelfChip)*70/100)  //maxchip指的是这一压注圈增加的最大的那笔钱 my_chip_in也指的是这一圈压了的多少钱
		{
			if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*12/100)
			{
				pGameParam->uRaiseNum=maxchip;

				//if( rival_alive<=2 )    //概率加和的关系
				//if( random_fun(77,100) )
				//this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系

				{
					if( random_rate(100,27) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 572,5)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(3));//概率很低的

				}

			} 
			// pGameParam->uWholeChip >(pGameParam->uWholeChip + pGameParam->uSelfChip)
			else if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip+12))
					pGameParam->uRaiseNum=maxchip;

					// if( rival_alive<=2 )    //概率加和的关系
					// if( random_fun(67,100) )
					// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(100,17) )
						pGameParam->uRaiseNum=maxchip;
					if( random_rate( 772,5)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(3));//概率很低的
					}
				}

			}
			else 
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip))
					pGameParam->uRaiseNum=maxchip;
				// if( rival_alive<=2 )    //概率加和的关系
				// if( random_fun(57,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{ 
					if( random_rate(100,12) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 125,0) &&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(3));//概率很低的
					}
				}

			}
		}

		else  if( pGameParam->uWholeChip >(pGameParam->uWholeChip + pGameParam->uSelfChip)*50/100) 
		{ 
			if (   random_rate( (pGameParam->uWholeChip + pGameParam->uSelfChip+1),(pGameParam->uWholeChip+52) )  )
				pGameParam->uRaiseNum=maxchip;

			//if( rival_alive<=2 )    //概率加和的关系
			// if( random_fun(37,100) )
			// this_chip=maxchip;

			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
			{
				if( random_rate(121,7) )
					pGameParam->uRaiseNum=maxchip;

				if( random_rate( 172,0)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				{
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum +=   maxchip*(1+randoma(2));//概率很低的
				}
			}

		}
		else 
		{        //modify
			if( random_rate( (pGameParam->uWholeChip + pGameParam->uSelfChip+1),(pGameParam->uWholeChip-34) ) )//考虑已经压了的 +剩余对手的情况
			{
				pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //概率加和的关系
				//if( random_fun(17,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{
					if( random_rate(112,7) )
						pGameParam->uRaiseNum=maxchip;
					//this_chip=this_chip>maxchip ? this_chip:maxchip ;

					if( random_rate( 217,0)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{ 
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(2));//概率很低的
					}
				}
			}
			//增加剩余对手数量对情况的影响！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！	
			//仅考虑剩余对手的情况	所以应该把概率定的低一些！！！！！！！！！！
			// if( rival_alive<=2 )     //概率加和的关系
			// if( random_fun(12,100) )
			// this_chip=maxchip;

			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
			{
				if( random_rate(100,17) )
					// if( random_fun(17,100) )
					pGameParam->uRaiseNum=maxchip;
				if( random_rate( 215,0)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				{ 
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum+= maxchip*(1+randoma(7));//概率很低的
				}
			}	 
		}														 
	}


	if(maxchip==pGameParam->uLastChip) //还没有人加注pGameParam->uLastChip
	{
		if(pGameParam->uRaiseNum==0) //让牌           //这里突然想到 大家都让牌的情况   自己牌较好时 如何处理
		{
			pGameParam->uStrategy = STRATEGY_CHECK;
		}
		if(pGameParam->uRaiseNum>0)
		{
			//加注 pGameParam->uRaiseNum-maxchip
			uRaiseJetton = pGameParam->uRaiseNum-pGameParam->uLastChip;
			if(uRaiseJetton > pGameParam->uSelfChip )
			{
				pGameParam->uStrategy = STRATEGY_ALLIN;
				pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
			}
			else
			{
				pGameParam->uStrategy = STRATEGY_RAISE;
			}
		}
	}


	if(maxchip>pGameParam->uLastChip) // 有人加注
	{
		if(pGameParam->uRaiseNum==0) //弃牌           //这里突然想到 大家都让牌的情况   自己牌较好时 如何处理
		{
			pGameParam->uStrategy = STRATEGY_FOLD;
		}
		if(pGameParam->uRaiseNum==maxchip) //跟牌
		{
			uRaiseJetton = maxchip - pGameParam->uLastChip;
			if(uRaiseJetton > pGameParam->uSelfChip )
			{
				pGameParam->uStrategy = STRATEGY_ALLIN;
				pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
			}
			else
			{
				pGameParam->uStrategy = STRATEGY_RAISE;
			}
		}
		if(pGameParam->uRaiseNum>maxchip)
		{
			uRaiseJetton = pGameParam->uRaiseNum-pGameParam->uLastChip;
			if(uRaiseJetton > pGameParam->uSelfChip )
			{
				pGameParam->uStrategy = STRATEGY_ALLIN;
				pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
			}
			else
			{
				pGameParam->uStrategy = STRATEGY_RAISE;
			}
		}
		//加注 my_raise_chip = pGameParam->uRaiseNum-pGameParam->uLastChip   //这里my_chip_in 指的是我本压注圈 已经压进去的

	}

	if(pGameParam->uStrategy==STRATEGY_CHECK)
	{

		char *decision="check";
		SendActionMsg(decision,0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_CALL)
	{
		char *decision="call";
		SendActionMsg(decision,0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_RAISE)
	{

		char *decision="raise";
		SendActionMsg(decision,uRaiseJetton);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_ALLIN)
	{
		char *decision ="all_in";
		SendActionMsg(decision,0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_FOLD)
	{
		char *decision ="fold";
		SendActionMsg(decision,0);
		pGameParam->uGameState = GAME_COMPLETE;
		return;
	}

	pGameParam->uLastChip = pGameParam->uRaiseNum;
	
	printf("strategy action !!!!!!!!!!!!!!!!!end!!!!!!!!!!\n");

}

//处理inquire-msg
void GameInquire(PGAME_PARAM pGameParam)
{
	Uint32 i,maxchip;
	Uint8 rivalnum;
	float maxrate;
	//Uint8 rivalnum;
	Uint32 selfbet;
	pGameParam->uCheckFlag = 0;
	pGameParam->uCallFlag = 0;
	pGameParam->uFoldFlag = 0;
	pGameParam->uRaiseFlag = 0;
	pGameParam->uAllinFlag = 0;

	pGameParam->uRaiseNum = 0;
	pGameParam->uStrategy = STRATEGY_FOLD;

	//翻牌前喊注
	printf("fanyufeng success!!!\n");
	if(pGameParam->uGameState==GAME_PRE)
	{
		printf("GAME_PRE!!!!!!\n");
		pGameParam->uPopChip = pGameParam->inquire_pop;//当前奖池注额

		maxchip = 0;
		maxrate = 0;
		rivalnum = 0;
		selfbet = 0;

		for(i=0;i<8;i++)
		{
			//遍历各玩家的投注和策略，看奇哥需要记录信息
			if(pGameParam->inquire_msg[i].bet>maxchip)
				maxchip = pGameParam->inquire_msg[i].bet;

			if(pGameParam->inquire_msg[i].pid == pGameParam->uId)
			{
				pGameParam->uSelfGold = pGameParam->inquire_msg[i].money;
				pGameParam->uSelfChip = pGameParam->inquire_msg[i].jetton;
				selfbet = pGameParam->inquire_msg[i].bet;
			}

			if( pGameParam->inquire_msg[i].pid!=pGameParam->uId
					&& pGameParam->inquire_msg[i].pid!=0
					&&(pGameParam->inquire_msg[i].strategy == STRATEGY_RAISE
						|| pGameParam->inquire_msg[i].strategy == STRATEGY_CALL
						|| pGameParam->inquire_msg[i].strategy == STRATEGY_ALLIN
						|| pGameParam->inquire_msg[i].strategy == STRATEGY_BLIND))
			{
				rivalnum++;
			}
		}

		for(i=0;i<8;i++)
		{
			if( pGameParam->inquire_msg[i].pid != pGameParam->uId && pGameParam->inquire_msg[i].pid != 0
				&& (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1)>maxrate
				&& pGameParam->inquire_msg[i].strategy != STRATEGY_FOLD
				&& (pGameParam->inquire_msg[i].bet + pGameParam->inquire_msg[i].jetton )>= ((pGameParam->uSelfChip+selfbet)/2))
				maxrate = (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1);			
		}		

		//策略选择（奇哥想想）
		if(  pGameParam->uStakeTime == 0 )
		{
			pGameParam->uStakeTime++;
			
			if( GetValue(pGameParam->uSelfCard[0])==GetValue(pGameParam->uSelfCard[1])
					&& GetValue(pGameParam->uSelfCard[0]) >= 12 )
			{
				pGameParam->uWinFlag = MUST_WIN;
			}
			else if( GetColor(pGameParam->uSelfCard[0]) == GetColor(pGameParam->uSelfCard[1])
					&& GetValue(pGameParam->uSelfCard[0]) + GetValue(pGameParam->uSelfCard[1]) >= 24 )
			{
			pGameParam->uWinFlag = MUST_WIN;
			}
			else if( GetValue(pGameParam->uSelfCard[0])==GetValue(pGameParam->uSelfCard[1])
					&& GetValue(pGameParam->uSelfCard[1]) >= 9 )
			{
				pGameParam->uWinFlag = PROB_WIN_MAX;
			}
			else if( GetColor(pGameParam->uSelfCard[0]) == GetColor( pGameParam->uSelfCard[1])
					&& (GetValue(pGameParam->uSelfCard[0]) == 14))
			{
				pGameParam->uWinFlag = PROB_WIN_MAX;
			}
			else if( GetColor(pGameParam->uSelfCard[0]) == GetColor( pGameParam->uSelfCard[1])
					&& (GetValue(pGameParam->uSelfCard[1]) >= 9) )
			{
				pGameParam->uWinFlag = PROB_WIN_MAX;
			}
			else if( GetValue(pGameParam->uSelfCard[0]) + GetValue(pGameParam->uSelfCard[1]) >= 24 )
			{
				pGameParam->uWinFlag = PROB_WIN_MAX;
			}
			else if( GetColor(pGameParam->uSelfCard[0]) != GetColor( pGameParam->uSelfCard[1])
					&& GetValue(pGameParam->uSelfCard[1]) <= 7 && GetValue(pGameParam->uSelfCard[0]) <= 13 )
			{
				pGameParam->uWinFlag = PROB_WIN_MIN;
			}
			else if( GetColor(pGameParam->uSelfCard[0]) == GetColor(pGameParam->uSelfCard[1])
					&& GetValue(pGameParam->uSelfCard[1]) == 4 && GetValue(pGameParam->uSelfCard[0]) == 9 )
			{
				pGameParam->uWinFlag = PROB_WIN_MIN;
			}
			else if( GetColor(pGameParam->uSelfCard[0]) == GetColor(pGameParam->uSelfCard[1])
					&& GetValue(pGameParam->uSelfCard[1]) < 4 && GetValue(pGameParam->uSelfCard[0]) <= 9 )
			{
				pGameParam->uWinFlag = PROB_WIN_MIN;
			}
			else
			{
				pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			}
  	
			pGameParam->uRaiseNum = 0;
			if(pGameParam->uWinFlag == MUST_WIN)
			{
				if( pGameParam->uNextActiveFlag == 0 && random_rate(2,0) )
				{	
					pGameParam->uCallFlag = 1;
					pGameParam->uRaiseNum = maxchip;
					pGameParam->uNextActiveFlag = 1;				
				}
				else
				{	
					pGameParam->uCallFlag = 1;
					pGameParam->uRaiseNum = maxchip;		
  	    	
					if(random_rate(100,50))
					{
						pGameParam->uRaiseFlag = 1;
						pGameParam->uCallFlag = 0;
						pGameParam->uRaiseNum += maxchip;
					}
					if(random_rate(100,30))
					{
						pGameParam->uRaiseFlag = 1;
						pGameParam->uCallFlag = 0;
						pGameParam->uRaiseNum += maxchip;
					}
					if(random_rate(100,10))
					{
						pGameParam->uRaiseFlag = 1;
						pGameParam->uCallFlag = 0;				
						pGameParam->uRaiseNum += maxchip;
					}
				}
			}
			else if(pGameParam->uWinFlag == PROB_WIN_MAX)
			{
				if(pGameParam->uNextActiveFlag == 0 && random_rate(2,0))
				{
					pGameParam->uCallFlag = 1;
					pGameParam->uRaiseNum = maxchip;
					pGameParam->uNextActiveFlag = 1;
				}
				else
				{
					pGameParam->uCallFlag = 1;
					pGameParam->uRaiseNum = maxchip;
  	    	
					if(random_rate(100,50))
					{
						pGameParam->uRaiseFlag = 1;
						pGameParam->uCallFlag = 0;
						pGameParam->uRaiseNum += maxchip;
					}
					if(random_rate(100,5))
					{
						pGameParam->uRaiseFlag = 1;
						pGameParam->uCallFlag = 0;
						pGameParam->uRaiseNum += maxchip;
					}
				}
			}
			else if(pGameParam->uWinFlag == PROB_WIN_MIDDLE)
			{  	
				if( pGameParam->uLastChip<BIG_BLIND && maxchip == BIG_BLIND )
				{
					pGameParam->uCallFlag = 1;
					pGameParam->uRaiseNum = maxchip;
				}
				else if( pGameParam->uLastChip==BIG_BLIND && maxchip == BIG_BLIND )
				{
					pGameParam->uCheckFlag = 1;
					pGameParam->uRaiseNum = maxchip;
				}
				else if( pGameParam->uLastChip<BIG_BLIND && maxchip < BIG_BLIND )
				{
					pGameParam->uCheckFlag = 1;
					pGameParam->uRaiseNum = maxchip;
				}
				else if(random_rate(5,3))
				{
					if( maxchip <= 6 * BIG_BLIND )
					{
						if(random_rate(2,0))
						{
							pGameParam->uCallFlag = 1;
							pGameParam->uRaiseNum = maxchip;
						}
						else
						{
							pGameParam->uRaiseFlag = 1;
							pGameParam->uRaiseNum = maxchip;							
						}
					}
					else
					{
						pGameParam->uFoldFlag = 1;
						pGameParam->uRaiseNum = 0;
					}
				}
				else
				{
					pGameParam->uFoldFlag = 1;
					pGameParam->uRaiseNum = 0;
				}
			}
			else if(pGameParam->uWinFlag==PROB_WIN_MIN)
			{
				if( pGameParam->uLastChip<BIG_BLIND && maxchip == BIG_BLIND )
				{
					pGameParam->uCallFlag = 1;
					pGameParam->uRaiseNum = maxchip;
				}
				else if( pGameParam->uLastChip==BIG_BLIND && maxchip == BIG_BLIND )
				{
					pGameParam->uCheckFlag = 1;
					pGameParam->uRaiseNum = maxchip;
				}
				else if( pGameParam->uLastChip<BIG_BLIND && maxchip < BIG_BLIND )
				{
					pGameParam->uCheckFlag = 1;
					pGameParam->uRaiseNum = maxchip;
				}
				else if(random_rate(10,2))
				{
					if( maxchip <= 3 * BIG_BLIND )
					{
						if(random_rate(2,0))
						{
							pGameParam->uCallFlag = 1;
							pGameParam->uRaiseNum = maxchip;
						}
						else
						{
							pGameParam->uRaiseFlag = 1;
							pGameParam->uRaiseNum = 2 * maxchip;							
						}
					}
					else
					{
						pGameParam->uFoldFlag = 1;
						pGameParam->uRaiseNum = 0;
					}
				}
				else
				{
					pGameParam->uFoldFlag = 1;
					pGameParam->uRaiseNum = 0;
				}
			}
  	
			if( random_rate(10,0) && pGameParam->uSeatNum >= pGameParam->uPlayerNum - 1 && pGameParam->uWinFlag != PROB_WIN_MIN )
			{
				pGameParam->uZhahuFlag = 1;
			}
		}
		else if(  pGameParam->uStakeTime >= 1 )
		{
			pGameParam->uStakeTime++;
  	
			if(pGameParam->uWinFlag == MUST_WIN)
			{
				pGameParam->uCallFlag = 1;
				pGameParam->uRaiseNum = maxchip;
  	
				if(random_rate(2,0))
				{
					pGameParam->uRaiseFlag = 1;
					pGameParam->uCallFlag = 0;
					pGameParam->uRaiseNum += maxchip;
				}
				if(random_rate(10,2))
				{
					pGameParam->uRaiseFlag = 1;
					pGameParam->uCallFlag = 0;
					pGameParam->uRaiseNum += maxchip;
				}
				if(random_rate(10,0))
				{
					pGameParam->uRaiseFlag = 1;
					pGameParam->uCallFlag = 0;
					pGameParam->uRaiseNum += maxchip;
				}
				if(random_rate(20,0))
				{
					pGameParam->uAllinFlag = 1;
					pGameParam->uRaiseFlag = 0;
					pGameParam->uCallFlag = 0;
					pGameParam->uRaiseNum = pGameParam->uLastChip + pGameParam->uSelfChip;
				}
			}
			else if(pGameParam->uWinFlag == PROB_WIN_MAX)
			{
				pGameParam->uCallFlag = 1;
				pGameParam->uRaiseNum = maxchip;
  	
				if(random_rate(2,0))
				{
					pGameParam->uRaiseFlag = 1;
					pGameParam->uCallFlag = 0;
					pGameParam->uRaiseNum += maxchip;
				}
				if( random_rate(20,0) )
				{
					pGameParam->uRaiseFlag = 1;
					pGameParam->uCallFlag = 0;
					pGameParam->uRaiseNum += maxchip;
				}
			}
			else if(pGameParam->uWinFlag == PROB_WIN_MIDDLE)
			{
				if(random_rate(5,3))
				{
					if( maxchip <= 6 * BIG_BLIND )
					{
						if(random_rate(2,0))
						{
							pGameParam->uCallFlag = 1;
							pGameParam->uRaiseNum = maxchip;
						}
						else
						{
							pGameParam->uRaiseFlag = 1;
							pGameParam->uRaiseNum = maxchip;							
						}
					}
					else
					{
						pGameParam->uFoldFlag = 1;
						pGameParam->uRaiseNum = 0;
					}
				}
				else
				{
					pGameParam->uFoldFlag = 1;
					pGameParam->uRaiseNum = 0;
				}
			}
			else if(pGameParam->uWinFlag==PROB_WIN_MIN)
			{
				if(random_rate(10,2))
				{
					if( maxchip <= 3 * BIG_BLIND )
					{
						if(random_rate(2,0))
						{
							pGameParam->uCallFlag = 1;
							pGameParam->uRaiseNum = maxchip;
						}
						else
						{
							pGameParam->uRaiseFlag = 1;
							pGameParam->uRaiseNum = 2 * maxchip;							
						}
					}
					else
					{
						pGameParam->uFoldFlag = 1;
						pGameParam->uRaiseNum = 0;
					}
				}
				else
				{
					pGameParam->uFoldFlag = 1;
					pGameParam->uRaiseNum = 0;
				}
			}
  	
			if( random_rate(10,0) && pGameParam->uSeatNum >= pGameParam->uPlayerNum - 1 && pGameParam->uWinFlag != PROB_WIN_MIN )
			{
				pGameParam->uZhahuFlag = 1;
			}
		}
		
  	if( pGameParam->uPlayerNum > 3 || pGameParam-> uPlayerNum == 2 )
  	{
			if( pGameParam->uWinFlag == MUST_WIN || pGameParam->uWinFlag == PROB_WIN_MAX )
			{
				if( pGameParam->uRaiseNum >= pGameParam->uSelfChip + pGameParam->uLastChip )
				{
					pGameParam->uStrategy = STRATEGY_ALLIN;
					pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
				}
				else if( pGameParam->uRaiseFlag == 1 )
				{
					pGameParam->uStrategy = STRATEGY_RAISE;
				}
				else
				{
					pGameParam->uStrategy = STRATEGY_CALL;
				}
			}
			else if( pGameParam->uZhahuFlag == 1 )
			{
				if( maxchip < 5 * BIG_BLIND && pGameParam->uSelfChip <= 2 * maxchip - pGameParam->uLastChip )
				{
					pGameParam->uStrategy = STRATEGY_ALLIN;
					pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
				}
				else if( maxchip < 5 * BIG_BLIND && pGameParam->uSelfChip > 2 * maxchip - pGameParam->uLastChip )
				{
					pGameParam->uStrategy = STRATEGY_RAISE;
					pGameParam->uRaiseNum = 2 * maxchip;
				}
				else
				{
					pGameParam->uRaiseNum = 0;
					pGameParam->uStrategy = STRATEGY_FOLD;
				}
			}
			else if( pGameParam->uWinFlag == PROB_WIN_MIDDLE || pGameParam->uWinFlag == PROB_WIN_MIN )
			{
				if( pGameParam->uAllinFlag == 1 )
				{
					pGameParam->uStrategy = STRATEGY_ALLIN;
					pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
				}
				else if( pGameParam->uRaiseFlag == 1 )
				{
					if( pGameParam->uRaiseNum >= pGameParam->uSelfChip + pGameParam->uLastChip )
					{
						pGameParam->uStrategy = STRATEGY_ALLIN;
						pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
					}
					else if( pGameParam->uRaiseNum < maxchip )
					{
						pGameParam->uStrategy = STRATEGY_FOLD;
						pGameParam->uRaiseNum = 0;
					}
					else if( pGameParam->uRaiseNum < 2 * maxchip )
					{
						pGameParam->uStrategy = STRATEGY_CALL;
						pGameParam->uRaiseNum = maxchip;			
					}
					else
					{
						pGameParam->uStrategy = STRATEGY_RAISE;
					}			
				}
				else if( pGameParam->uCallFlag == 1 )
				{
					if( maxchip >= pGameParam->uSelfChip + pGameParam->uLastChip )
					{
						pGameParam->uStrategy = STRATEGY_ALLIN;
						pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
					}
					else if( pGameParam->uRaiseNum < maxchip )
					{
						pGameParam->uStrategy = STRATEGY_FOLD;
						pGameParam->uRaiseNum = 0;
					}
					else
						pGameParam->uStrategy = STRATEGY_CALL;				
				}
				else if( pGameParam->uCheckFlag == 1 )
				{
					pGameParam->uStrategy = STRATEGY_CHECK;
					pGameParam->uRaiseNum = pGameParam->uLastChip;
				}
				else if( pGameParam->uFoldFlag == 1 )
				{
					pGameParam->uStrategy = STRATEGY_FOLD;
					pGameParam->uRaiseNum = 0;
				}	
			}
		}
		else
		{
			if( pGameParam->uWinFlag == MUST_WIN )
			{
				if( pGameParam->uRaiseNum >= pGameParam->uSelfChip + pGameParam->uLastChip )
				{
					pGameParam->uStrategy = STRATEGY_ALLIN;
					pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
				}
				else if( pGameParam->uRaiseFlag == 1 )
				{
					pGameParam->uStrategy = STRATEGY_RAISE;
				}
				else
				{
					pGameParam->uStrategy = STRATEGY_CALL;
				}
			}
			else if( pGameParam->uWinFlag == PROB_WIN_MAX )
			{
				if( maxchip <= 10 * BIG_BLIND )
				{
					if(random_rate(5,1))
					{
						if( pGameParam->uRaiseNum >= pGameParam->uSelfChip + pGameParam->uLastChip )
						{
							pGameParam->uStrategy = STRATEGY_ALLIN;
							pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
						}
						else if( pGameParam->uRaiseFlag == 1 )
						{
							pGameParam->uStrategy = STRATEGY_RAISE;
						}
						else
						{
							pGameParam->uStrategy = STRATEGY_CALL;
						}
					}
					else
					{
						if( maxchip >= pGameParam->uSelfChip + pGameParam->uLastChip )
						{
							pGameParam->uStrategy = STRATEGY_ALLIN;
							pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
						}				
						else
						{
							pGameParam->uStrategy = STRATEGY_CALL;
							pGameParam->uRaiseNum = maxchip;
						}
					}		
				}
				else
				{
					pGameParam->uStrategy = STRATEGY_FOLD;
					pGameParam->uRaiseNum = 0;
				}
			}
			else if( pGameParam->uZhahuFlag == 1 )
			{
				if( maxchip < 5 * BIG_BLIND && pGameParam->uSelfChip <= 2 * maxchip - pGameParam->uLastChip )
				{
					pGameParam->uStrategy = STRATEGY_ALLIN;
					pGameParam->uRaiseNum = pGameParam->uSelfChip + pGameParam->uLastChip;
				}
				else if( maxchip < 5 * BIG_BLIND && pGameParam->uSelfChip > 2 * maxchip - pGameParam->uLastChip )
				{
					pGameParam->uStrategy = STRATEGY_RAISE;
					pGameParam->uRaiseNum = 2 * maxchip;
				}
				else
				{
					pGameParam->uRaiseNum = 0;
					pGameParam->uStrategy = STRATEGY_FOLD;
				}
			}
			else if( pGameParam->uWinFlag == PROB_WIN_MIDDLE || pGameParam->uWinFlag == PROB_WIN_MIN )
			{
					pGameParam->uStrategy = STRATEGY_FOLD;
					pGameParam->uRaiseNum = 0;
			}		
		}
  	
		if(pGameParam->uStrategy==STRATEGY_CHECK)
		{
			SendActionMsg("check",0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
  	
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_CALL)
		{
			SendActionMsg("call",0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_RAISE)
		{
			SendActionMsg("raise",pGameParam->uRaiseNum-pGameParam->uLastChip);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_ALLIN)
		{
			SendActionMsg("all_in",0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_FOLD)
		{
			SendActionMsg("fold",0);
			pGameParam->uGameState = GAME_COMPLETE;
			return;
		}
		pGameParam->uLastChip = pGameParam->uRaiseNum;
	}
	
	//翻牌圈喊注
	else if(pGameParam->uGameState==GAME_FLOP)
	{
		printf("GAME_FLOP!!!!!!\n");

	pGameParam->uPopChip = pGameParam->inquire_pop;//当前奖池注额
	maxchip = 0;
	maxrate = 0;
	rivalnum = 0;
	selfbet = 0;

	for(i=0;i<8;i++)
	{
		//遍历各玩家的投注和策略，看奇哥需要记录信息
		if(pGameParam->inquire_msg[i].bet>maxchip)
			maxchip = pGameParam->inquire_msg[i].bet;

		if(pGameParam->inquire_msg[i].pid == pGameParam->uId)
		{
			pGameParam->uSelfGold = pGameParam->inquire_msg[i].money;
			pGameParam->uSelfChip = pGameParam->inquire_msg[i].jetton;
			selfbet = pGameParam->inquire_msg[i].bet;
		}

		if( pGameParam->inquire_msg[i].pid!=pGameParam->uId
				&& pGameParam->inquire_msg[i].pid!=0
				&&(pGameParam->inquire_msg[i].strategy == STRATEGY_RAISE
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_CALL
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_ALLIN
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_BLIND))
		{
			rivalnum++;
		}
	}

	for(i=0;i<8;i++)
	{
		if( pGameParam->inquire_msg[i].pid != pGameParam->uId && pGameParam->inquire_msg[i].pid != 0
				&& (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1)>maxrate
				&& pGameParam->inquire_msg[i].strategy != STRATEGY_FOLD
				&& pGameParam->inquire_msg[i].bet + pGameParam->inquire_msg[i].jetton >= (pGameParam->uSelfChip+selfbet)/2)
			maxrate = (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1);
				
	}

	if( pGameParam->uStakeTime == 0)
		strategy_flop(pGameParam);

	pGameParam->uStakeTime++;//调用策略函数先对pGameParam->uStakeTime    每一次收到新的牌要对pGameParam->uStakeTime清零

	if(pGameParam->uWinFlag == MUST_WIN) //          ->xx=win_must                                             
	{ 
		pGameParam->uMustWinFlag = 1;//这一局的标志位 出了四张牌后 若不是必赢状态了怎么办？？ 用以解决


		//不能一次加的太多，怕吓走别人	   
		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 

			pGameParam->uRaiseNum = maxchip;  //先保证至少跟注
			if(  random_rate(100,77) )
			{
				if(  random_rate(100,37) )  //modify 第一次想先套别人 uStakeTime=2时再来狠的
					pGameParam->uRaiseNum+=maxchip;

				if(  random_rate(100,27) )  //modify
					pGameParam->uRaiseNum+=maxchip*2;

				if(  random_rate(100,17) )  //modify
					pGameParam->uRaiseNum+=maxchip*2;				
			}
			else
			{
				if(  random_rate(100,77) )
				{
					if( random_rate(100,25) )  //modify
						pGameParam->uRaiseNum+=maxchip*randoma(2);
					if( random_rate(100,12) )  //modify
						pGameParam->uRaiseNum+=maxchip*(5+randoma(6));

					if( random_rate(100,7) )   //modify
						pGameParam->uRaiseNum += pGameParam->uSelfChip; // my_chip_left
				}
			}    				
		}

		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 
			pGameParam->uRaiseNum = maxchip;  //先保证至少跟注
			if(  random_rate(100,97) )
			{
				    //if(  random_rate(100,77) )                          //modify
					pGameParam->uRaiseNum+=maxchip;

				    //else if(  random_rate(100,57) )                     //modify 
				    if(  random_rate(100,77) )                     //modify 
					pGameParam->uRaiseNum+=maxchip*2;					
			}
			else
			{
				//if(  random_rate(100,57) )
				//{
					if( random_rate(100,92) )
						pGameParam->uRaiseNum+=maxchip*randoma(2);	
					else if( random_rate(100,25) )                 //modify 
						pGameParam->uRaiseNum+=maxchip*(2+randoma(3));
					if( random_rate(100,2) )                       //modify 
						pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    做出All_in之后应该不用再判断其他了吧 肯定不会再弃牌
				//} 
			}
			
			if( random_rate(107,25) )                       //modify 
			pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    做出All_in之后应该不用再判断其他了吧 肯定不会再弃牌
			
			if(pGameParam->uStakeTime>3)
			{
				pGameParam->uRaiseNum+=maxchip;
				if( random_rate(100,57) )
					pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left  
			}
		}

	}	

	if( pGameParam->uWinFlag == PROB_WIN_MAX ) //          ->xx=win_possiblebig     //很可能赢~                                         
	{    
		//不能一次加的太多，怕吓走别人

		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 
			if( random_rate(103,(pGameParam->uModelValue+520)/72))//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			{  
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//有待核对！！！！！！！！！！！！！！！！！！
					pGameParam->uRaiseNum=maxchip;  //先保证至少跟注
				else
				{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=maxchip;
					else
						pGameParam->uRaiseNum=0;
				}
				if(  random_rate(100,52) )         //modify
				{		
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//有待核对！！！！！！！！！！！！！！！！！！
					{ 
						//pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理  //modify !!!!!!!!!!
						pGameParam->uRaiseNum+=maxchip;
						if(  random_rate(100,27) )  //modify
						{
							pGameParam->uRaiseNum+=maxchip*2;
							pGameParam->uProbWinMaxFlag=1;//
						}
						if(  random_rate(100,17) )
						{
							pGameParam->uRaiseNum+=maxchip*2;
							pGameParam->uProbWinMaxFlag=1;
						}
					}
					else
					{
						if(  random_rate(103,pGameParam->uModelValue/72) )
							pGameParam->uRaiseNum+=maxchip;
					}
				}
				else
				{
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//有待核对！！！！！！！！！！！！！！！！！！
					{	
						if(  random_rate(100,37) )   //modify
						{
							if( random_rate(100,25) )//modify
							{
								pGameParam->uRaiseNum+=maxchip*randoma(2);
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
							}
							if( random_rate(5,1) )   //modify
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(6));
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
							}
							if( random_rate(77,1) )  //modify
							{
								pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
							}
						}
						//  else this_chip=this_chip;
					}
				}  
			}	  
		}

		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 

			pGameParam->uRaiseNum=maxchip;  //先保证至少跟注

			if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//有待核对！！！！！！！！！！！！！！！！！！
			{			

				if(  random_rate(100,57) )       //modify
				{
					if( random_rate(100,37) )    //modify
					{
						pGameParam->uRaiseNum+=maxchip;
						pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
					}
					if(  random_rate(100,7) )
					{
						pGameParam->uRaiseNum+=maxchip*2;
						pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
					}
				}
				else{
					if(  random_rate(100,77) )
					{
						if( random_rate(7,0) )
						{
							pGameParam->uRaiseNum+=maxchip*randoma(2),
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
						}

						if( random_rate(127,21) )
						{
							pGameParam->uRaiseNum+=maxchip*(2+randoma(3)),
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
						}

						if( random_rate(100,7)&&random_rate(103,pGameParam->uModelValue/72) )
						{ 
							pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left 
							pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理 all_in之后不用做处理吧 ？？？？？？？？
						}
					} 
				}
			}
			if(pGameParam->uStakeTime>3)
			{ 
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//有待核对！！！！！！！！！！！！！！！！！！
				{
					if( random_rate(100,21) )
						pGameParam->uRaiseNum+= pGameParam->uSelfChip; // my_chip_left  
				} 
			}

		}

	}




	//一般可能赢
	if(pGameParam->uWinFlag == PROB_WIN_MIDDLE) //  利用得到的折中后的Value值         ->xx=win_possiblenormal     //一般可能赢~                                         
	{ 

		//不能一次加的太多，怕吓走别人

		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{   
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)         //比我期望赢的大
			{  
				temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; 
				temp=temp*100/MAX_ACCESS_JETTON;
			}

			if(  random_rate(100,87-temp) )//77改为了87因为后面还会在取random_rate(103,Value/72) )呢 77是不是就太小了 ？？            可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{  
				//若randoma(7462)较费时间 可以同时比上一个数 random_rate(103,Value/72) )
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //最后要不要来一个		if(  random_fun(7462-Value,7462) )	this_chip=0; 返回权	
				{       
					pGameParam->uRaiseNum=maxchip;  //先保证至少跟注  //跟注
					if(pGameParam->uModelValue>7462*6/7)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,77) )
						{
							if(  random_rate(100,57) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,27) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //是否需要简化而删掉
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate( 103,pGameParam->uModelValue/72);
								
								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
									pGameParam->uZhahuFlag=1;//诈唬的标志位
							    }
								//if( random_fun(2,100) )
								//  this_chip= this_chip + maxchip*( 5+randoma(12) )*random_fun( pGameParam->uModelValue/72,7462/72 ); // my_chip_left
							}
							//  else this_chip=this_chip;

						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
							//if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							if( random_rate(100,37) )
								//pGameParam->uRaiseNum=0;  //先保证至少跟注 
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum : maxchip ;

							if( random_rate( 100,10)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(15));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}								 
						}

					}


					else if( pGameParam->uModelValue>7462*5/7 )    // 排名在前2/7可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,12) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //是否需要简化而删掉
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
									pGameParam->uZhahuFlag=1;//诈唬的标志位
							    }
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )   //概率加和的关系 rival_all==1 //1未算自己。
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum = pGameParam->uRaiseNum > maxchip ? pGameParam->uRaiseNum:maxchip ;

							if( random_rate( 102,7)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}										
					}


					else if(pGameParam->uModelValue>7462*5/10)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,29) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							else if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{     //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								if( random_rate(100,17) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								// if( random_fun(1,170) )
								//   this_chip= this_chip + maxchip*randoma(7)*random_rate(103,pGameParam->uModelValue/72); // my_chip_left

							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(105,2)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬 小心的标志位
							}
						}											

					}

					else
					{   //自己在后50%  要谨慎  判断对手压的的占其比重 若比我方比重大很多则认为我方要以较大概率弃疗

						//  if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						//	{
						// if( random_fun(37,100) )
						// this_chip=this_chip>maxchip ? this_chip:maxchip ;

						//	   if( random_fun( 7,100) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
						//       this_chip= this_chip + maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//概率很低的
						//	 }


						// maxchip+rival_chipleft>my_chip*1/2
						//伪代码
						//每一次压注开始时 轮到自己了，计算已跟选手总金币数比自己0.5大，情况下，他们已压注数占他们总钱数的比值
						// 最大比值*7462 与我的pGameParam->uModelValue比较 若大于1000，则~~~~~~~


						if( (maxrate*7462 > pGameParam->uModelValue +1000) || maxrate>0.92   )   //对手已压其90%的金币 证明其弃牌可能很小了
						{ 
							if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
								pGameParam->uRaiseNum=0;       //pGameParam->uFoldFlag = 1;										
						}	

						if( maxrate*7462 > pGameParam->uModelValue + 200 )   //这个就一般不太像诈唬
						{ 
							if( random_rate(103,(int)(maxrate*7462-105)/72) )
								pGameParam->uRaiseNum=0;//pGameParam->uFoldFlag = 1;
						}


						if( maxrate<0.3 )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
							if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
							{ 
								if( random_rate( 207,2)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
									pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
								}									

							}							

					}	
					
					 //modify    maxrate>0.7
					if( maxrate>0.95||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) && maxrate>0.77    )   //这个就一般不太像诈唬
					{ 
						if( random_rate(103,(int)(maxrate*7462-527)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					//else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //这个就一般不太像诈唬
					//{ 
					//	if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
						//	pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					//}		
				
				}


			}	

			//考虑是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			if(  random_rate(103,(7462-pGameParam->uModelValue)/75 )   )  //modify	 -110         //最后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
			{ pGameParam->uRaiseNum = 0; }                                  //再以这么大的概率弃疗 双层保险  这样好吗？？  降低了玩的可能！！！！！！！


			if( ( (maxrate*7462 > pGameParam->uModelValue +1000) &&   (maxrate>0.77) ) || (maxrate>0.92)  )   //对手已压其90%的金币 证明其弃牌可能很小了
			{ 
				if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
			}	

			else if( ( maxrate*7462 > pGameParam->uModelValue + 500 ) && (maxrate>0.32)     )   //这个就一般不太像诈唬  modify 
			{ 
				if( random_rate(103,(int)(maxrate*7462-155)/72 ))
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
			}

			/*
			   if( maxrate<0.3 )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
			   { 
			   if( random_rate( 100,7) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			   {
			   pGameParam->uRaiseNum+=maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//概率很低的
			   pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
			   }									

			   }	 
			   */




			//  if(  random_fun(3,100) )//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			//	{  this_chip=0; } //  7/100的概率不跟

			//最后 引入对手决策  不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
			/*	
				if(已跟对手 跟前的剩余注数大于my注数的1/2) 
				计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

				if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				if( (max_rate[x])>pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				*/



		}


		//加注两次以上要考虑 已压的和别人的压得和剩余人数情况了吧！！！！！！！
		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//比我期望赢的大
			{ temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON; }

			//已经跟了一次证明牌应该还不错  或者运气还好
			if(  random_rate(100,92-temp) )//可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{ 					
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //最后要不要来一个		if(  random_fun(7462-Value,7462) )	this_chip=0; 返回权	
				{ 
					pGameParam->uRaiseNum= maxchip;  //先保证至少跟注 //先保证至少跟注

					if(pGameParam->uModelValue>7462*6/7)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,77) )
						{
							if(  random_rate(100,27) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //是否需要简化而删掉
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+= maxchip*randoma(2) * random_rate(103,pGameParam->uModelValue/72);
									
									if( random_rate(272,5)&& random_rate(103,pGameParam->uModelValue/72) )//modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
										{
											pGameParam->uRaiseNum+=maxchip*(2+randoma(7)); // my_chip_left
											pGameParam->uZhahuFlag=1;//诈唬的标志位
										}
							}
							//  else this_chip=this_chip;

						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							if( random_rate(100,37) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum:maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(102, 7) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(3+randoma(9));   //概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/7)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,52) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else 
						{ //是否需要简化而删掉
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(127,1)&& random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(1+randoma(5)); // my_chip_left
									pGameParam->uZhahuFlag=1;//诈唬的标志位
								}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 100,2) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(8));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/10)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else{ //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								if( random_rate(100,9) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								// if( random_fun(1,170) )
								//  this_chip= this_chip + maxchip*(randoma(5))*random_rate(103,pGameParam->uModelValue/72); // my_chip_left
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,5)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}
						}											
					}

					else
					{   //自己在后50%  要谨慎  判断对手压的的占其比重 若比我方比重大很多则认为我方要以较大概率弃疗


							if( ( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate >0.52) ) || maxrate >0.95  )   //对手已压其90%的金币 证明其弃牌可能很小了
							{ 
								if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
							}	

							else if(  (maxrate*7462 > pGameParam->uModelValue + 200)&&(maxrate >0.21) || maxrate >0.75 )   //这个就一般不太像诈唬
							{ 
								if( random_rate(103,(int)(maxrate*7462-327)/72 ))
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
							}

						/*
						// maxchip+rival_chipleft>my_chip*1/2
						if(已跟对手 跟前的剩余注数大于my注数的1/2)  计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

						if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
						{ 
						if( random_fun( (max_rate[x]-215),7462) )
						this_chip=0;

						}
						if( (max_rate[x])>pGameParam->uModelValue +200  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
						{ 
						if( random_fun(max_rate[x]-327,7462) )
						this_chip=0;

						}
						*/


						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,0)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{ 
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}

						}	

					}


                     //modify    maxrate>0.7
					if( maxrate>0.9||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) || maxrate>0.7    )   //这个就一般不太像诈唬
					{ 
						if( random_rate(103,(int)(maxrate*7462-327)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //这个就一般不太像诈唬
					{ 
						if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}									 

					/*
					//最后 引入对手决策  不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
					if(已跟对手 跟前的剩余注数大于my注数的1/2) 
					计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]  实际中应rate[7]=maxchip*7462/对手总注数  先乘后除

					if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
					{ 
					if( random_fun( (max_rate[x]-215),7462) )
					this_chip=0;

					}
					else if( (max_rate[x])> pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
					{ 
					if( random_fun( (max_rate[x]-327),7462) )
					this_chip=0;

					}
					else if ((max_rate[x])> pGameParam->uModelValue)
					{ 
					if( random_fun( (max_rate[x]-pGameParam->uModelValue),7462) )
					this_chip=0;

					}
					*/



				}

			}

			if(pGameParam->uStakeTime>=3)//这是在上面已经处理后遗漏的情况下  我觉得自己已经压了很多了有必要看一下结果？？  这个地方欠考虑！！！！！！！！！！！！！！！！！！！！！！
			{ 
				if(  pGameParam->uRaiseNum == 0  )  //跟了很多次了 不能轻易放弃啊
				{ 


					if(pGameParam->uWholeChip>(pGameParam->uWholeChip+ pGameParam->uSelfChip)*70/100)  //maxchip指的是这一压注圈增加的最大的那笔钱 my_chip_in也指的是这一圈压了的多少钱
					{
						if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*12/100)
						{
							pGameParam->uRaiseNum = maxchip;//this_chip=maxchip;
						}
						else if(maxchip-pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
						{
							if(random_rate( maxchip,pGameParam->uSelfChip+10 ) )
								pGameParam->uRaiseNum = maxchip;
						}
						else 
						{  
							if(random_rate(maxchip+1,pGameParam->uSelfChip))
								pGameParam->uRaiseNum= maxchip;
						}
					}

					else  if(  pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*50/100  ) 
					{ 
						if ( random_rate( (pGameParam->uWholeChip+pGameParam->uSelfChip+1),(pGameParam->uWholeChip+52)) )
							pGameParam->uRaiseNum= maxchip;
					}
					else 
					{
						if( random_rate( (pGameParam->uWholeChip+pGameParam->uSelfChip+1) ,pGameParam->uWholeChip ) )                                                    //if( random_rate(pGameParam->uWholeChip,(pGameParam->uWholeChip+pGameParam->uSelfChip) ) )
							pGameParam->uRaiseNum= maxchip;
					}														 
				}
				else
				{
					if(  ( random_rate(103,pGameParam->uModelValue/72) ) && pGameParam->uModelValue>7462*7/12   )
					{
						pGameParam->uRaiseNum+=maxchip;
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 502,7) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}
					}

				}

			}


		}	
	}




	if(pGameParam->uWinFlag == PROB_WIN_MIN) //  利用得到的折中后的Value值         ->xx=win_possibleless     //一般可能赢~                                         
	{ 

		//不能一次加的太多，怕吓走别人

		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{  

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//比我期望赢的大
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,52-temp) )//77改为了87因为后面还会在取random_fun(pGameParam->uModelValue/72,7462/72) )呢 77是不是就太小了 ？？            可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{  
				//若randoma(7462)较费时间 可以同时比上一个数 random_fun(pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue-10)/72) )	 //很小可能赢 故比率在小一点            最 后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{       
					pGameParam->uRaiseNum = maxchip;  //跟注
					if(pGameParam->uModelValue>7462*25/100)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,57) )
						{
							if(  random_rate(100,27) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							//this_chip=this_chip+maxchip*random_fun(pGameParam->uModelValue/72,7462/72);
							/*
							   if(  random_fun(27,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);

							   if(  random_fun(17,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);	
							   */	
						}
						else
						{ // 诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,57) )
							{
								// if( random_fun(7,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(275,2)&&random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum+= maxchip*(2+randoma(7)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )	
							//if( rival_alive<= rival_all/3 || rival_all==1 )    //概率加和的关系
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,1) && random_rate(103,pGameParam->uModelValue/72)  ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=  maxchip*(2+randoma(9));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}
						}


					}


					else if(pGameParam->uModelValue>7462*2/10)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else
						{ //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,27) )
							{
								//  if( random_fun(7,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(201,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{ 
										pGameParam->uRaiseNum +=  maxchip*(2+randoma(5));// my_chip_left
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,1) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum +=   maxchip*(2+randoma(9));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;///诈唬的标志位
							}
						}				

					}

					//考虑节省效率是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					else if(pGameParam->uModelValue>7462*15/100)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=   maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    
									if( random_rate(271,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum +=   maxchip*(2+randoma(10)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;///诈唬的标志位
									}
							}
							//考虑要不要弃掉！！！！！！！！！！！！！！！！！！！！！！！！！！！1			
							//  else this_chip=this_chip;

						} 
					}

					//后15%情况下  直接弃疗
					else
					{   
					    if( random_rate(102,97)|| random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=0; 
					}



					if( maxrate >0.9  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,90 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //这个就一般不太像诈唬
					{ 
						if( random_rate(100,(int)(maxrate*100+12) )  )
							pGameParam->uRaiseNum=0;
					}
					else 
					{ 											 
						if( random_rate(100,(int)maxrate*100) )
							pGameParam->uRaiseNum=0;
					}

				}	

				//考虑是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				if(  random_rate(103,  (int)((7462-pGameParam->uModelValue)/72)  ) )	 //最后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{ pGameParam->uRaiseNum=0;}//再以这么大的概率弃疗 双层保险  这样好吗？？

			}
			//考虑屏蔽掉		
			//  if(  random_fun(3,100) )//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			//  {  this_chip=0; } //  7/100的概率不跟

			//最后 引入对手决策    对手压得很多咱们就不诈唬了！！！！！！！！！！！      不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
			/*
			   if(已跟对手 跟前的剩余注数大于my注数的1/2) 
			   计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//最后判断保证 后10%以很高的概率不玩！！
			if(pGameParam->uRaiseNum >=maxchip)
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //后10%
				{ 
					if( random_rate(   103,(int)((7462-pGameParam->uModelValue)/72)   )   )
						pGameParam->uRaiseNum=0;
				}
			}
		}


		//加注两次以上要考虑 已压的和别人的压得和剩余人数情况了吧！！！！！！！
		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//比我期望赢的大
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,77-temp) )//第二次进入了 所以应该说运气让咱们以比较高一点的概率玩下去                            77改为了87因为后面还会在取random_fun((int)pGameParam->uModelValue/72,7462/72) )呢 77是不是就太小了 ？？            可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{  
				//若randoma(7462)较费时间 可以同时比上一个数 random_fun(pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue+10)/72) )	 //很小可能赢 故比率在小一点            最 后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{       pGameParam->uRaiseNum = maxchip;  //跟注
					if(pGameParam->uModelValue>7462*25/100)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,57) )
						{
							if(  random_rate(100,27) )
								pGameParam->uRaiseNum += maxchip*random_rate(103,pGameParam->uModelValue/72);
							/*
							   if(  random_fun(27,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);

							   if(  random_fun(17,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);	
							   */	
						}
						else { // 诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,57) )
							{
								// if( random_fun(7,100) )
								// this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    
									if( random_rate(102,0)&&random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum += maxchip*(2+randoma(7)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 177,2)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum += maxchip*(2+randoma(9));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}
						}		
					}


					else if(pGameParam->uModelValue>7462*2/10)    // 排名在前8/10可以加注
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(27,100) )
							{
								//if( random_fun(7,100) )
								//this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(201,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum += maxchip*(3+randoma(9));// my_chip_left
										pGameParam->uZhahuCarefulFlag=1;///诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 207,0)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{ 
								pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位  这里有问题，上面的可能得出是0也会进入！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							}
						}	


					}

					//考虑节省效率是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					else if(pGameParam->uModelValue>7462*15/100)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(270,1) && random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
										pGameParam->uRaiseNum +=  maxchip*(5+randoma(10)); // my_chip_left
									}
							}
							//  else this_chip=this_chip;

						} 
					}







					if( maxrate >0.9  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,90 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //这个就一般不太像诈唬
					{ 
						if( random_rate(100,(int)(maxrate*100+12) )  )
							pGameParam->uRaiseNum=0;
					}
					else 
					{ 											 
						if( random_rate(100,(int)maxrate*84) )
							pGameParam->uRaiseNum=0;
					}	

				}		
				/*	
				//后15%情况下 
				//自己在后150%   判断对手压的的占其比重很大  则诈唬基本可能无效              若比我方比重大很多则认为我方要以较大概率弃疗

				// maxchip+rival_chipleft>my_chip*1/2
				//伪代码
				if(已跟对手 跟前的剩余注数大于my注数的1/2)  计算 rate[7]=maxchip*100/对手总注数   取出最大的max_rate[x]

				if( (max_rate[x])>90  )   //对手已压其90%的金币 证明其弃牌可能很小了
				{ 
				if( random_fun(90,100) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				this_chip=0;										
				}
				if( (max_rate[x])>70  )   //这个就一般不太像诈唬
				{ 
				if( random_fun(max_rate[x]+7,100) )
				this_chip=0;

				}
				else if( (max_rate[x])>50  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
				{ 
				if( random_fun(max_rate[x]+12,100) )
				this_chip=0;
				}								 
				else
				{ 
				if( random_fun(max_rate[x],100) )
				this_chip=0;
				}			
				*/


				//考虑是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				if(  random_rate(103,(7462-pGameParam->uModelValue)/72) )	 //最后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{ pGameParam->uRaiseNum=0;}//再以这么大的概率弃疗 双层保险  这样好吗？？

			}

			//  if(  random_fun(3,100) )//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			//	{  this_chip=0; } //  7/100的概率不跟

			//最后 引入对手决策    对手压得很多咱们就不诈唬了！！！！！！！！！！！      不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
			/*
			   if(已跟对手 跟前的剩余注数大于my注数的1/2) 
			   计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//最后判断保证 后10%以很高的概率不玩！！
			if(pGameParam->uRaiseNum >= maxchip)//yi Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //后10%
				{
					if( random_rate( 103,(7462-pGameParam->uModelValue)/72) )
						pGameParam->uRaiseNum=0;
				}
			}



			if(pGameParam->uStakeTime>=3)//这是在上面已经处理后遗漏的情况下  我觉得自己已经压了很多了有必要看一下结果？？  这个地方欠考虑！！！！！！！！！！！！！！！！！！！！！！
			{ 
				if(pGameParam->uRaiseNum==0) //Need Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111 //跟了很多次了 不能轻易放弃啊
				{ 

					if( pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*70/100 )  //maxchip指的是这一压注圈增加的最大的那笔钱 my_chip_in也指的是这一圈压了的多少钱
					{
						if(maxchip - pGameParam->uLastChip <  pGameParam->uSelfChip*12/100)
						{
							pGameParam->uRaiseNum=maxchip;                    //Need modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
						}
						else if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
						{  if(    random_rate(maxchip+1,(pGameParam->uWholeChip+10)  )    )
							pGameParam->uRaiseNum=maxchip;  
						}
						else 
						{  if( random_rate(maxchip+1,(pGameParam->uWholeChip) ))
							pGameParam->uRaiseNum=maxchip; 
						}
					}

					else  if(  pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*50/100) 
					{ 
						if ( random_rate( ( pGameParam->uWholeChip+pGameParam->uSelfChip+1),( pGameParam->uWholeChip+52) ) )
							pGameParam->uRaiseNum= maxchip;//modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					}
					else 
					{
						if( random_rate( ( pGameParam->uWholeChip+pGameParam->uSelfChip+1),( pGameParam->uWholeChip) ) )
							pGameParam->uRaiseNum= maxchip;//modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					}														 
				}
				else{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						pGameParam->uRaiseNum +=  maxchip;
				}

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
				{
					if( random_rate(100,37) )
						pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;

					if( random_rate( 512,1) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{  pGameParam->uZhahuCarefulFlag=1;      //bluff_flag_careful=1,//诈唬的标志位

						pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//概率很低的
					}

				}

			}					

		}	
	}

	//action 动作


	Strategy_Action(pGameParam,maxchip,rivalnum);
}		
/*
   if( pGameParam->uStakeTime == 0 )
   {
   pGameParam->uStateTime++;

//策略选择（奇哥想想）
strategy_flop(pGameParam);

if(pGameParam->uWinFlag == MUST_WIN)
{
pGameParam->uRaiseNum = 2 * maxchip;

if(random_rate(2,1))
pGameParam->uRaiseNum += maxchip;
if(random_rate(10,3))
pGameParam->uRaiseNum += maxchip;
if(random_rate(10,1))
pGameParam->uRaiseNum += maxchip;
}

}


if(pGameParam->uWinFlag == MUST_WIN)
{
pGameParam->uRaiseNum = 2 * maxchip;
pGameParam->uStrategy = STRATEGY_RAISE;
}
if(pGameParam->uWinFlag == PROB_WIN_MAX)
{
pGameParam->uRaiseNum = maxchip;
pGameParam->uStrategy = STRATEGY_RAISE;
}
else if( maxchip == 0 )
{
pGameParam->uStrategy = STRATEGY_CHECK;
}
else if(pGameParam->uWinFlag == PROB_WIN_MIDDLE)
{
pGameParam->uStrategy = STRATEGY_CALL;
}
else if(pGameParam->uWinFlag == PROB_WIN_MIN)
{
pGameParam->uStrategy = STRATEGY_FOLD;
}

if(pGameParam->uStrategy==STRATEGY_CHECK)
{
SendActionMsg("check",0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
return;
}
else if(pGameParam->uStrategy==STRATEGY_CALL)
{
SendActionMsg("call",0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
return;
}
else if(pGameParam->uStrategy==STRATEGY_RAISE)
{
SendActionMsg("raise",pGameParam->uRaiseNum);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
return;
}
else if(pGameParam->uStrategy==STRATEGY_ALLIN)
{
SendActionMsg("allin",0);//发送函数，这个函数除了第一个参数为raise的情况外，第二个参数都为0;raise情况下第二个参数为加注金额
return;
}
else if(pGameParam->uStrategy==STRATEGY_FOLD)
{
SendActionMsg("fold",0);
printf("sendmasgaction successs!!!!!\n");
pGameParam->uGameState = GAME_COMPLETE;
return;
}*/

//转牌圈喊注
else if(pGameParam->uGameState==GAME_TURN)
{
	printf("GAME_TURN !!!!!\n");
	pGameParam->uPopChip = pGameParam->inquire_pop;//当前奖池注额

	maxchip = 0;
	maxrate = 0;
	rivalnum = 0;
	selfbet = 0;

	for(i=0;i<8;i++)
	{
		//遍历各玩家的投注和策略，看奇哥需要记录信息
		if(pGameParam->inquire_msg[i].bet>maxchip)
			maxchip = pGameParam->inquire_msg[i].bet;

		if(pGameParam->inquire_msg[i].pid == pGameParam->uId)
		{
			pGameParam->uSelfGold = pGameParam->inquire_msg[i].money;
			pGameParam->uSelfChip = pGameParam->inquire_msg[i].jetton;
			selfbet = pGameParam->inquire_msg[i].bet;
		}

		if( pGameParam->inquire_msg[i].pid!=pGameParam->uId
				&& pGameParam->inquire_msg[i].pid!=0
				&&(pGameParam->inquire_msg[i].strategy == STRATEGY_RAISE
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_CALL
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_ALLIN
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_BLIND))
		{
			rivalnum++;
		}
	}

	for(i=0;i<8;i++)
	{
		if( pGameParam->inquire_msg[i].pid != pGameParam->uId && pGameParam->inquire_msg[i].pid != 0
				&& (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1)>maxrate
				&& pGameParam->inquire_msg[i].strategy != STRATEGY_FOLD
				&& (pGameParam->inquire_msg[i].bet + pGameParam->inquire_msg[i].jetton) >= ((pGameParam->uSelfChip+selfbet)/2))
				maxrate = (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1);
	}

	if( pGameParam->uStakeTime == 0)
		strategy_turn(pGameParam);

	pGameParam->uStakeTime++;//调用策略函数先对pGameParam->uStakeTime    每一次收到新的牌要对pGameParam->uStakeTime清零

	
	
    if(pGameParam->uWinFlag == MUST_WIN) //          ->xx=win_must                                             
	{ 
		pGameParam->uMustWinFlag = 1;//这一局的标志位 出了四张牌后 若不是必赢状态了怎么办？？ 用以解决


		//不能一次加的太多，怕吓走别人	   
		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 

			pGameParam->uRaiseNum += maxchip;  //先保证至少跟注
			if(  random_rate(100,77) )
			{
				if(  random_rate(100,37) )  //modify 第一次想先套别人 uStakeTime=2时再来狠的
					pGameParam->uRaiseNum+=maxchip;

				if(  random_rate(100,27) )  //modify
					pGameParam->uRaiseNum+=maxchip*2;

				if(  random_rate(100,17) )  //modify
					pGameParam->uRaiseNum+=maxchip*2;				
			}
			else
			{
				//if(  random_rate(100,77) )
				//{
					if( random_rate(100,52) )  //modify
						pGameParam->uRaiseNum+=maxchip*randoma(2);
					if( random_rate(100,37) )  //modify
						pGameParam->uRaiseNum+=maxchip*(5+randoma(6));

					if( random_rate(100,7) )   //modify
						pGameParam->uRaiseNum += pGameParam->uSelfChip; // my_chip_left
				//}
			}    				
		}

		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 
			pGameParam->uRaiseNum = maxchip;  //先保证至少跟注
			if(  random_rate(100,97) )
			{
				    //if(  random_rate(100,77) )                          //modify
					pGameParam->uRaiseNum+=maxchip;

				    //else if(  random_rate(100,57) )                     //modify 
				    if(  random_rate(100,77) )                     //modify 
					pGameParam->uRaiseNum+=maxchip*2;					
			}
			else
			{
				//if(  random_rate(100,57) )
				//{
					if( random_rate(100,92) )
						pGameParam->uRaiseNum+=maxchip*randoma(2);	
					else if( random_rate(100,25) )                 //modify 
						pGameParam->uRaiseNum+=maxchip*(2+randoma(3));
					if( random_rate(100,2) )                       //modify 
						pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    做出All_in之后应该不用再判断其他了吧 肯定不会再弃牌
				//} 
			}
			
			if( random_rate(107,52) )                       //modify 
			pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    做出All_in之后应该不用再判断其他了吧 肯定不会再弃牌
			
			if(pGameParam->uStakeTime>3)
			{
				pGameParam->uRaiseNum+=maxchip;
				if( random_rate(100,57) )
					pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left  
			}
		}

	}	

	if( pGameParam->uWinFlag == PROB_WIN_MAX ) //          ->xx=win_possiblebig     //很可能赢~                                         
	{    
		//不能一次加的太多，怕吓走别人

		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 
			if( random_rate(103,(pGameParam->uModelValue+520)/72))//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			{  
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//有待核对！！！！！！！！！！！！！！！！！！
					pGameParam->uRaiseNum=maxchip;  //先保证至少跟注
				else
				{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=maxchip;
					else
						pGameParam->uRaiseNum=0;
				}
				if(  random_rate(100,72) )         //modify
				{		
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//有待核对！！！！！！！！！！！！！！！！！！
					{ 
						//pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理  //modify !!!!!!!!!!
						pGameParam->uRaiseNum+=maxchip;
						if(  random_rate(100,27) )  //modify
						{
							pGameParam->uRaiseNum+=maxchip*2;
							pGameParam->uProbWinMaxFlag=1;//
						}
						if(  random_rate(100,17) )
						{
							pGameParam->uRaiseNum+=maxchip*2;
							pGameParam->uProbWinMaxFlag=1;
						}
					}
					else
					{
						if(  random_rate(103,pGameParam->uModelValue/72) )
							pGameParam->uRaiseNum+=maxchip;
					}
				}
				else
				{
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//有待核对！！！！！！！！！！！！！！！！！！
					{	
					    pGameParam->uRaiseNum+=maxchip;
						if(  random_rate(100,37) )   //modify
						{
							if( random_rate(100,25) )//modify
							{
								pGameParam->uRaiseNum+=maxchip*(1+randoma(5));
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
							}
							if( random_rate(5,1) )   //modify
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(6));
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
							}
							if( random_rate(77,1) )  //modify
							{
								pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
							}
						}
						//  else this_chip=this_chip;
					}
				}  
			}	  
		}

		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 

			pGameParam->uRaiseNum=maxchip;  //先保证至少跟注

			if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//有待核对！！！！！！！！！！！！！！！！！！
			{			

				if(  random_rate(100,57) )       //modify
				{   
					pGameParam->uRaiseNum+=maxchip;
					if( random_rate(100,37) )    //modify
					{
						pGameParam->uRaiseNum+=maxchip*(1+randoma(5));
						pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
					}
					if(  random_rate(100,7) )
					{
						pGameParam->uRaiseNum+=maxchip*(2+randoma(7));
						pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
					}
				}
				else{
					if(  random_rate(100,77) )
					{
						if( random_rate(7,0) )
						{
							pGameParam->uRaiseNum+=maxchip*randoma(2),
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
						}

						if( random_rate(127,21) )
						{
							pGameParam->uRaiseNum+=maxchip*(2+randoma(3)),
								pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理
						}

						if( random_rate(100,5)&&random_rate(103,pGameParam->uModelValue/72) )
						{ 
							pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left 
							pGameParam->uProbWinMaxFlag=1;//标记进入了PROB_WIN_MAX的处理 all_in之后不用做处理吧 ？？？？？？？？
						}
					} 
				}
			}
			if(pGameParam->uStakeTime>3)
			{ 
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//有待核对！！！！！！！！！！！！！！！！！！
				{
					if( random_rate(100,21) )
						pGameParam->uRaiseNum+= pGameParam->uSelfChip; // my_chip_left  
				} 
			}

		}

	}




	//一般可能赢
	if(pGameParam->uWinFlag == PROB_WIN_MIDDLE) //  利用得到的折中后的Value值         ->xx=win_possiblenormal     //一般可能赢~                                         
	{ 

		//不能一次加的太多，怕吓走别人

		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{   
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)         //比我期望赢的大
			{  
				temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; 
				temp=temp*100/MAX_ACCESS_JETTON;
			}

			if(  random_rate(100,87-temp) )//77改为了87因为后面还会在取random_rate(103,Value/72) )呢 77是不是就太小了 ？？            可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{  
				//若randoma(7462)较费时间 可以同时比上一个数 random_rate(103,Value/72) )
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //最后要不要来一个		if(  random_fun(7462-Value,7462) )	this_chip=0; 返回权	
				{       
					pGameParam->uRaiseNum=maxchip;  //先保证至少跟注  //跟注
					if(pGameParam->uModelValue>7462*6/7)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,77) )
						{
							if(  random_rate(100,57) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,27) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //是否需要简化而删掉
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate( 103,pGameParam->uModelValue/72);
								
								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
									pGameParam->uZhahuFlag=1;//诈唬的标志位
							    }
								//if( random_fun(2,100) )
								//  this_chip= this_chip + maxchip*( 5+randoma(12) )*random_fun( pGameParam->uModelValue/72,7462/72 ); // my_chip_left
							}
						
						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 || pGameParam->uPlayerNum==2 )
							//if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							if( random_rate(100,37) )
								//pGameParam->uRaiseNum=0;  //先保证至少跟注 
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum : maxchip ;

							if( random_rate( 100,10)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(15));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}								 
						}

					}


					else if( pGameParam->uModelValue>7462*5/7 )    // 排名在前2/7可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,12) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //是否需要简化而删掉
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
									pGameParam->uZhahuFlag=1;//诈唬的标志位
							    }
							}
							//  else this_chip=this_chip;

						}
						
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )   //概率加和的关系 rival_all==1 //1未算自己。
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum = pGameParam->uRaiseNum > maxchip ? pGameParam->uRaiseNum:maxchip ;

							if( random_rate( 102,7)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}										
					}


					else if(pGameParam->uModelValue>7462*5/10)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,29) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							else if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{     //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								if( random_rate(100,17) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								// if( random_fun(1,170) )
								//   this_chip= this_chip + maxchip*randoma(7)*random_rate(103,pGameParam->uModelValue/72); // my_chip_left

							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(105,2)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬 小心的标志位
							}
						}											

					}

					else
					{   //自己在后50%  要谨慎  判断对手压的的占其比重 若比我方比重大很多则认为我方要以较大概率弃疗

						//  if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						//	{
						// if( random_fun(37,100) )
						// this_chip=this_chip>maxchip ? this_chip:maxchip ;

						//	   if( random_fun( 7,100) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
						//       this_chip= this_chip + maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//概率很低的
						//	 }


						// maxchip+rival_chipleft>my_chip*1/2
						//伪代码
						//每一次压注开始时 轮到自己了，计算已跟选手总金币数比自己0.5大，情况下，他们已压注数占他们总钱数的比值
						// 最大比值*7462 与我的pGameParam->uModelValue比较 若大于1000，则~~~~~~~


						if( (maxrate*7462 > pGameParam->uModelValue +1000) || maxrate>0.92   )   //对手已压其90%的金币 证明其弃牌可能很小了
						{ 
							if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
								pGameParam->uRaiseNum=0;       //pGameParam->uFoldFlag = 1;										
						}	

						if( maxrate*7462 > pGameParam->uModelValue + 200 )   //这个就一般不太像诈唬
						{ 
							if( random_rate(103,(int)(maxrate*7462-105)/72) )
								pGameParam->uRaiseNum=0;//pGameParam->uFoldFlag = 1;
						}


						if( maxrate<0.3 )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
							if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
							{ 
								if( random_rate( 207,2)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
									pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
								}									

							}							

					}	
					
					 //modify    maxrate>0.7
					if( maxrate>0.95||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) && maxrate>0.77    )   //这个就一般不太像诈唬
					{ 
						if( random_rate(103,(int)(maxrate*7462-527)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					//else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //这个就一般不太像诈唬
					//{ 
					//	if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					//}		
				
				}


			}	

			//考虑是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			if(  random_rate(103,(7462-pGameParam->uModelValue)/75 )   )  //modify	 -110         //最后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
			{ pGameParam->uRaiseNum = 0; }                                  //再以这么大的概率弃疗 双层保险  这样好吗？？  降低了玩的可能！！！！！！！


			if( ( (maxrate*7462 > pGameParam->uModelValue +1000) &&   (maxrate>0.77) ) || (maxrate>0.92)  )   //对手已压其90%的金币 证明其弃牌可能很小了
			{ 
				if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
			}	

			else if( ( maxrate*7462 > pGameParam->uModelValue + 500 ) && (maxrate>0.32)     )   //这个就一般不太像诈唬  modify 
			{ 
				if( random_rate(103,(int)(maxrate*7462-155)/72 ))
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
			}

			/*
			   if( maxrate<0.3 )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
			   { 
			   if( random_rate( 100,7) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
			   {
			   pGameParam->uRaiseNum+=maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//概率很低的
			   pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
			   }									

			   }	 
			   */




			//  if(  random_fun(3,100) )//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			//	{  this_chip=0; } //  7/100的概率不跟

			//最后 引入对手决策  不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
			/*	
				if(已跟对手 跟前的剩余注数大于my注数的1/2) 
				计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

				if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				if( (max_rate[x])>pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				*/



		}


		//加注两次以上要考虑 已压的和别人的压得和剩余人数情况了吧！！！！！！！
		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//比我期望赢的大
			{ temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON; }

			//已经跟了一次证明牌应该还不错  或者运气还好
			if(  random_rate(100,92-temp) )//可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{ 					
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //最后要不要来一个		if(  random_fun(7462-Value,7462) )	this_chip=0; 返回权	
				{ 
					pGameParam->uRaiseNum= maxchip;  //先保证至少跟注 //先保证至少跟注

					if(pGameParam->uModelValue>7462*6/7)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,77) )
						{
							if(  random_rate(100,27) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //是否需要简化而删掉
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+= maxchip*randoma(2) * random_rate(103,pGameParam->uModelValue/72);
									
									if( random_rate(272,5)&& random_rate(103,pGameParam->uModelValue/72) )//modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
										{
											pGameParam->uRaiseNum+=maxchip*(2+randoma(7)); // my_chip_left
											pGameParam->uZhahuFlag=1;//诈唬的标志位
										}
							}
							//  else this_chip=this_chip;

						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							if( random_rate(100,37) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum:maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(102, 7) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(3+randoma(9));   //概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/7)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,52) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else 
						{ //是否需要简化而删掉
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(127,1)&& random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(1+randoma(5)); // my_chip_left
									pGameParam->uZhahuFlag=1;//诈唬的标志位
								}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 100,2) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(8));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/10)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else{ //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								if( random_rate(100,9) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								// if( random_fun(1,170) )
								//  this_chip= this_chip + maxchip*(randoma(5))*random_rate(103,pGameParam->uModelValue/72); // my_chip_left
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,5)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}
						}											
					}

					else
					{   //自己在后50%  要谨慎  判断对手压的的占其比重 若比我方比重大很多则认为我方要以较大概率弃疗


							if( ( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate >0.52) ) || maxrate >0.95  )   //对手已压其90%的金币 证明其弃牌可能很小了
							{ 
								if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
							}	

							else if(  (maxrate*7462 > pGameParam->uModelValue + 200)&&(maxrate >0.21) || maxrate >0.75 )   //这个就一般不太像诈唬
							{ 
								if( random_rate(103,(int)(maxrate*7462-327)/72 ))
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
							}

						/*
						// maxchip+rival_chipleft>my_chip*1/2
						if(已跟对手 跟前的剩余注数大于my注数的1/2)  计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

						if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
						{ 
						if( random_fun( (max_rate[x]-215),7462) )
						this_chip=0;

						}
						if( (max_rate[x])>pGameParam->uModelValue +200  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
						{ 
						if( random_fun(max_rate[x]-327,7462) )
						this_chip=0;

						}
						*/


						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,0)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{ 
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}

						}	

					}


                     //modify    maxrate>0.7
					if( maxrate>0.9||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) || maxrate>0.7    )   //这个就一般不太像诈唬
					{ 
						if( random_rate(103,(int)(maxrate*7462-327)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //这个就一般不太像诈唬
					{ 
						if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}									 

					/*
					//最后 引入对手决策  不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
					if(已跟对手 跟前的剩余注数大于my注数的1/2) 
					计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]  实际中应rate[7]=maxchip*7462/对手总注数  先乘后除

					if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
					{ 
					if( random_fun( (max_rate[x]-215),7462) )
					this_chip=0;

					}
					else if( (max_rate[x])> pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
					{ 
					if( random_fun( (max_rate[x]-327),7462) )
					this_chip=0;

					}
					else if ((max_rate[x])> pGameParam->uModelValue)
					{ 
					if( random_fun( (max_rate[x]-pGameParam->uModelValue),7462) )
					this_chip=0;

					}
					*/



				}

			}

			if(pGameParam->uStakeTime>=3)//这是在上面已经处理后遗漏的情况下  我觉得自己已经压了很多了有必要看一下结果？？  这个地方欠考虑！！！！！！！！！！！！！！！！！！！！！！
			{ 
				if(  pGameParam->uRaiseNum == 0  )  //跟了很多次了 不能轻易放弃啊
				{ 


					if(pGameParam->uWholeChip>(pGameParam->uWholeChip+ pGameParam->uSelfChip)*70/100)  //maxchip指的是这一压注圈增加的最大的那笔钱 my_chip_in也指的是这一圈压了的多少钱
					{
						if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*12/100)
						{
							pGameParam->uRaiseNum = maxchip;//this_chip=maxchip;
						}
						else if(maxchip-pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
						{
							if(random_rate( maxchip,pGameParam->uSelfChip+10 ) )
								pGameParam->uRaiseNum = maxchip;
						}
						else 
						{  
							if(random_rate(maxchip+1,pGameParam->uSelfChip))
								pGameParam->uRaiseNum= maxchip;
						}
					}

					else  if(  pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*50/100  ) 
					{ 
						if ( random_rate( (pGameParam->uWholeChip+pGameParam->uSelfChip+1),(pGameParam->uWholeChip+52)) )
							pGameParam->uRaiseNum= maxchip;
					}
					else 
					{
						if( random_rate((pGameParam->uWholeChip+pGameParam->uSelfChip+1), pGameParam->uWholeChip) )
							pGameParam->uRaiseNum= maxchip;
					}														 
				}
				else
				{
					if(  ( random_rate(103,pGameParam->uModelValue/72) ) && pGameParam->uModelValue>7462*7/12   )
					{
						pGameParam->uRaiseNum+=maxchip;
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 502,7) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//概率很低的
								pGameParam->uZhahuFlag=1;//诈唬的标志位
							}
						}
					}

				}

			}


		}	
	}




	if(pGameParam->uWinFlag == PROB_WIN_MIN) //  利用得到的折中后的Value值         ->xx=win_possibleless     //一般可能赢~                                         
	{ 

		//不能一次加的太多，怕吓走别人

		if(pGameParam->uStakeTime==1)//第一次加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{  

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//比我期望赢的大
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,52-temp) )//77改为了87因为后面还会在取random_fun(pGameParam->uModelValue/72,7462/72) )呢 77是不是就太小了 ？？            可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{  
				//若randoma(7462)较费时间 可以同时比上一个数 random_fun(pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue-10)/72) )	 //很小可能赢 故比率在小一点            最 后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{       
					pGameParam->uRaiseNum = maxchip;  //跟注
					if(pGameParam->uModelValue>7462*25/100)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,57) )
						{
							if(  random_rate(100,27) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							//this_chip=this_chip+maxchip*random_fun(pGameParam->uModelValue/72,7462/72);
							/*
							   if(  random_fun(27,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);

							   if(  random_fun(17,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);	
							   */	
						}
						else
						{ // 诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,57) )
							{
								// if( random_fun(7,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(275,2)&&random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum+= maxchip*(2+randoma(7)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )	
							//if( rival_alive<= rival_all/3 || rival_all==1 )    //概率加和的关系
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,1) && random_rate(103,pGameParam->uModelValue/72)  ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum+=  maxchip*(2+randoma(9));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}
						}


					}


					else if(pGameParam->uModelValue>7462*2/10)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else
						{ //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,27) )
							{
								//  if( random_fun(7,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(201,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{ 
										pGameParam->uRaiseNum +=  maxchip*(2+randoma(5));// my_chip_left
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,1) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum +=   maxchip*(2+randoma(9));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;///诈唬的标志位
							}
						}				

					}

					//考虑节省效率是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					else if(pGameParam->uModelValue>7462*15/100)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=   maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    
									if( random_rate(271,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum +=   maxchip*(2+randoma(10)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;///诈唬的标志位
									}
							}
							//考虑要不要弃掉！！！！！！！！！！！！！！！！！！！！！！！！！！！1			
							//  else this_chip=this_chip;

						} 
					}

					//后15%情况下  直接弃疗
					else
					{   
					    if( random_rate(102,97)|| random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=0; 
					}



					if( maxrate >0.9  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,90 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //这个就一般不太像诈唬
					{ 
						if( random_rate(100,(int)(maxrate*100+12) )  )
							pGameParam->uRaiseNum=0;
					}
					else 
					{ 											 
						if( random_rate(100,(int)maxrate*100) )
							pGameParam->uRaiseNum=0;
					}

				}	

				//考虑是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				if(  random_rate(103,  (int)((7462-pGameParam->uModelValue)/72)  ) )	 //最后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{ pGameParam->uRaiseNum=0;}//再以这么大的概率弃疗 双层保险  这样好吗？？

			}
			//考虑屏蔽掉		
			//  if(  random_fun(3,100) )//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			//  {  this_chip=0; } //  7/100的概率不跟

			//最后 引入对手决策    对手压得很多咱们就不诈唬了！！！！！！！！！！！      不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
			/*
			   if(已跟对手 跟前的剩余注数大于my注数的1/2) 
			   计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//最后判断保证 后10%以很高的概率不玩！！
			if(pGameParam->uRaiseNum >=maxchip)
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //后10%
				{ 
					if( random_rate(   103,(int)((7462-pGameParam->uModelValue)/72)   )   )
						pGameParam->uRaiseNum=0;
				}
			}
		}


		//加注两次以上要考虑 已压的和别人的压得和剩余人数情况了吧！！！！！！！
		if(pGameParam->uStakeTime>1)//第2次以上加注，可以不加那么大  怕吓走别人，但也可以一定概率压大！！
		{ 

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//比我期望赢的大
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,77-temp) )//第二次进入了 所以应该说运气让咱们以比较高一点的概率玩下去                            77改为了87因为后面还会在取random_fun((int)pGameParam->uModelValue/72,7462/72) )呢 77是不是就太小了 ？？            可能赢，所以要random一下比较大的概率 77/100 的概率赢 进入判断 跟
			{  
				//若randoma(7462)较费时间 可以同时比上一个数 random_fun((int)pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue+10)/72) )	 //很小可能赢 故比率在小一点            最 后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{       pGameParam->uRaiseNum = maxchip;  //跟注
					if(pGameParam->uModelValue>7462*25/100)    // 排名在前2/7可以加注
					{
						if(  random_rate(100,57) )
						{
							if(  random_rate(100,27) )
								pGameParam->uRaiseNum += maxchip*random_rate(103,pGameParam->uModelValue/72);
							/*
							   if(  random_fun(27,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);

							   if(  random_fun(17,100) )
							   this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);	
							   */	
						}
						else { // 诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,57) )
							{
								// if( random_fun(7,100) )
								// this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    
									if( random_rate(102,0)&&random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum += maxchip*(2+randoma(7)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 177,2)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{
								pGameParam->uRaiseNum += maxchip*(2+randoma(9));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
							}
						}		
					}


					else if(pGameParam->uModelValue>7462*2/10)    // 排名在前8/10可以加注
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							if(  random_rate(100,27) )
							{
								//if( random_fun(7,100) )
								//this_chip=this_chip+maxchip*randoma(2)*random_fun((int)pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun((int)pGameParam->uModelValue/72,7462/72);
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(201,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum += maxchip*(3+randoma(9));// my_chip_left
										pGameParam->uZhahuCarefulFlag=1;///诈唬的标志位
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 207,0)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							{ 
								pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//概率很低的
								pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位  这里有问题，上面的可能得出是0也会进入！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							}
						}	


					}

					//考虑节省效率是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					else if(pGameParam->uModelValue>7462*15/100)    // 排名在前1/2可以加注
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //是否需要简化而删掉
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(270,1) && random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uZhahuCarefulFlag=1;//诈唬的标志位
										pGameParam->uRaiseNum +=  maxchip*(5+randoma(10)); // my_chip_left
									}
							}
							//  else this_chip=this_chip;

						} 
					}







					if( maxrate >0.9  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,90 ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //对手已压其90%的金币 证明其弃牌可能很小了
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //这个就一般不太像诈唬
					{ 
						if( random_rate(100,(int)(maxrate*100+12) )  )
							pGameParam->uRaiseNum=0;
					}
					else 
					{ 											 
						if( random_rate(100,(int)maxrate*84) )
							pGameParam->uRaiseNum=0;
					}	

				}		
				/*	
				//后15%情况下 
				//自己在后150%   判断对手压的的占其比重很大  则诈唬基本可能无效              若比我方比重大很多则认为我方要以较大概率弃疗

				// maxchip+rival_chipleft>my_chip*1/2
				//伪代码
				if(已跟对手 跟前的剩余注数大于my注数的1/2)  计算 rate[7]=maxchip*100/对手总注数   取出最大的max_rate[x]

				if( (max_rate[x])>90  )   //对手已压其90%的金币 证明其弃牌可能很小了
				{ 
				if( random_fun(90,100) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				this_chip=0;										
				}
				if( (max_rate[x])>70  )   //这个就一般不太像诈唬
				{ 
				if( random_fun(max_rate[x]+7,100) )
				this_chip=0;

				}
				else if( (max_rate[x])>50  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
				{ 
				if( random_fun(max_rate[x]+12,100) )
				this_chip=0;
				}								 
				else
				{ 
				if( random_fun(max_rate[x],100) )
				this_chip=0;
				}			
				*/


				//考虑是否屏蔽掉！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				if(  random_rate(103,(7462-pGameParam->uModelValue)/72) )	 //最后要不要来一个		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; 返回权	
				{ pGameParam->uRaiseNum=0;}//再以这么大的概率弃疗 双层保险  这样好吗？？

			}

			//  if(  random_fun(3,100) )//很可能赢 不是一定会赢，所以要random一下比较大的概率 92/100 的概率赢 跟
			//	{  this_chip=0; } //  7/100的概率不跟

			//最后 引入对手决策    对手压得很多咱们就不诈唬了！！！！！！！！！！！      不考虑对手压的不多的情形 因为他已经跟了！！就证明还好吧
			/*
			   if(已跟对手 跟前的剩余注数大于my注数的1/2) 
			   计算 rate[7]=maxchip/对手总注数*7462  取出最大的max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//最后判断保证 后10%以很高的概率不玩！！
			if(pGameParam->uRaiseNum >= maxchip)//yi Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //后10%
				{
					if( random_rate( 103,(7462-pGameParam->uModelValue)/72) )
						pGameParam->uRaiseNum=0;
				}
			}



			if(pGameParam->uStakeTime>=3)//这是在上面已经处理后遗漏的情况下  我觉得自己已经压了很多了有必要看一下结果？？  这个地方欠考虑！！！！！！！！！！！！！！！！！！！！！！
			{ 
				if(pGameParam->uRaiseNum==0) //Need Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111 //跟了很多次了 不能轻易放弃啊
				{ 

					if( pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*70/100 )  //maxchip指的是这一压注圈增加的最大的那笔钱 my_chip_in也指的是这一圈压了的多少钱
					{
						if(maxchip - pGameParam->uLastChip <  pGameParam->uSelfChip*12/100)
						{
							pGameParam->uRaiseNum=maxchip;                    //Need modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
						}
						else if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
						{  if(    random_rate(maxchip+1,(pGameParam->uLastChip+10)  )    )
							pGameParam->uRaiseNum=maxchip;  
						}
						else 
						{  if( random_rate(maxchip+1,(pGameParam->uLastChip) ))
							pGameParam->uRaiseNum=maxchip; 
						}
					}

					else  if(  pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*50/100) 
					{ 
						if ( random_rate( ( pGameParam->uWholeChip+pGameParam->uSelfChip+1),( pGameParam->uWholeChip+52) ) )
							pGameParam->uRaiseNum= maxchip;//modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					}
					else 
					{
						if( random_rate( ( pGameParam->uWholeChip+pGameParam->uSelfChip+1),( pGameParam->uWholeChip) ) )
							pGameParam->uRaiseNum= maxchip;//modify！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					}														 
				}
				else{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						pGameParam->uRaiseNum +=  maxchip;
				}

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //概率加和的关系
				{
					if( random_rate(100,37) )
						pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;

					if( random_rate( 512,1) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{  pGameParam->uZhahuCarefulFlag=1;      //bluff_flag_careful=1,//诈唬的标志位

						pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//概率很低的
					}

				}

			}					

		}	
	}

	//action 动作

	Strategy_Action(pGameParam,maxchip,rivalnum);
}	
//河牌圈喊注
else if(pGameParam->uGameState==GAME_RIVER)
{
	pGameParam->uPopChip = pGameParam->inquire_pop;//当前奖池注额

	maxchip = 0;
	maxrate = 0;
	rivalnum = 0;
	selfbet = 0;

	for(i=0;i<8;i++)
	{
		//遍历各玩家的投注和策略，看奇哥需要记录信息
		if(pGameParam->inquire_msg[i].bet>maxchip)
			maxchip = pGameParam->inquire_msg[i].bet;

		if(pGameParam->inquire_msg[i].pid == pGameParam->uId)
		{
			pGameParam->uSelfGold = pGameParam->inquire_msg[i].money;
			pGameParam->uSelfChip = pGameParam->inquire_msg[i].jetton;
			selfbet = pGameParam->inquire_msg[i].bet;
		}

		if( pGameParam->inquire_msg[i].pid!=pGameParam->uId
				&& pGameParam->inquire_msg[i].pid!=0
				&&(pGameParam->inquire_msg[i].strategy == STRATEGY_RAISE
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_CALL
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_ALLIN
					|| pGameParam->inquire_msg[i].strategy == STRATEGY_BLIND))
		{
			rivalnum++;
		}
	}

	for(i=0;i<8;i++)
	{
		if( pGameParam->inquire_msg[i].pid != pGameParam->uId && pGameParam->inquire_msg[i].pid != 0
				&& (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1)>maxrate
				&& pGameParam->inquire_msg[i].strategy != STRATEGY_FOLD
				&& pGameParam->inquire_msg[i].bet + pGameParam->inquire_msg[i].jetton >= (pGameParam->uSelfChip+selfbet)/2)
			maxrate = (float)(pGameParam->inquire_msg[i].bet)/(float)(pGameParam->inquire_msg[i].bet+pGameParam->inquire_msg[i].jetton+1);
	}

	//策略选择（奇哥想想）
	strategy_river(pGameParam);

	if( pGameParam->uMustWinFlag == 1 )
	{
		pGameParam->uRaiseNum = maxchip;

		if(random_rate(100,77))
			pGameParam->uRaiseNum += maxchip * 7 * ( 2 + randoma(10));
	}
	else if( pGameParam->uWinFlag == MUST_WIN )
	{
		pGameParam->uRaiseNum = maxchip;

		if(random_rate(100,77))
			pGameParam->uRaiseNum += maxchip * 7 * ( 2 + randoma(10));			
	}
	else if( pGameParam->uWinFlag == PROB_WIN_MAX )
	{
		if( random_rate(103,pGameParam->uModelValue/72) )
			pGameParam->uRaiseNum = maxchip;
		if( random_rate(2,1) )
			pGameParam->uRaiseNum+=maxchip*7*( 2 + randoma(10));
	}
	else if( pGameParam->uProbWinMaxFlag == 1 )
	{
		if(rivalnum<=(pGameParam->uPlayerNum-1)/3||pGameParam->uPlayerNum==2)
			pGameParam->uRaiseNum = maxchip;
		if( maxchip - pGameParam->uLastChip <= pGameParam->uSelfChip / 2 )
			pGameParam->uRaiseNum = maxchip;
		if( random_rate(103,pGameParam->uModelValue/72) )
			pGameParam->uRaiseNum = maxchip;
	}
	else if( pGameParam->uZhahuFlag == 1 )
	{
		if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 10 
				|| pGameParam->uWholeChip > ( pGameParam->uWholeChip + pGameParam->uSelfChip ) * 9 / 10 )
			pGameParam->uRaiseNum = maxchip;
		else if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 4 )
		{
			if(random_rate(maxchip+1,pGameParam->uLastChip+10))
				pGameParam->uRaiseNum = maxchip;
			if(rivalnum<=(pGameParam->uPlayerNum-1)/3||pGameParam->uPlayerNum==2)
			{
				if(random_rate(100,7))
					pGameParam->uRaiseNum+=maxchip*(1+randoma(7))*random_rate(103,pGameParam->uModelValue/72);
			}
		}
		else
		{
			if(random_rate(103,pGameParam->uModelValue/72))
				pGameParam->uRaiseNum = maxchip;
			if(rivalnum<=(pGameParam->uPlayerNum-1)/3||pGameParam->uPlayerNum==2)
			{
				if(random_rate(100,5))
					pGameParam->uRaiseNum+=maxchip*(1+randoma(6))*random_rate(103,pGameParam->uModelValue/72);
			}
		}
	}
	else if( pGameParam->uZhahuCarefulFlag == 1 )
	{
		if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 10 
				|| pGameParam->uWholeChip > ( pGameParam->uWholeChip + pGameParam->uSelfChip ) * 9 / 10 )
			pGameParam->uRaiseNum = maxchip;
		else if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 4 )
		{
			if(random_rate(maxchip+1,pGameParam->uLastChip+10))
				pGameParam->uRaiseNum = maxchip;
			if(rivalnum<=(pGameParam->uPlayerNum-1)/3||pGameParam->uPlayerNum==2)
			{
				if(random_rate(100,7))
					pGameParam->uRaiseNum+=maxchip*(1+randoma(7))*random_rate(103,pGameParam->uModelValue/72);
			}
		}
		else
		{
			if(random_rate(103,pGameParam->uModelValue/72))
				pGameParam->uRaiseNum = maxchip;
			if(rivalnum<=(pGameParam->uPlayerNum-1)/3||pGameParam->uPlayerNum==2)
			{
				if(random_rate(100,5))
					pGameParam->uRaiseNum+=maxchip*(1+randoma(6))*random_rate(103,pGameParam->uModelValue/72);
			}
		}

		if( maxchip - pGameParam->uLastChip > pGameParam->uSelfChip * 9 / 10 
				&& pGameParam->uWholeChip < ( pGameParam->uWholeChip + pGameParam->uSelfChip ) * 3 / 10 )
			pGameParam->uRaiseNum = maxchip;
	}
	else if( pGameParam->uWinFlag == PROB_WIN_MIDDLE || pGameParam->uWinFlag == PROB_WIN_MIN )
	{
		if( pGameParam->uWholeChip > ( pGameParam->uWholeChip + pGameParam->uSelfChip ) * 9 / 10 )
		{
			if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 10 )
				pGameParam->uRaiseNum = maxchip;
			else if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 4 )
			{
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum = maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{					 
					if( random_rate( 100,7) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的	 
					}
				}
			}
			else
			{
				if(random_rate(100,92))//回来检查一下！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					pGameParam->uRaiseNum = maxchip;//pGameParam->uRaiseNum = 0;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{	
					if(random_rate(100,57))
						pGameParam->uRaiseNum = maxchip;

					if( random_rate( 100,7)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
					}

				}						
			}
		}
		else if( pGameParam->uWholeChip > ( pGameParam->uWholeChip + pGameParam->uSelfChip ) * 7 / 10 )
		{
			if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 10 )
			{
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum = maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{	
					if(random_rate(100,37))//无意义！！！！！！！！！！！！！！！！！！！！！！！
						pGameParam->uRaiseNum = maxchip;	

					if( random_rate( 100,7)&& random_rate(103,pGameParam->uModelValue/72)) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
					}	 
				}	
			}
			else if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 4 )
			{
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum = maxchip;	

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{					 
					if(random_rate(100,27))//有意义！！！！！！！！！！！！！！！！！！！！！！！
						pGameParam->uRaiseNum = maxchip;	

					if( random_rate( 100,7)&& random_rate(103,pGameParam->uModelValue/72)) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
					}		 
				}
			}
			else
			{
				if(random_rate(maxchip+1,pGameParam->uLastChip))
					pGameParam->uRaiseNum = maxchip;	

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //概率加和的关系
				{	
					if(random_rate(100,21))//有意义！！！！！！！！！！！！！！！！！！！！！！！
						pGameParam->uRaiseNum = maxchip;	

					if( random_rate( 100,7)&& random_rate(103,pGameParam->uModelValue/72)) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
					}
				}						
			}
		}

		else  if(pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*5/10) 
		{ 
			if ( random_rate( (pGameParam->uWholeChip+pGameParam->uSelfChip+1),(pGameParam->uWholeChip+52) ) )
				pGameParam->uRaiseNum = maxchip;


			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
			{
				if( random_rate(100,20) )
					pGameParam->uRaiseNum = maxchip;

				if( random_rate( 100,5)&&random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					// this_chip= this_chip + maxchip*(1+randoma(7))*random_rate(103,Value/72);//概率很低的
				{
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
				} 

			}

		}

		else 
		{
			if( random_rate((pGameParam->uWholeChip+pGameParam->uSelfChip+1), pGameParam->uWholeChip) )//考虑已经压了的 +剩余对手的情况
			{
				pGameParam->uRaiseNum = maxchip;


				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
				{
					if( random_rate(100,16) )
						pGameParam->uRaiseNum = maxchip;

					if( random_rate( 100,3)&& random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
						// this_chip= this_chip + maxchip*(1+randoma(7))*random_rate(103,Value/72);//概率很低的
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
					} 

				}
			}

			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
			{
				if( random_rate(100,16) )
					pGameParam->uRaiseNum = maxchip;

				if( random_rate( 100,3) && random_rate(103,pGameParam->uModelValue/72) ) //诈唬！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
					// this_chip= this_chip + maxchip*(1+randoma(7))*random_rate(103,Value/72);//概率很低的
				{
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum += maxchip*(1+randoma(7));//概率很低的
				} 

			}		 
		}
	}	
	//肯定不玩的情形
	if( pGameParam->uWinFlag == PROB_WIN_MIN )//肯定不玩的情形
	{
		if( maxchip-pGameParam->uLastChip> (pGameParam->uWholeChip+pGameParam->uSelfChip)*7/10 )
			pGameParam->uRaiseNum=0;
		if(pGameParam->uWholeChip<(pGameParam->uWholeChip+pGameParam->uSelfChip)*10/100)   
			if( maxchip-pGameParam->uLastChip> (pGameParam->uWholeChip+pGameParam->uSelfChip) *5/10 )
				pGameParam->uRaiseNum=0;

		//if(已跟对手 跟前的剩余注数大于my注数的1/2)  计算 rate[7]=maxchip*100/对手总注数   取出最大的max_rate[x]    
		if( maxrate > 0.9  )   //对手已压其90%的金币 证明其弃牌可能很小了
		{ 
			if( random_rate(100,92) )  //比较有可能是对手诈唬呢！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
				pGameParam->uRaiseNum=0;										
		}	
		else if( maxrate > 0.7  )   //这个就一般不太像诈唬
		{ 
			if( random_rate(100,(int)(maxrate*100)+7) )
				pGameParam->uRaiseNum=0;
		}
		else if( maxrate>0.5 )   //把7462乘在最前面//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //把7462乘在最前面
		{ 
			if( random_rate(100,(int)(maxrate*100)+12) )
				pGameParam->uRaiseNum=0;
		}								 
		else
		{ 
			if( random_rate(100,(int)(maxrate*100) ) )
				pGameParam->uRaiseNum=0;
		}			

		if( rivalnum > pGameParam->uPlayerNum/2  )  
		{		 
			pGameParam->uRaiseNum=0; 
		}

		//if(Mustqiliao)
		//	  this_chip=0;		 		
	}
	Strategy_Action(pGameParam,maxchip,rivalnum);

}	
return;
}

//处理potwin-msg
void GameShowdown(PGAME_PARAM pGameParam)
{
	pGameParam->uGameState = GAME_START;
}

//处理potwin-msg
void GamePotwin(PGAME_PARAM pGameParam)
{
	pGameParam->uGameState = GAME_START;
}
