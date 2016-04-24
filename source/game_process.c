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

//����������Ϣ
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


	//��ȡׯ����Ϣ
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
	//��ȡСäע�����Ϣ

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
	//��ȡ��äע�����Ϣ


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
	// ��ȡ��ͨ���1 ��Ϣ
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
	//��ȡ��ͨ���2 ��Ϣ
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
	//��ȡ��ͨ���3 ��Ϣ
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
	//��ȡ��ͨ���4 ��Ϣ
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

	//��ȡ��ͨ���5 ��Ϣ	
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

//����seat-info-msg
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



//����blind-msg
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
		//��������Ҳ����Խ�����ӵ����������룬����û�ҵ��������������������
		if( pGameParam->uSelfGold < MAX_ACCESS_JETTON - pGameParam->uSelfChip )
		{
			pGameParam->uSelfChip += pGameParam->uSelfGold;
			pGameParam->uSelfGold = 0;
		}
		//����㹻
		else
		{
			pGameParam->uSelfChip = MAX_ACCESS_JETTON;
			pGameParam->uSelfGold -= ( MAX_ACCESS_JETTON - pGameParam->uSelfChip );
		}
	}

	//������ӳ�����Բ���äע
	if( pGameParam->uSelfChip < Blind )
	{
		pGameParam->uGameState = GAME_END;
		return;
	}	

	//��������Ƿ��Ǵ�Сäע
	if( pGameParam->sblind_msg.pid == pGameParam->uId )
		pGameParam->uSelfChip -= pGameParam->sblind_msg.bet;
	else if( pGameParam->bblind_msg.pid == pGameParam->uId )
		pGameParam->uSelfChip -= pGameParam->bblind_msg.bet;
	return;
}

//����hold-cards-msg
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

//����flop-msg
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

//����turn-msg
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

//����river-msg
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
	char BufferSendDec[BUFFER_SIZE2];                 //���;�����Ϣ������
	bzero(BufferSendDec,BUFFER_SIZE2);
	char *sendf ="raise";
	if((strcmp(sendbuf,sendf))==0 )
	{
		int mnt;
		mnt= sprintf(BufferSendDec,"%s %d \n",sendbuf,number);		
		// �����������buffer�е����� 
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
		// �����������buffer�е����� 
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

	if(pGameParam->uRaiseNum<maxchip)  //�ж�һ��   �ֲ��Ѿ�ѹ�˺ܶ�ȴ��Ҫ���������
	{ 
		if(pGameParam->uMustWinFlag==1)//һ������� ���ﲻ����this_chip<maxchip�� �������ų�һ��
		{
			pGameParam->uRaiseNum=maxchip;
		}

		if(pGameParam->uProbWinMaxFlag==1)//һ������� ���ﲻ����this_chip<maxchip�� �������ų�һ��
		{
			if( random_rate(103,pGameParam->uModelValue/72) )
				pGameParam->uRaiseNum=maxchip;
		}

		if( pGameParam->uZhahuFlag==1  ) //�ǲ��ǲ����ж�I_am_Alive ��Ϊ�ܹ������жϾ�֤��֮ǰû������    һ������� ���ﲻ����this_chip<maxchip�� �������ų�һ�� 
		{
			if( (maxchip-pGameParam->uLastChip< pGameParam->uSelfChip*12/100) || (    pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*90/100    )   )
			{
				pGameParam->uRaiseNum=maxchip;
			}
			else if(maxchip-pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ ���Զ���СһЩ��
				// if( random_fun(77,100) )
				// this_chip=maxchip;
				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
					// if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,57) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 202,7)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(7));//���ʺܵ͵�
					}
				}
			}
			else 
			{  
				if(random_rate(103,pGameParam->uModelValue/72))//pGameParam->uModelValue����ҲӦ���ܵ��ã���
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
				//if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,37) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 520,7)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(7));//���ʺܵ͵�
					}
				}
			}
		}

		if( pGameParam->uZhahuCarefulFlag==1 ) //�ǲ��ǲ����ж�I_am_Alive ��Ϊ�ܹ������жϾ�֤��֮ǰû������    һ������� ���ﲻ����this_chip<maxchip�� �������ų�һ�� 
		{      //pGameParam->uLastChip < pGameParam->uSelfChip
			if( (maxchip-pGameParam->uLastChip< pGameParam->uSelfChip*12/100) || (    pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*90/100    )   )
			{
				pGameParam->uRaiseNum=maxchip;
			}
			else if(maxchip-pGameParam->uLastChip < pGameParam->uSelfChip*25/100 )
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ ���Զ���СһЩ��
				// if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(103,pGameParam->uModelValue/72) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 520,1)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1; 
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(7));//���ʺܵ͵�
					}
				}
			}

		}








		if(  pGameParam->uWholeChip>(pGameParam->uWholeChip + pGameParam->uSelfChip)*90/100 )  //maxchipָ������һѹעȦ���ӵ������Ǳ�Ǯ my_chip_inҲָ������һȦѹ�˵Ķ���Ǯ
		{
			if(maxchip - pGameParam->uLastChip < pGameParam->uSelfChip*12/100)    // || (    my_chip_in_whole>(my_chip_in_whole+my_chip_left)*90/100    )
			{
				pGameParam->uRaiseNum=maxchip;
			}
			else if( maxchip- pGameParam->uLastChip < pGameParam->uSelfChip* 25/100)
			{  
				if( random_rate(maxchip+1,pGameParam->uLastChip+21) )
					pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ ���Զ���СһЩ��
				// if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,57) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 127,5)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(5));//���ʺܵ͵�
					}
				}
			}
			else 
			{  
				if(  random_rate(maxchip+1,pGameParam->uLastChip+7 ) )
					pGameParam->uRaiseNum=maxchip;

				//if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
				//if( random_fun(77,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,27) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 277,5)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{ 
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(5));//���ʺܵ͵�
					}
				}
			}
		}  


		if(  pGameParam->uWholeChip >(pGameParam->uWholeChip + pGameParam->uSelfChip)*70/100)  //maxchipָ������һѹעȦ���ӵ������Ǳ�Ǯ my_chip_inҲָ������һȦѹ�˵Ķ���Ǯ
		{
			if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*12/100)
			{
				pGameParam->uRaiseNum=maxchip;

				//if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
				//if( random_fun(77,100) )
				//this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ

				{
					if( random_rate(100,27) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 572,5)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(3));//���ʺܵ͵�

				}

			} 
			// pGameParam->uWholeChip >(pGameParam->uWholeChip + pGameParam->uSelfChip)
			else if(maxchip- pGameParam->uLastChip < pGameParam->uSelfChip*25/100)
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip+12))
					pGameParam->uRaiseNum=maxchip;

					// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
					// if( random_fun(67,100) )
					// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,17) )
						pGameParam->uRaiseNum=maxchip;
					if( random_rate( 772,5)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(3));//���ʺܵ͵�
					}
				}

			}
			else 
			{  
				if(random_rate(maxchip+1,pGameParam->uLastChip))
					pGameParam->uRaiseNum=maxchip;
				// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
				// if( random_fun(57,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{ 
					if( random_rate(100,12) )
						pGameParam->uRaiseNum=maxchip;

					if( random_rate( 125,0) &&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+=  maxchip*(1+randoma(3));//���ʺܵ͵�
					}
				}

			}
		}

		else  if( pGameParam->uWholeChip >(pGameParam->uWholeChip + pGameParam->uSelfChip)*50/100) 
		{ 
			if (   random_rate( (pGameParam->uWholeChip + pGameParam->uSelfChip+1),(pGameParam->uWholeChip+52) )  )
				pGameParam->uRaiseNum=maxchip;

			//if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
			// if( random_fun(37,100) )
			// this_chip=maxchip;

			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
			{
				if( random_rate(121,7) )
					pGameParam->uRaiseNum=maxchip;

				if( random_rate( 172,0)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
				{
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum +=   maxchip*(1+randoma(2));//���ʺܵ͵�
				}
			}

		}
		else 
		{        //modify
			if( random_rate( (pGameParam->uWholeChip + pGameParam->uSelfChip+1),(pGameParam->uWholeChip-34) ) )//�����Ѿ�ѹ�˵� +ʣ����ֵ����
			{
				pGameParam->uRaiseNum=maxchip;

				// if( rival_alive<=2 )    //���ʼӺ͵Ĺ�ϵ
				//if( random_fun(17,100) )
				// this_chip=maxchip;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(112,7) )
						pGameParam->uRaiseNum=maxchip;
					//this_chip=this_chip>maxchip ? this_chip:maxchip ;

					if( random_rate( 217,0)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{ 
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum+= maxchip*(1+randoma(2));//���ʺܵ͵�
					}
				}
			}
			//����ʣ����������������Ӱ�죡����������������������������������������������������������������������������������������	
			//������ʣ����ֵ����	����Ӧ�ðѸ��ʶ��ĵ�һЩ��������������������
			// if( rival_alive<=2 )     //���ʼӺ͵Ĺ�ϵ
			// if( random_fun(12,100) )
			// this_chip=maxchip;

			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
			{
				if( random_rate(100,17) )
					// if( random_fun(17,100) )
					pGameParam->uRaiseNum=maxchip;
				if( random_rate( 215,0)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
				{ 
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum+= maxchip*(1+randoma(7));//���ʺܵ͵�
				}
			}	 
		}														 
	}


	if(maxchip==pGameParam->uLastChip) //��û���˼�עpGameParam->uLastChip
	{
		if(pGameParam->uRaiseNum==0) //����           //����ͻȻ�뵽 ��Ҷ����Ƶ����   �Լ��ƽϺ�ʱ ��δ���
		{
			pGameParam->uStrategy = STRATEGY_CHECK;
		}
		if(pGameParam->uRaiseNum>0)
		{
			//��ע pGameParam->uRaiseNum-maxchip
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


	if(maxchip>pGameParam->uLastChip) // ���˼�ע
	{
		if(pGameParam->uRaiseNum==0) //����           //����ͻȻ�뵽 ��Ҷ����Ƶ����   �Լ��ƽϺ�ʱ ��δ���
		{
			pGameParam->uStrategy = STRATEGY_FOLD;
		}
		if(pGameParam->uRaiseNum==maxchip) //����
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
		//��ע my_raise_chip = pGameParam->uRaiseNum-pGameParam->uLastChip   //����my_chip_in ָ�����ұ�ѹעȦ �Ѿ�ѹ��ȥ��

	}

	if(pGameParam->uStrategy==STRATEGY_CHECK)
	{

		char *decision="check";
		SendActionMsg(decision,0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_CALL)
	{
		char *decision="call";
		SendActionMsg(decision,0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_RAISE)
	{

		char *decision="raise";
		SendActionMsg(decision,uRaiseJetton);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
		return;
	}
	else if(pGameParam->uStrategy==STRATEGY_ALLIN)
	{
		char *decision ="all_in";
		SendActionMsg(decision,0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
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

//����inquire-msg
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

	//����ǰ��ע
	printf("fanyufeng success!!!\n");
	if(pGameParam->uGameState==GAME_PRE)
	{
		printf("GAME_PRE!!!!!!\n");
		pGameParam->uPopChip = pGameParam->inquire_pop;//��ǰ����ע��

		maxchip = 0;
		maxrate = 0;
		rivalnum = 0;
		selfbet = 0;

		for(i=0;i<8;i++)
		{
			//��������ҵ�Ͷע�Ͳ��ԣ��������Ҫ��¼��Ϣ
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

		//����ѡ��������룩
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
			SendActionMsg("check",0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
  	
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_CALL)
		{
			SendActionMsg("call",0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_RAISE)
		{
			SendActionMsg("raise",pGameParam->uRaiseNum-pGameParam->uLastChip);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
			return;
		}
		else if(pGameParam->uStrategy==STRATEGY_ALLIN)
		{
			SendActionMsg("all_in",0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
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
	
	//����Ȧ��ע
	else if(pGameParam->uGameState==GAME_FLOP)
	{
		printf("GAME_FLOP!!!!!!\n");

	pGameParam->uPopChip = pGameParam->inquire_pop;//��ǰ����ע��
	maxchip = 0;
	maxrate = 0;
	rivalnum = 0;
	selfbet = 0;

	for(i=0;i<8;i++)
	{
		//��������ҵ�Ͷע�Ͳ��ԣ��������Ҫ��¼��Ϣ
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

	pGameParam->uStakeTime++;//���ò��Ժ����ȶ�pGameParam->uStakeTime    ÿһ���յ��µ���Ҫ��pGameParam->uStakeTime����

	if(pGameParam->uWinFlag == MUST_WIN) //          ->xx=win_must                                             
	{ 
		pGameParam->uMustWinFlag = 1;//��һ�ֵı�־λ ���������ƺ� �����Ǳ�Ӯ״̬����ô�죿�� ���Խ��


		//����һ�μӵ�̫�࣬�����߱���	   
		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 

			pGameParam->uRaiseNum = maxchip;  //�ȱ�֤���ٸ�ע
			if(  random_rate(100,77) )
			{
				if(  random_rate(100,37) )  //modify ��һ�������ױ��� uStakeTime=2ʱ�����ݵ�
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

		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 
			pGameParam->uRaiseNum = maxchip;  //�ȱ�֤���ٸ�ע
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
						pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    ����All_in֮��Ӧ�ò������ж������˰� �϶�����������
				//} 
			}
			
			if( random_rate(107,25) )                       //modify 
			pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    ����All_in֮��Ӧ�ò������ж������˰� �϶�����������
			
			if(pGameParam->uStakeTime>3)
			{
				pGameParam->uRaiseNum+=maxchip;
				if( random_rate(100,57) )
					pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left  
			}
		}

	}	

	if( pGameParam->uWinFlag == PROB_WIN_MAX ) //          ->xx=win_possiblebig     //�ܿ���Ӯ~                                         
	{    
		//����һ�μӵ�̫�࣬�����߱���

		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 
			if( random_rate(103,(pGameParam->uModelValue+520)/72))//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			{  
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//�д��˶ԣ�����������������������������������
					pGameParam->uRaiseNum=maxchip;  //�ȱ�֤���ٸ�ע
				else
				{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=maxchip;
					else
						pGameParam->uRaiseNum=0;
				}
				if(  random_rate(100,52) )         //modify
				{		
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//�д��˶ԣ�����������������������������������
					{ 
						//pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���  //modify !!!!!!!!!!
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
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//�д��˶ԣ�����������������������������������
					{	
						if(  random_rate(100,37) )   //modify
						{
							if( random_rate(100,25) )//modify
							{
								pGameParam->uRaiseNum+=maxchip*randoma(2);
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
							}
							if( random_rate(5,1) )   //modify
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(6));
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
							}
							if( random_rate(77,1) )  //modify
							{
								pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
							}
						}
						//  else this_chip=this_chip;
					}
				}  
			}	  
		}

		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 

			pGameParam->uRaiseNum=maxchip;  //�ȱ�֤���ٸ�ע

			if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//�д��˶ԣ�����������������������������������
			{			

				if(  random_rate(100,57) )       //modify
				{
					if( random_rate(100,37) )    //modify
					{
						pGameParam->uRaiseNum+=maxchip;
						pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
					}
					if(  random_rate(100,7) )
					{
						pGameParam->uRaiseNum+=maxchip*2;
						pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
					}
				}
				else{
					if(  random_rate(100,77) )
					{
						if( random_rate(7,0) )
						{
							pGameParam->uRaiseNum+=maxchip*randoma(2),
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
						}

						if( random_rate(127,21) )
						{
							pGameParam->uRaiseNum+=maxchip*(2+randoma(3)),
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
						}

						if( random_rate(100,7)&&random_rate(103,pGameParam->uModelValue/72) )
						{ 
							pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left 
							pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ��� all_in֮����������� ����������������
						}
					} 
				}
			}
			if(pGameParam->uStakeTime>3)
			{ 
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//�д��˶ԣ�����������������������������������
				{
					if( random_rate(100,21) )
						pGameParam->uRaiseNum+= pGameParam->uSelfChip; // my_chip_left  
				} 
			}

		}

	}




	//һ�����Ӯ
	if(pGameParam->uWinFlag == PROB_WIN_MIDDLE) //  ���õõ������к��Valueֵ         ->xx=win_possiblenormal     //һ�����Ӯ~                                         
	{ 

		//����һ�μӵ�̫�࣬�����߱���

		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{   
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)         //��������Ӯ�Ĵ�
			{  
				temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; 
				temp=temp*100/MAX_ACCESS_JETTON;
			}

			if(  random_rate(100,87-temp) )//77��Ϊ��87��Ϊ���滹����ȡrandom_rate(103,Value/72) )�� 77�ǲ��Ǿ�̫С�� ����            ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{  
				//��randoma(7462)�Ϸ�ʱ�� ����ͬʱ����һ���� random_rate(103,Value/72) )
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-Value,7462) )	this_chip=0; ����Ȩ	
				{       
					pGameParam->uRaiseNum=maxchip;  //�ȱ�֤���ٸ�ע  //��ע
					if(pGameParam->uModelValue>7462*6/7)    // ������ǰ2/7���Լ�ע
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
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate( 103,pGameParam->uModelValue/72);
								
								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
									pGameParam->uZhahuFlag=1;//թ���ı�־λ
							    }
								//if( random_fun(2,100) )
								//  this_chip= this_chip + maxchip*( 5+randoma(12) )*random_fun( pGameParam->uModelValue/72,7462/72 ); // my_chip_left
							}
							//  else this_chip=this_chip;

						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
							//if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							if( random_rate(100,37) )
								//pGameParam->uRaiseNum=0;  //�ȱ�֤���ٸ�ע 
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum : maxchip ;

							if( random_rate( 100,10)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(15));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}								 
						}

					}


					else if( pGameParam->uModelValue>7462*5/7 )    // ������ǰ2/7���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,12) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
									pGameParam->uZhahuFlag=1;//թ���ı�־λ
							    }
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )   //���ʼӺ͵Ĺ�ϵ rival_all==1 //1δ���Լ���
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum = pGameParam->uRaiseNum > maxchip ? pGameParam->uRaiseNum:maxchip ;

							if( random_rate( 102,7)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}										
					}


					else if(pGameParam->uModelValue>7462*5/10)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,29) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							else if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{     //�Ƿ���Ҫ�򻯶�ɾ��
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

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(105,2)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ�� С�ĵı�־λ
							}
						}											

					}

					else
					{   //�Լ��ں�50%  Ҫ����  �ж϶���ѹ�ĵ�ռ����� �����ҷ����ش�ܶ�����Ϊ�ҷ�Ҫ�Խϴ��������

						//  if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						//	{
						// if( random_fun(37,100) )
						// this_chip=this_chip>maxchip ? this_chip:maxchip ;

						//	   if( random_fun( 7,100) ) //թ����������������������������������������������������������������������������������������������������������������������������
						//       this_chip= this_chip + maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//���ʺܵ͵�
						//	 }


						// maxchip+rival_chipleft>my_chip*1/2
						//α����
						//ÿһ��ѹע��ʼʱ �ֵ��Լ��ˣ������Ѹ�ѡ���ܽ�������Լ�0.5������£�������ѹע��ռ������Ǯ���ı�ֵ
						// ����ֵ*7462 ���ҵ�pGameParam->uModelValue�Ƚ� ������1000����~~~~~~~


						if( (maxrate*7462 > pGameParam->uModelValue +1000) || maxrate>0.92   )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
						{ 
							if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
								pGameParam->uRaiseNum=0;       //pGameParam->uFoldFlag = 1;										
						}	

						if( maxrate*7462 > pGameParam->uModelValue + 200 )   //�����һ�㲻̫��թ��
						{ 
							if( random_rate(103,(int)(maxrate*7462-105)/72) )
								pGameParam->uRaiseNum=0;//pGameParam->uFoldFlag = 1;
						}


						if( maxrate<0.3 )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
							if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
							{ 
								if( random_rate( 207,2)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
									pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
								}									

							}							

					}	
					
					 //modify    maxrate>0.7
					if( maxrate>0.95||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) && maxrate>0.77    )   //�����һ�㲻̫��թ��
					{ 
						if( random_rate(103,(int)(maxrate*7462-527)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					//else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //�����һ�㲻̫��թ��
					//{ 
					//	if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
						//	pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					//}		
				
				}


			}	

			//�����Ƿ����ε���������������������������������������������������������������������������������������������������������������������������
			if(  random_rate(103,(7462-pGameParam->uModelValue)/75 )   )  //modify	 -110         //���Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
			{ pGameParam->uRaiseNum = 0; }                                  //������ô��ĸ������� ˫�㱣��  �������𣿣�  ��������Ŀ��ܣ�������������


			if( ( (maxrate*7462 > pGameParam->uModelValue +1000) &&   (maxrate>0.77) ) || (maxrate>0.92)  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
			{ 
				if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
			}	

			else if( ( maxrate*7462 > pGameParam->uModelValue + 500 ) && (maxrate>0.32)     )   //�����һ�㲻̫��թ��  modify 
			{ 
				if( random_rate(103,(int)(maxrate*7462-155)/72 ))
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
			}

			/*
			   if( maxrate<0.3 )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
			   { 
			   if( random_rate( 100,7) ) //թ����������������������������������������������������������������������������������������������������������������������������
			   {
			   pGameParam->uRaiseNum+=maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//���ʺܵ͵�
			   pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
			   }									

			   }	 
			   */




			//  if(  random_fun(3,100) )//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			//	{  this_chip=0; } //  7/100�ĸ��ʲ���

			//��� ������־���  �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
			/*	
				if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
				���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

				if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				if( (max_rate[x])>pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				*/



		}


		//��ע��������Ҫ���� ��ѹ�ĺͱ��˵�ѹ�ú�ʣ����������˰ɣ�������������
		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//��������Ӯ�Ĵ�
			{ temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON; }

			//�Ѿ�����һ��֤����Ӧ�û�����  ������������
			if(  random_rate(100,92-temp) )//����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{ 					
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-Value,7462) )	this_chip=0; ����Ȩ	
				{ 
					pGameParam->uRaiseNum= maxchip;  //�ȱ�֤���ٸ�ע //�ȱ�֤���ٸ�ע

					if(pGameParam->uModelValue>7462*6/7)    // ������ǰ2/7���Լ�ע
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
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+= maxchip*randoma(2) * random_rate(103,pGameParam->uModelValue/72);
									
									if( random_rate(272,5)&& random_rate(103,pGameParam->uModelValue/72) )//modify����������������������������������������������������������������������������
										{
											pGameParam->uRaiseNum+=maxchip*(2+randoma(7)); // my_chip_left
											pGameParam->uZhahuFlag=1;//թ���ı�־λ
										}
							}
							//  else this_chip=this_chip;

						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							if( random_rate(100,37) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum:maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(102, 7) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(3+randoma(9));   //���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/7)    // ������ǰ2/7���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,52) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else 
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(127,1)&& random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(1+randoma(5)); // my_chip_left
									pGameParam->uZhahuFlag=1;//թ���ı�־λ
								}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 100,2) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(8));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/10)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else{ //�Ƿ���Ҫ�򻯶�ɾ��
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
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,5)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}
						}											
					}

					else
					{   //�Լ��ں�50%  Ҫ����  �ж϶���ѹ�ĵ�ռ����� �����ҷ����ش�ܶ�����Ϊ�ҷ�Ҫ�Խϴ��������


							if( ( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate >0.52) ) || maxrate >0.95  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
							{ 
								if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
							}	

							else if(  (maxrate*7462 > pGameParam->uModelValue + 200)&&(maxrate >0.21) || maxrate >0.75 )   //�����һ�㲻̫��թ��
							{ 
								if( random_rate(103,(int)(maxrate*7462-327)/72 ))
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
							}

						/*
						// maxchip+rival_chipleft>my_chip*1/2
						if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2)  ���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

						if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
						{ 
						if( random_fun( (max_rate[x]-215),7462) )
						this_chip=0;

						}
						if( (max_rate[x])>pGameParam->uModelValue +200  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
						{ 
						if( random_fun(max_rate[x]-327,7462) )
						this_chip=0;

						}
						*/


						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,0)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{ 
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}

						}	

					}


                     //modify    maxrate>0.7
					if( maxrate>0.9||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) || maxrate>0.7    )   //�����һ�㲻̫��թ��
					{ 
						if( random_rate(103,(int)(maxrate*7462-327)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //�����һ�㲻̫��թ��
					{ 
						if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}									 

					/*
					//��� ������־���  �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
					if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
					���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]  ʵ����Ӧrate[7]=maxchip*7462/������ע��  �ȳ˺��

					if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
					{ 
					if( random_fun( (max_rate[x]-215),7462) )
					this_chip=0;

					}
					else if( (max_rate[x])> pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
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

			if(pGameParam->uStakeTime>=3)//�����������Ѿ��������©�������  �Ҿ����Լ��Ѿ�ѹ�˺ܶ����б�Ҫ��һ�½������  ����ط�Ƿ���ǣ�������������������������������������������
			{ 
				if(  pGameParam->uRaiseNum == 0  )  //���˺ܶ���� �������׷�����
				{ 


					if(pGameParam->uWholeChip>(pGameParam->uWholeChip+ pGameParam->uSelfChip)*70/100)  //maxchipָ������һѹעȦ���ӵ������Ǳ�Ǯ my_chip_inҲָ������һȦѹ�˵Ķ���Ǯ
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
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 502,7) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}
					}

				}

			}


		}	
	}




	if(pGameParam->uWinFlag == PROB_WIN_MIN) //  ���õõ������к��Valueֵ         ->xx=win_possibleless     //һ�����Ӯ~                                         
	{ 

		//����һ�μӵ�̫�࣬�����߱���

		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{  

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//��������Ӯ�Ĵ�
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,52-temp) )//77��Ϊ��87��Ϊ���滹����ȡrandom_fun(pGameParam->uModelValue/72,7462/72) )�� 77�ǲ��Ǿ�̫С�� ����            ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{  
				//��randoma(7462)�Ϸ�ʱ�� ����ͬʱ����һ���� random_fun(pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue-10)/72) )	 //��С����Ӯ �ʱ�����Сһ��            �� ��Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{       
					pGameParam->uRaiseNum = maxchip;  //��ע
					if(pGameParam->uModelValue>7462*25/100)    // ������ǰ2/7���Լ�ע
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
						{ // թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )	
							//if( rival_alive<= rival_all/3 || rival_all==1 )    //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,1) && random_rate(103,pGameParam->uModelValue/72)  ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=  maxchip*(2+randoma(9));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}
						}


					}


					else if(pGameParam->uModelValue>7462*2/10)    // ������ǰ2/7���Լ�ע
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else
						{ //թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,1) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum +=   maxchip*(2+randoma(9));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;///թ���ı�־λ
							}
						}				

					}

					//���ǽ�ʡЧ���Ƿ����ε���������������������������������������������������������������������������������������������������������������������������������������
					else if(pGameParam->uModelValue>7462*15/100)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=   maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//թ����������������������������������������������������������������������������������������������������������������������������	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    
									if( random_rate(271,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum +=   maxchip*(2+randoma(10)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;///թ���ı�־λ
									}
							}
							//����Ҫ��Ҫ����������������������������������������������������������1			
							//  else this_chip=this_chip;

						} 
					}

					//��15%�����  ֱ������
					else
					{   
					    if( random_rate(102,97)|| random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=0; 
					}



					if( maxrate >0.9  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,90 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //�����һ�㲻̫��թ��
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

				//�����Ƿ����ε���������������������������������������������������������������������������������������������������������������������������
				if(  random_rate(103,  (int)((7462-pGameParam->uModelValue)/72)  ) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{ pGameParam->uRaiseNum=0;}//������ô��ĸ������� ˫�㱣��  �������𣿣�

			}
			//�������ε�		
			//  if(  random_fun(3,100) )//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			//  {  this_chip=0; } //  7/100�ĸ��ʲ���

			//��� ������־���    ����ѹ�úܶ����ǾͲ�թ���ˣ���������������������      �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
			/*
			   if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
			   ���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//����жϱ�֤ ��10%�Ժܸߵĸ��ʲ��棡��
			if(pGameParam->uRaiseNum >=maxchip)
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //��10%
				{ 
					if( random_rate(   103,(int)((7462-pGameParam->uModelValue)/72)   )   )
						pGameParam->uRaiseNum=0;
				}
			}
		}


		//��ע��������Ҫ���� ��ѹ�ĺͱ��˵�ѹ�ú�ʣ����������˰ɣ�������������
		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//��������Ӯ�Ĵ�
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,77-temp) )//�ڶ��ν����� ����Ӧ��˵�����������ԱȽϸ�һ��ĸ�������ȥ                            77��Ϊ��87��Ϊ���滹����ȡrandom_fun((int)pGameParam->uModelValue/72,7462/72) )�� 77�ǲ��Ǿ�̫С�� ����            ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{  
				//��randoma(7462)�Ϸ�ʱ�� ����ͬʱ����һ���� random_fun(pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue+10)/72) )	 //��С����Ӯ �ʱ�����Сһ��            �� ��Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{       pGameParam->uRaiseNum = maxchip;  //��ע
					if(pGameParam->uModelValue>7462*25/100)    // ������ǰ2/7���Լ�ע
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
						else { // թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 177,2)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum += maxchip*(2+randoma(9));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}
						}		
					}


					else if(pGameParam->uModelValue>7462*2/10)    // ������ǰ8/10���Լ�ע
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;///թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 207,0)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{ 
								pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ  ���������⣬����Ŀ��ܵó���0Ҳ����룡��������������������������������������������������������������������������������������
							}
						}	


					}

					//���ǽ�ʡЧ���Ƿ����ε���������������������������������������������������������������������������������������������������������������������������������������
					else if(pGameParam->uModelValue>7462*15/100)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//թ����������������������������������������������������������������������������������������������������������������������������	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(270,1) && random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
										pGameParam->uRaiseNum +=  maxchip*(5+randoma(10)); // my_chip_left
									}
							}
							//  else this_chip=this_chip;

						} 
					}







					if( maxrate >0.9  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,90 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //�����һ�㲻̫��թ��
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
				//��15%����� 
				//�Լ��ں�150%   �ж϶���ѹ�ĵ�ռ����غܴ�  ��թ������������Ч              �����ҷ����ش�ܶ�����Ϊ�ҷ�Ҫ�Խϴ��������

				// maxchip+rival_chipleft>my_chip*1/2
				//α����
				if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2)  ���� rate[7]=maxchip*100/������ע��   ȡ������max_rate[x]

				if( (max_rate[x])>90  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
				{ 
				if( random_fun(90,100) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
				this_chip=0;										
				}
				if( (max_rate[x])>70  )   //�����һ�㲻̫��թ��
				{ 
				if( random_fun(max_rate[x]+7,100) )
				this_chip=0;

				}
				else if( (max_rate[x])>50  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
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


				//�����Ƿ����ε���������������������������������������������������������������������������������������������������������������������������
				if(  random_rate(103,(7462-pGameParam->uModelValue)/72) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{ pGameParam->uRaiseNum=0;}//������ô��ĸ������� ˫�㱣��  �������𣿣�

			}

			//  if(  random_fun(3,100) )//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			//	{  this_chip=0; } //  7/100�ĸ��ʲ���

			//��� ������־���    ����ѹ�úܶ����ǾͲ�թ���ˣ���������������������      �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
			/*
			   if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
			   ���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//����жϱ�֤ ��10%�Ժܸߵĸ��ʲ��棡��
			if(pGameParam->uRaiseNum >= maxchip)//yi Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //��10%
				{
					if( random_rate( 103,(7462-pGameParam->uModelValue)/72) )
						pGameParam->uRaiseNum=0;
				}
			}



			if(pGameParam->uStakeTime>=3)//�����������Ѿ��������©�������  �Ҿ����Լ��Ѿ�ѹ�˺ܶ����б�Ҫ��һ�½������  ����ط�Ƿ���ǣ�������������������������������������������
			{ 
				if(pGameParam->uRaiseNum==0) //Need Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111 //���˺ܶ���� �������׷�����
				{ 

					if( pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*70/100 )  //maxchipָ������һѹעȦ���ӵ������Ǳ�Ǯ my_chip_inҲָ������һȦѹ�˵Ķ���Ǯ
					{
						if(maxchip - pGameParam->uLastChip <  pGameParam->uSelfChip*12/100)
						{
							pGameParam->uRaiseNum=maxchip;                    //Need modify����������������������������������������������������������������������������
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
							pGameParam->uRaiseNum= maxchip;//modify����������������������������������������������������������������������������
					}
					else 
					{
						if( random_rate( ( pGameParam->uWholeChip+pGameParam->uSelfChip+1),( pGameParam->uWholeChip) ) )
							pGameParam->uRaiseNum= maxchip;//modify����������������������������������������������������������������������������
					}														 
				}
				else{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						pGameParam->uRaiseNum +=  maxchip;
				}

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,37) )
						pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;

					if( random_rate( 512,1) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{  pGameParam->uZhahuCarefulFlag=1;      //bluff_flag_careful=1,//թ���ı�־λ

						pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//���ʺܵ͵�
					}

				}

			}					

		}	
	}

	//action ����


	Strategy_Action(pGameParam,maxchip,rivalnum);
}		
/*
   if( pGameParam->uStakeTime == 0 )
   {
   pGameParam->uStateTime++;

//����ѡ��������룩
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
SendActionMsg("check",0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
return;
}
else if(pGameParam->uStrategy==STRATEGY_CALL)
{
SendActionMsg("call",0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
return;
}
else if(pGameParam->uStrategy==STRATEGY_RAISE)
{
SendActionMsg("raise",pGameParam->uRaiseNum);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
return;
}
else if(pGameParam->uStrategy==STRATEGY_ALLIN)
{
SendActionMsg("allin",0);//���ͺ���������������˵�һ������Ϊraise������⣬�ڶ���������Ϊ0;raise����µڶ�������Ϊ��ע���
return;
}
else if(pGameParam->uStrategy==STRATEGY_FOLD)
{
SendActionMsg("fold",0);
printf("sendmasgaction successs!!!!!\n");
pGameParam->uGameState = GAME_COMPLETE;
return;
}*/

//ת��Ȧ��ע
else if(pGameParam->uGameState==GAME_TURN)
{
	printf("GAME_TURN !!!!!\n");
	pGameParam->uPopChip = pGameParam->inquire_pop;//��ǰ����ע��

	maxchip = 0;
	maxrate = 0;
	rivalnum = 0;
	selfbet = 0;

	for(i=0;i<8;i++)
	{
		//��������ҵ�Ͷע�Ͳ��ԣ��������Ҫ��¼��Ϣ
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

	pGameParam->uStakeTime++;//���ò��Ժ����ȶ�pGameParam->uStakeTime    ÿһ���յ��µ���Ҫ��pGameParam->uStakeTime����

	
	
    if(pGameParam->uWinFlag == MUST_WIN) //          ->xx=win_must                                             
	{ 
		pGameParam->uMustWinFlag = 1;//��һ�ֵı�־λ ���������ƺ� �����Ǳ�Ӯ״̬����ô�죿�� ���Խ��


		//����һ�μӵ�̫�࣬�����߱���	   
		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 

			pGameParam->uRaiseNum += maxchip;  //�ȱ�֤���ٸ�ע
			if(  random_rate(100,77) )
			{
				if(  random_rate(100,37) )  //modify ��һ�������ױ��� uStakeTime=2ʱ�����ݵ�
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

		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 
			pGameParam->uRaiseNum = maxchip;  //�ȱ�֤���ٸ�ע
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
						pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    ����All_in֮��Ӧ�ò������ж������˰� �϶�����������
				//} 
			}
			
			if( random_rate(107,52) )                       //modify 
			pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left    ����All_in֮��Ӧ�ò������ж������˰� �϶�����������
			
			if(pGameParam->uStakeTime>3)
			{
				pGameParam->uRaiseNum+=maxchip;
				if( random_rate(100,57) )
					pGameParam->uRaiseNum+=pGameParam->uSelfChip; // my_chip_left  
			}
		}

	}	

	if( pGameParam->uWinFlag == PROB_WIN_MAX ) //          ->xx=win_possiblebig     //�ܿ���Ӯ~                                         
	{    
		//����һ�μӵ�̫�࣬�����߱���

		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 
			if( random_rate(103,(pGameParam->uModelValue+520)/72))//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			{  
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//�д��˶ԣ�����������������������������������
					pGameParam->uRaiseNum=maxchip;  //�ȱ�֤���ٸ�ע
				else
				{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=maxchip;
					else
						pGameParam->uRaiseNum=0;
				}
				if(  random_rate(100,72) )         //modify
				{		
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//�д��˶ԣ�����������������������������������
					{ 
						//pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���  //modify !!!!!!!!!!
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
					if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX )//�д��˶ԣ�����������������������������������
					{	
					    pGameParam->uRaiseNum+=maxchip;
						if(  random_rate(100,37) )   //modify
						{
							if( random_rate(100,25) )//modify
							{
								pGameParam->uRaiseNum+=maxchip*(1+randoma(5));
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
							}
							if( random_rate(5,1) )   //modify
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(6));
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
							}
							if( random_rate(77,1) )  //modify
							{
								pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
							}
						}
						//  else this_chip=this_chip;
					}
				}  
			}	  
		}

		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 

			pGameParam->uRaiseNum=maxchip;  //�ȱ�֤���ٸ�ע

			if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//�д��˶ԣ�����������������������������������
			{			

				if(  random_rate(100,57) )       //modify
				{   
					pGameParam->uRaiseNum+=maxchip;
					if( random_rate(100,37) )    //modify
					{
						pGameParam->uRaiseNum+=maxchip*(1+randoma(5));
						pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
					}
					if(  random_rate(100,7) )
					{
						pGameParam->uRaiseNum+=maxchip*(2+randoma(7));
						pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
					}
				}
				else{
					if(  random_rate(100,77) )
					{
						if( random_rate(7,0) )
						{
							pGameParam->uRaiseNum+=maxchip*randoma(2),
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
						}

						if( random_rate(127,21) )
						{
							pGameParam->uRaiseNum+=maxchip*(2+randoma(3)),
								pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ���
						}

						if( random_rate(100,5)&&random_rate(103,pGameParam->uModelValue/72) )
						{ 
							pGameParam->uRaiseNum+=maxchip+ pGameParam->uSelfChip; // my_chip_left 
							pGameParam->uProbWinMaxFlag=1;//��ǽ�����PROB_WIN_MAX�Ĵ��� all_in֮����������� ����������������
						}
					} 
				}
			}
			if(pGameParam->uStakeTime>3)
			{ 
				if( pGameParam->uIsAllFlag == FIVE_IN_FIVE || pGameParam->uIsAllFlag == FIVE_IN_SIX)//�д��˶ԣ�����������������������������������
				{
					if( random_rate(100,21) )
						pGameParam->uRaiseNum+= pGameParam->uSelfChip; // my_chip_left  
				} 
			}

		}

	}




	//һ�����Ӯ
	if(pGameParam->uWinFlag == PROB_WIN_MIDDLE) //  ���õõ������к��Valueֵ         ->xx=win_possiblenormal     //һ�����Ӯ~                                         
	{ 

		//����һ�μӵ�̫�࣬�����߱���

		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{   
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)         //��������Ӯ�Ĵ�
			{  
				temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; 
				temp=temp*100/MAX_ACCESS_JETTON;
			}

			if(  random_rate(100,87-temp) )//77��Ϊ��87��Ϊ���滹����ȡrandom_rate(103,Value/72) )�� 77�ǲ��Ǿ�̫С�� ����            ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{  
				//��randoma(7462)�Ϸ�ʱ�� ����ͬʱ����һ���� random_rate(103,Value/72) )
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-Value,7462) )	this_chip=0; ����Ȩ	
				{       
					pGameParam->uRaiseNum=maxchip;  //�ȱ�֤���ٸ�ע  //��ע
					if(pGameParam->uModelValue>7462*6/7)    // ������ǰ2/7���Լ�ע
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
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate( 103,pGameParam->uModelValue/72);
								
								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
									pGameParam->uZhahuFlag=1;//թ���ı�־λ
							    }
								//if( random_fun(2,100) )
								//  this_chip= this_chip + maxchip*( 5+randoma(12) )*random_fun( pGameParam->uModelValue/72,7462/72 ); // my_chip_left
							}
						
						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 || pGameParam->uPlayerNum==2 )
							//if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							if( random_rate(100,37) )
								//pGameParam->uRaiseNum=0;  //�ȱ�֤���ٸ�ע 
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum : maxchip ;

							if( random_rate( 100,10)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(15));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}								 
						}

					}


					else if( pGameParam->uModelValue>7462*5/7 )    // ������ǰ2/7���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,12) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(100,2) && random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
									pGameParam->uZhahuFlag=1;//թ���ı�־λ
							    }
							}
							//  else this_chip=this_chip;

						}
						
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )   //���ʼӺ͵Ĺ�ϵ rival_all==1 //1δ���Լ���
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum = pGameParam->uRaiseNum > maxchip ? pGameParam->uRaiseNum:maxchip ;

							if( random_rate( 102,7)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}										
					}


					else if(pGameParam->uModelValue>7462*5/10)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,29) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							else if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else
						{     //�Ƿ���Ҫ�򻯶�ɾ��
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

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(105,2)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ�� С�ĵı�־λ
							}
						}											

					}

					else
					{   //�Լ��ں�50%  Ҫ����  �ж϶���ѹ�ĵ�ռ����� �����ҷ����ش�ܶ�����Ϊ�ҷ�Ҫ�Խϴ��������

						//  if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						//	{
						// if( random_fun(37,100) )
						// this_chip=this_chip>maxchip ? this_chip:maxchip ;

						//	   if( random_fun( 7,100) ) //թ����������������������������������������������������������������������������������������������������������������������������
						//       this_chip= this_chip + maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//���ʺܵ͵�
						//	 }


						// maxchip+rival_chipleft>my_chip*1/2
						//α����
						//ÿһ��ѹע��ʼʱ �ֵ��Լ��ˣ������Ѹ�ѡ���ܽ�������Լ�0.5������£�������ѹע��ռ������Ǯ���ı�ֵ
						// ����ֵ*7462 ���ҵ�pGameParam->uModelValue�Ƚ� ������1000����~~~~~~~


						if( (maxrate*7462 > pGameParam->uModelValue +1000) || maxrate>0.92   )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
						{ 
							if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
								pGameParam->uRaiseNum=0;       //pGameParam->uFoldFlag = 1;										
						}	

						if( maxrate*7462 > pGameParam->uModelValue + 200 )   //�����һ�㲻̫��թ��
						{ 
							if( random_rate(103,(int)(maxrate*7462-105)/72) )
								pGameParam->uRaiseNum=0;//pGameParam->uFoldFlag = 1;
						}


						if( maxrate<0.3 )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
							if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
							{ 
								if( random_rate( 207,2)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
								{
									pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
									pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
								}									

							}							

					}	
					
					 //modify    maxrate>0.7
					if( maxrate>0.95||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) && maxrate>0.77    )   //�����һ�㲻̫��թ��
					{ 
						if( random_rate(103,(int)(maxrate*7462-527)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					//else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //�����һ�㲻̫��թ��
					//{ 
					//	if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					//}		
				
				}


			}	

			//�����Ƿ����ε���������������������������������������������������������������������������������������������������������������������������
			if(  random_rate(103,(7462-pGameParam->uModelValue)/75 )   )  //modify	 -110         //���Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
			{ pGameParam->uRaiseNum = 0; }                                  //������ô��ĸ������� ˫�㱣��  �������𣿣�  ��������Ŀ��ܣ�������������


			if( ( (maxrate*7462 > pGameParam->uModelValue +1000) &&   (maxrate>0.77) ) || (maxrate>0.92)  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
			{ 
				if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
			}	

			else if( ( maxrate*7462 > pGameParam->uModelValue + 500 ) && (maxrate>0.32)     )   //�����һ�㲻̫��թ��  modify 
			{ 
				if( random_rate(103,(int)(maxrate*7462-155)/72 ))
					pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
			}

			/*
			   if( maxrate<0.3 )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )
			   { 
			   if( random_rate( 100,7) ) //թ����������������������������������������������������������������������������������������������������������������������������
			   {
			   pGameParam->uRaiseNum+=maxchip*(2+randoma(15))*random_rate(103,pGameParam->uModelValue/72);//���ʺܵ͵�
			   pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
			   }									

			   }	 
			   */




			//  if(  random_fun(3,100) )//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			//	{  this_chip=0; } //  7/100�ĸ��ʲ���

			//��� ������־���  �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
			/*	
				if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
				���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

				if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				if( (max_rate[x])>pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
				{ 
				if( random_fun( (max_rate[x]-215),7462) )
				this_chip=0;

				}
				*/



		}


		//��ע��������Ҫ���� ��ѹ�ĺͱ��˵�ѹ�ú�ʣ����������˰ɣ�������������
		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 
			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//��������Ӯ�Ĵ�
			{ temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON; }

			//�Ѿ�����һ��֤����Ӧ�û�����  ������������
			if(  random_rate(100,92-temp) )//����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{ 					
				if(  random_rate(103,pGameParam->uModelValue/72) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-Value,7462) )	this_chip=0; ����Ȩ	
				{ 
					pGameParam->uRaiseNum= maxchip;  //�ȱ�֤���ٸ�ע //�ȱ�֤���ٸ�ע

					if(pGameParam->uModelValue>7462*6/7)    // ������ǰ2/7���Լ�ע
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
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,57) )
							{
								if( random_rate(100,52) )
									pGameParam->uRaiseNum+= maxchip*randoma(2) * random_rate(103,pGameParam->uModelValue/72);
									
									if( random_rate(272,5)&& random_rate(103,pGameParam->uModelValue/72) )//modify����������������������������������������������������������������������������
										{
											pGameParam->uRaiseNum+=maxchip*(2+randoma(7)); // my_chip_left
											pGameParam->uZhahuFlag=1;//թ���ı�־λ
										}
							}
							//  else this_chip=this_chip;

						}

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							if( random_rate(100,37) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum:maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate(102, 7) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(3+randoma(9));   //���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/7)    // ������ǰ2/7���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,52) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,17) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else 
						{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,37) )
							{
								if( random_rate(100,21) )
									pGameParam->uRaiseNum+=maxchip*randoma(2)*random_rate(103,pGameParam->uModelValue/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_rate(103,pGameParam->uModelValue/72);

								if( random_rate(127,1)&& random_rate(103,pGameParam->uModelValue/72) )
								{
									pGameParam->uRaiseNum+=maxchip*(1+randoma(5)); // my_chip_left
									pGameParam->uZhahuFlag=1;//թ���ı�־λ
								}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							if( random_rate(100,27) )
								pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 100,2) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(8));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}


					}


					else if(pGameParam->uModelValue>7462*5/10)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,52) )
						{
							if(  random_rate(100,39) )
								pGameParam->uRaiseNum+=maxchip*random_rate(103,pGameParam->uModelValue/72);

							if(  random_rate(100,7) )
								pGameParam->uRaiseNum+=maxchip*2*random_rate(103,pGameParam->uModelValue/72);					
						}
						else{ //�Ƿ���Ҫ�򻯶�ɾ��
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
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,5)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}
						}											
					}

					else
					{   //�Լ��ں�50%  Ҫ����  �ж϶���ѹ�ĵ�ռ����� �����ҷ����ش�ܶ�����Ϊ�ҷ�Ҫ�Խϴ��������


							if( ( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate >0.52) ) || maxrate >0.95  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
							{ 
								if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
							}	

							else if(  (maxrate*7462 > pGameParam->uModelValue + 200)&&(maxrate >0.21) || maxrate >0.75 )   //�����һ�㲻̫��թ��
							{ 
								if( random_rate(103,(int)(maxrate*7462-327)/72 ))
									pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
							}

						/*
						// maxchip+rival_chipleft>my_chip*1/2
						if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2)  ���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

						if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
						{ 
						if( random_fun( (max_rate[x]-215),7462) )
						this_chip=0;

						}
						if( (max_rate[x])>pGameParam->uModelValue +200  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
						{ 
						if( random_fun(max_rate[x]-327,7462) )
						this_chip=0;

						}
						*/


						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,0)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{ 
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}

						}	

					}


                     //modify    maxrate>0.7
					if( maxrate>0.9||( (maxrate*7462 > pGameParam->uModelValue +1000)&&(maxrate>0.7) )  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 103,(int)(maxrate*7462-215)/72 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;										
					}	

					else if( (maxrate*7462 > pGameParam->uModelValue + 500) || maxrate>0.7    )   //�����һ�㲻̫��թ��
					{ 
						if( random_rate(103,(int)(maxrate*7462-327)/72 ))
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}			 

					else if(   (maxrate*7462 > pGameParam->uModelValue)  || maxrate>0.5  )   //�����һ�㲻̫��թ��
					{ 
						if( random_rate(103,(int)(maxrate*7462-pGameParam->uModelValue)/72) )
							pGameParam->uRaiseNum = 0;  //pGameParam->uFoldFlag = 1;
					}									 

					/*
					//��� ������־���  �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
					if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
					���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]  ʵ����Ӧrate[7]=maxchip*7462/������ע��  �ȳ˺��

					if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
					{ 
					if( random_fun( (max_rate[x]-215),7462) )
					this_chip=0;

					}
					else if( (max_rate[x])> pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
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

			if(pGameParam->uStakeTime>=3)//�����������Ѿ��������©�������  �Ҿ����Լ��Ѿ�ѹ�˺ܶ����б�Ҫ��һ�½������  ����ط�Ƿ���ǣ�������������������������������������������
			{ 
				if(  pGameParam->uRaiseNum == 0  )  //���˺ܶ���� �������׷�����
				{ 


					if(pGameParam->uWholeChip>(pGameParam->uWholeChip+ pGameParam->uSelfChip)*70/100)  //maxchipָ������һѹעȦ���ӵ������Ǳ�Ǯ my_chip_inҲָ������һȦѹ�˵Ķ���Ǯ
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
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 502,7) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=maxchip*(2+randoma(5));//���ʺܵ͵�
								pGameParam->uZhahuFlag=1;//թ���ı�־λ
							}
						}
					}

				}

			}


		}	
	}




	if(pGameParam->uWinFlag == PROB_WIN_MIN) //  ���õõ������к��Valueֵ         ->xx=win_possibleless     //һ�����Ӯ~                                         
	{ 

		//����һ�μӵ�̫�࣬�����߱���

		if(pGameParam->uStakeTime==1)//��һ�μ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{  

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//��������Ӯ�Ĵ�
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,52-temp) )//77��Ϊ��87��Ϊ���滹����ȡrandom_fun(pGameParam->uModelValue/72,7462/72) )�� 77�ǲ��Ǿ�̫С�� ����            ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{  
				//��randoma(7462)�Ϸ�ʱ�� ����ͬʱ����һ���� random_fun(pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue-10)/72) )	 //��С����Ӯ �ʱ�����Сһ��            �� ��Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{       
					pGameParam->uRaiseNum = maxchip;  //��ע
					if(pGameParam->uModelValue>7462*25/100)    // ������ǰ2/7���Լ�ע
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
						{ // թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )	
							//if( rival_alive<= rival_all/3 || rival_all==1 )    //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 202,1) && random_rate(103,pGameParam->uModelValue/72)  ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum+=  maxchip*(2+randoma(9));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}
						}


					}


					else if(pGameParam->uModelValue>7462*2/10)    // ������ǰ2/7���Լ�ע
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else
						{ //թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							// if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 127,1) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum +=   maxchip*(2+randoma(9));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;///թ���ı�־λ
							}
						}				

					}

					//���ǽ�ʡЧ���Ƿ����ε���������������������������������������������������������������������������������������������������������������������������������������
					else if(pGameParam->uModelValue>7462*15/100)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=   maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//թ����������������������������������������������������������������������������������������������������������������������������	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    
									if( random_rate(271,0)&& random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uRaiseNum +=   maxchip*(2+randoma(10)); // my_chip_left
										pGameParam->uZhahuCarefulFlag=1;///թ���ı�־λ
									}
							}
							//����Ҫ��Ҫ����������������������������������������������������������1			
							//  else this_chip=this_chip;

						} 
					}

					//��15%�����  ֱ������
					else
					{   
					    if( random_rate(102,97)|| random_rate(103,pGameParam->uModelValue/72) )
						 pGameParam->uRaiseNum=0; 
					}



					if( maxrate >0.9  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,90 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //�����һ�㲻̫��թ��
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

				//�����Ƿ����ε���������������������������������������������������������������������������������������������������������������������������
				if(  random_rate(103,  (int)((7462-pGameParam->uModelValue)/72)  ) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{ pGameParam->uRaiseNum=0;}//������ô��ĸ������� ˫�㱣��  �������𣿣�

			}
			//�������ε�		
			//  if(  random_fun(3,100) )//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			//  {  this_chip=0; } //  7/100�ĸ��ʲ���

			//��� ������־���    ����ѹ�úܶ����ǾͲ�թ���ˣ���������������������      �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
			/*
			   if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
			   ���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//����жϱ�֤ ��10%�Ժܸߵĸ��ʲ��棡��
			if(pGameParam->uRaiseNum >=maxchip)
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //��10%
				{ 
					if( random_rate(   103,(int)((7462-pGameParam->uModelValue)/72)   )   )
						pGameParam->uRaiseNum=0;
				}
			}
		}


		//��ע��������Ҫ���� ��ѹ�ĺͱ��˵�ѹ�ú�ʣ����������˰ɣ�������������
		if(pGameParam->uStakeTime>1)//��2�����ϼ�ע�����Բ�����ô��  �����߱��ˣ���Ҳ����һ������ѹ�󣡣�
		{ 

			int temp=0;
			if(maxchip>MAX_ACCESS_JETTON*pGameParam->uModelValue/7462)//��������Ӯ�Ĵ�
			{temp=maxchip-MAX_ACCESS_JETTON*pGameParam->uModelValue/7462; temp=temp*100/MAX_ACCESS_JETTON;}

			if(  random_rate(100,77-temp) )//�ڶ��ν����� ����Ӧ��˵�����������ԱȽϸ�һ��ĸ�������ȥ                            77��Ϊ��87��Ϊ���滹����ȡrandom_fun((int)pGameParam->uModelValue/72,7462/72) )�� 77�ǲ��Ǿ�̫С�� ����            ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 77/100 �ĸ���Ӯ �����ж� ��
			{  
				//��randoma(7462)�Ϸ�ʱ�� ����ͬʱ����һ���� random_fun((int)pGameParam->uModelValue/72,7462/72) )
				if(  random_rate(103,(pGameParam->uModelValue+10)/72) )	 //��С����Ӯ �ʱ�����Сһ��            �� ��Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{       pGameParam->uRaiseNum = maxchip;  //��ע
					if(pGameParam->uModelValue>7462*25/100)    // ������ǰ2/7���Լ�ע
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
						else { // թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 

						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							//this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 177,2)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{
								pGameParam->uRaiseNum += maxchip*(2+randoma(9));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
							}
						}		
					}


					else if(pGameParam->uModelValue>7462*2/10)    // ������ǰ8/10���Լ�ע
					{
						if(  random_rate(100,37) )
						{
							if(  random_rate(100,21) )
								pGameParam->uRaiseNum +=maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(17,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //թ����������������������������������������������������������������������������������������������������������������������������
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
										pGameParam->uZhahuCarefulFlag=1;///թ���ı�־λ
									}
							}
							//  else this_chip=this_chip;

						} 
						if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
						{
							//if( random_fun(37,100) )
							// this_chip=this_chip>maxchip ? this_chip:maxchip ;

							if( random_rate( 207,0)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
							{ 
								pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//���ʺܵ͵�
								pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ  ���������⣬����Ŀ��ܵó���0Ҳ����룡��������������������������������������������������������������������������������������
							}
						}	


					}

					//���ǽ�ʡЧ���Ƿ����ε���������������������������������������������������������������������������������������������������������������������������������������
					else if(pGameParam->uModelValue>7462*15/100)    // ������ǰ1/2���Լ�ע
					{
						if(  random_rate(100,25) )
						{
							if(  random_rate(100,9) )
								pGameParam->uRaiseNum +=  maxchip*random_rate(103,pGameParam->uModelValue/72);

							//if(  random_fun(7,100) )
							//this_chip=this_chip+maxchip*2*random_fun(pGameParam->uModelValue/72,7462/72);					
						}
						else{ //�Ƿ���Ҫ�򻯶�ɾ��
							if(  random_rate(100,21) )
							{
								//  if( random_fun(19,100) )
								//  this_chip=this_chip+maxchip*randoma(2)*random_fun(pGameParam->uModelValue/72,7462/72);
								// if( random_fun(25,100) )
								// this_chip=this_chip+maxchip*(2+randoma(6))*random_fun(pGameParam->uModelValue/72,7462/72);
								//թ����������������������������������������������������������������������������������������������������������������������������	
								if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )  
									if( random_rate(270,1) && random_rate(103,pGameParam->uModelValue/72) )
									{
										pGameParam->uZhahuCarefulFlag=1;//թ���ı�־λ
										pGameParam->uRaiseNum +=  maxchip*(5+randoma(10)); // my_chip_left
									}
							}
							//  else this_chip=this_chip;

						} 
					}







					if( maxrate >0.9  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,90 ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}

					else if( maxrate >0.7  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
					{ 
						if( random_rate( 100,(int)(maxrate*100+7) ) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
							pGameParam->uRaiseNum=0;										
					}   
					else if( maxrate> 0.5 )   //�����һ�㲻̫��թ��
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
				//��15%����� 
				//�Լ��ں�150%   �ж϶���ѹ�ĵ�ռ����غܴ�  ��թ������������Ч              �����ҷ����ش�ܶ�����Ϊ�ҷ�Ҫ�Խϴ��������

				// maxchip+rival_chipleft>my_chip*1/2
				//α����
				if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2)  ���� rate[7]=maxchip*100/������ע��   ȡ������max_rate[x]

				if( (max_rate[x])>90  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
				{ 
				if( random_fun(90,100) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
				this_chip=0;										
				}
				if( (max_rate[x])>70  )   //�����һ�㲻̫��թ��
				{ 
				if( random_fun(max_rate[x]+7,100) )
				this_chip=0;

				}
				else if( (max_rate[x])>50  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
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


				//�����Ƿ����ε���������������������������������������������������������������������������������������������������������������������������
				if(  random_rate(103,(7462-pGameParam->uModelValue)/72) )	 //���Ҫ��Ҫ��һ��		if(  random_fun(7462-pGameParam->uModelValue,7462) )	this_chip=0; ����Ȩ	
				{ pGameParam->uRaiseNum=0;}//������ô��ĸ������� ˫�㱣��  �������𣿣�

			}

			//  if(  random_fun(3,100) )//�ܿ���Ӯ ����һ����Ӯ������Ҫrandomһ�±Ƚϴ�ĸ��� 92/100 �ĸ���Ӯ ��
			//	{  this_chip=0; } //  7/100�ĸ��ʲ���

			//��� ������־���    ����ѹ�úܶ����ǾͲ�թ���ˣ���������������������      �����Ƕ���ѹ�Ĳ�������� ��Ϊ���Ѿ����ˣ�����֤�����ð�
			/*
			   if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2) 
			   ���� rate[7]=maxchip/������ע��*7462  ȡ������max_rate[x]

			   if( (max_rate[x])>pGameParam->uModelValue +1000  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   if( (max_rate[x])>pGameParam->uModelValue +500  )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
			   { 
			   if( random_fun( (max_rate[x]-215),7462) )
			   this_chip=0;

			   }
			   */			
			//����жϱ�֤ ��10%�Ժܸߵĸ��ʲ��棡��
			if(pGameParam->uRaiseNum >= maxchip)//yi Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
			{ 
				if(pGameParam->uModelValue*100/7462<10)  //��10%
				{
					if( random_rate( 103,(7462-pGameParam->uModelValue)/72) )
						pGameParam->uRaiseNum=0;
				}
			}



			if(pGameParam->uStakeTime>=3)//�����������Ѿ��������©�������  �Ҿ����Լ��Ѿ�ѹ�˺ܶ����б�Ҫ��һ�½������  ����ط�Ƿ���ǣ�������������������������������������������
			{ 
				if(pGameParam->uRaiseNum==0) //Need Modify!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111 //���˺ܶ���� �������׷�����
				{ 

					if( pGameParam->uWholeChip>(pGameParam->uWholeChip+pGameParam->uSelfChip)*70/100 )  //maxchipָ������һѹעȦ���ӵ������Ǳ�Ǯ my_chip_inҲָ������һȦѹ�˵Ķ���Ǯ
					{
						if(maxchip - pGameParam->uLastChip <  pGameParam->uSelfChip*12/100)
						{
							pGameParam->uRaiseNum=maxchip;                    //Need modify����������������������������������������������������������������������������
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
							pGameParam->uRaiseNum= maxchip;//modify����������������������������������������������������������������������������
					}
					else 
					{
						if( random_rate( ( pGameParam->uWholeChip+pGameParam->uSelfChip+1),( pGameParam->uWholeChip) ) )
							pGameParam->uRaiseNum= maxchip;//modify����������������������������������������������������������������������������
					}														 
				}
				else{
					if(  random_rate(103,pGameParam->uModelValue/72) )
						pGameParam->uRaiseNum +=  maxchip;
				}

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )     //���ʼӺ͵Ĺ�ϵ
				{
					if( random_rate(100,37) )
						pGameParam->uRaiseNum=pGameParam->uRaiseNum> maxchip ? pGameParam->uRaiseNum: maxchip ;

					if( random_rate( 512,1) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{  pGameParam->uZhahuCarefulFlag=1;      //bluff_flag_careful=1,//թ���ı�־λ

						pGameParam->uRaiseNum +=  maxchip*(2+randoma(7));//���ʺܵ͵�
					}

				}

			}					

		}	
	}

	//action ����

	Strategy_Action(pGameParam,maxchip,rivalnum);
}	
//����Ȧ��ע
else if(pGameParam->uGameState==GAME_RIVER)
{
	pGameParam->uPopChip = pGameParam->inquire_pop;//��ǰ����ע��

	maxchip = 0;
	maxrate = 0;
	rivalnum = 0;
	selfbet = 0;

	for(i=0;i<8;i++)
	{
		//��������ҵ�Ͷע�Ͳ��ԣ��������Ҫ��¼��Ϣ
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

	//����ѡ��������룩
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

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{					 
					if( random_rate( 100,7) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�	 
					}
				}
			}
			else
			{
				if(random_rate(100,92))//�������һ�£�����������������������������������������������������������������������������������������
					pGameParam->uRaiseNum = maxchip;//pGameParam->uRaiseNum = 0;

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{	
					if(random_rate(100,57))
						pGameParam->uRaiseNum = maxchip;

					if( random_rate( 100,7)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
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

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{	
					if(random_rate(100,37))//�����壡��������������������������������������������
						pGameParam->uRaiseNum = maxchip;	

					if( random_rate( 100,7)&& random_rate(103,pGameParam->uModelValue/72)) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
					}	 
				}	
			}
			else if( maxchip - pGameParam->uLastChip < pGameParam->uSelfChip / 4 )
			{
				if(random_rate(maxchip+1,pGameParam->uLastChip+10))
					pGameParam->uRaiseNum = maxchip;	

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{					 
					if(random_rate(100,27))//�����壡��������������������������������������������
						pGameParam->uRaiseNum = maxchip;	

					if( random_rate( 100,7)&& random_rate(103,pGameParam->uModelValue/72)) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
					}		 
				}
			}
			else
			{
				if(random_rate(maxchip+1,pGameParam->uLastChip))
					pGameParam->uRaiseNum = maxchip;	

				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 )    //���ʼӺ͵Ĺ�ϵ
				{	
					if(random_rate(100,21))//�����壡��������������������������������������������
						pGameParam->uRaiseNum = maxchip;	

					if( random_rate( 100,7)&& random_rate(103,pGameParam->uModelValue/72)) //թ����������������������������������������������������������������������������������������������������������������������������
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
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

				if( random_rate( 100,5)&&random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					// this_chip= this_chip + maxchip*(1+randoma(7))*random_rate(103,Value/72);//���ʺܵ͵�
				{
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
				} 

			}

		}

		else 
		{
			if( random_rate((pGameParam->uWholeChip+pGameParam->uSelfChip+1), pGameParam->uWholeChip) )//�����Ѿ�ѹ�˵� +ʣ����ֵ����
			{
				pGameParam->uRaiseNum = maxchip;


				if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
				{
					if( random_rate(100,16) )
						pGameParam->uRaiseNum = maxchip;

					if( random_rate( 100,3)&& random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
						// this_chip= this_chip + maxchip*(1+randoma(7))*random_rate(103,Value/72);//���ʺܵ͵�
					{
						pGameParam->uZhahuFlag=1;
						pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
					} 

				}
			}

			if( rivalnum<= (pGameParam->uPlayerNum-1)/3 ||pGameParam->uPlayerNum==2 ) 
			{
				if( random_rate(100,16) )
					pGameParam->uRaiseNum = maxchip;

				if( random_rate( 100,3) && random_rate(103,pGameParam->uModelValue/72) ) //թ����������������������������������������������������������������������������������������������������������������������������
					// this_chip= this_chip + maxchip*(1+randoma(7))*random_rate(103,Value/72);//���ʺܵ͵�
				{
					pGameParam->uZhahuFlag=1;
					pGameParam->uRaiseNum += maxchip*(1+randoma(7));//���ʺܵ͵�
				} 

			}		 
		}
	}	
	//�϶����������
	if( pGameParam->uWinFlag == PROB_WIN_MIN )//�϶����������
	{
		if( maxchip-pGameParam->uLastChip> (pGameParam->uWholeChip+pGameParam->uSelfChip)*7/10 )
			pGameParam->uRaiseNum=0;
		if(pGameParam->uWholeChip<(pGameParam->uWholeChip+pGameParam->uSelfChip)*10/100)   
			if( maxchip-pGameParam->uLastChip> (pGameParam->uWholeChip+pGameParam->uSelfChip) *5/10 )
				pGameParam->uRaiseNum=0;

		//if(�Ѹ����� ��ǰ��ʣ��ע������myע����1/2)  ���� rate[7]=maxchip*100/������ע��   ȡ������max_rate[x]    
		if( maxrate > 0.9  )   //������ѹ��90%�Ľ�� ֤�������ƿ��ܺ�С��
		{ 
			if( random_rate(100,92) )  //�Ƚ��п����Ƕ���թ���أ�������������������������������������������������������������������������
				pGameParam->uRaiseNum=0;										
		}	
		else if( maxrate > 0.7  )   //�����һ�㲻̫��թ��
		{ 
			if( random_rate(100,(int)(maxrate*100)+7) )
				pGameParam->uRaiseNum=0;
		}
		else if( maxrate>0.5 )   //��7462������ǰ��//if( (max_rate[x])>pGameParam->uModelValue/7462   )  //��7462������ǰ��
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

//����potwin-msg
void GameShowdown(PGAME_PARAM pGameParam)
{
	pGameParam->uGameState = GAME_START;
}

//����potwin-msg
void GamePotwin(PGAME_PARAM pGameParam)
{
	pGameParam->uGameState = GAME_START;
}
