//ȫ�ֱ���ͷ�ļ�

#ifndef _GAME_GLOBAL_H_
#define _GAME_GLOBAL_H_

#include "game_global.h"

#define Uint8 unsigned char
#define Uint16 unsigned short int
#define Uint32 unsigned int

#define GetColor(card) ((card&0xF0)>>4)
#define GetValue(card) (card&0x0F)

#define MAX_ACCESS_JETTON 2000
#define BIG_BLIND 40

#define GAME_START 10
#define GAME_PRE 11
#define GAME_FLOP 12
#define GAME_TURN 13
#define GAME_RIVER 14
#define GAME_COMPLETE 15
#define GAME_END 16

#define STRATEGY_BLIND 20
#define STRATEGY_CHECK 21
#define STRATEGY_CALL 22
#define STRATEGY_RAISE 23
#define STRATEGY_ALLIN 24
#define STRATEGY_FOLD 25

#define STRAIGHT_FLUSH 31 //ͬ��˳
#define FOUR_OF_A_KIND 32 //����
#define FULL_HOUSE 33 //��«
#define FLUSH 34 //ͬ��
#define STRAIGHT 35 //˳��
#define THREE_OF_A_KIND 36 //����
#define TWO_PAIR 37 //����
#define ONE_PAIR 38 //һ��
#define HIGH_CARD 39 //����

#define MUST_WIN 40
#define PROB_WIN_MAX 41
#define PROB_WIN_MIDDLE 42
#define PROB_WIN_MIN 43
#define PROB_MUST_WIN  44

#define FIVE_IN_FIVE 50
#define FOUR_IN_FIVE 51
#define FIVE_IN_SIX 52
#define FOUR_IN_SIX 53
#define FIVE_IN_SEVEN 54

#define BUFFER_SIZE 1024



//PGAME_PARAM pGameParam;
int client_socket_fd;        //�׽��ִ�������
//char *decision;              //����


#if 0
char puke[4][13]={
	{0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D},
	{0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D},
	{0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D},
	{0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D},	
};
#endif

typedef struct Seat{
   Uint32  pid;
	 Uint32  jetton;
	 Uint32  money;
}SeatMsg;

//äע��Ϣ
typedef struct Blind{
	Uint32 pid;
	Uint32 bet;
}BlindMsg;


typedef struct hold{
	char color;
	char point;
	int pai;
}HoldPa;

typedef struct flop{
	char flop_color;
	char flop_point;
	int flop_pai;
}FlopPa;

//������Ϣ
typedef struct Holden{
	Uint8 card; 
}HoldMsg;

//ѯ����Ϣ
typedef struct Inquire{
	Uint32 pid;
	Uint32 jetton;
	Uint32 money;
	Uint32 bet;
	int  strategy;//6�ֲ��ԣ������к궨��
}InquireMsg;

//��������Ϣ
typedef struct Flopen{
	Uint8 card; 
}FlopMsg;

//ת����Ϣ
typedef struct Turn{
	Uint8 card;
}TurnMsg;

//������Ϣ
typedef struct River{
	Uint8 card;
}RiverMsg;

//�ʳط�����Ϣ
typedef struct Potwin{
	Uint32 pid;
	Uint32 num;
}PotwinMsg;

typedef struct _GAME_PARAM
{
	Uint16 uId;
	char Name[20];
	
	//������Ϣ
	SeatMsg button_message;
	SeatMsg small_blind_message;
	SeatMsg big_blind_message;
	SeatMsg common_message1;
	SeatMsg common_message2;
	SeatMsg common_message3;
	SeatMsg common_message4;
	SeatMsg common_message5;
	
	//äע��Ϣ
	BlindMsg sblind_msg;//Сäע��Ϣ
	BlindMsg bblind_msg;//��äע��Ϣ
	
	//ѯ����Ϣ
	InquireMsg inquire_msg[8];
	Uint32 inquire_pop;//��Ϣ��Я���Ľ��ؽ��
	
	//����������Ϣ
	HoldMsg hold_msg[2];

	//���Ź�������Ϣ
	FlopMsg flop_msg[3];
	
	//ת����Ϣ
	TurnMsg turn_msg;
	
	//������Ϣ
	RiverMsg river_msg;
	
	//̯����Ϣ
//	ShowdownMsg showdown_msg;
	
	//�ʳط�����Ϣ
	PotwinMsg potwin_msg[8];
	
	Uint8 uGameState;//״ָ̬ʾ
	Uint8 uGameNum;//�ѱȳ�����
	
	Uint8 uPlayerNum;//��ǰδ�Ʋ������
	Uint8 uCurrentNum;//��ǰ�ƾ�ʣ�������
	Uint8 uCardNum;//��ǰ�ѳ�����
	Uint8 uCard[5][15];//���Ƶ�Ԫ
	Uint8 uSelfCard[2];
	Uint8 uCommonCard[5];
	
	
	Uint8 uStraight[11];//��1��ʼ��Ч����ʾ����ֵ��ʼ+4��Χ�ڵ���������
	Uint8 uFlushStraight[5][11];//��[x][1]��ʼ��Ч����ʾĳ��ɫ+4��Χ�ڵ���������
	Uint32 uSelfChip;//�������
	Uint32 uSelfGold;//������
	Uint32 uPopChip;//���س���
	Uint32 uMaxChip;//�������ֵ�ǰ�������Ͷע��
	Uint32 uSumChip;//�Լ������ڵ�ǰͶע��
	Uint8 uOneNum;//���Ÿ���
	Uint8 uTwoNum;//�ɶԸ���
	Uint8 uThreeNum;//��������
	Uint8 uFourNum;//��������
	Uint8 One[7];//��������������
	Uint8 Two[3];//��������������
	Uint8 Three[2];//��������������
	Uint8 Four;//����������
	Uint8 uStraightNum;//˳��ƥ�����ʱ������
	Uint8 uFlushStraightNum;//��1��ʼ��Ч��ͬ��˳ƥ�����ʱ������
	Uint8 uFlushStraightColor;
	Uint8 uStraightMin;//˳��ƥ���������ʱ����С��
	Uint8 uFlushStraightMin;//��1��ʼ��Ч��ͬ��˳ƥ���������ʱ����С��
	Uint8 uFlushNum;//ͬ�������Ŀ
	Uint8 uFlushColor;
	Uint8 Flush[13];//ͬ���Ƽ�¼����
	
	Uint8 uWinFlag;
	Uint8 uIsAllFlag;
	Uint16 uModelValue;

	Uint8 total_num  ;     //��ǰ�׳��ܽ��
	//��ǰ��ע����
	Uint8 uStrategy;
	Uint32 uRaiseNum;//��ע���
	Uint32 uLastChip;//�Լ����ϴ���ע���
	Uint32 uWholeChip;//�Լ�������Ѻע��
	
	Uint8 uStakeTime;
	Uint8 uSeatNum;
	
	Uint8 uFoldFlag;
	Uint8 uCheckFlag;
	Uint8 uCallFlag;
	Uint8 uRaiseFlag;
	Uint8 uAllinFlag;
	Uint8 uMustWinFlag;//��Ҫ�������ı�־λ����Ϊ�϶�Ӯ
	Uint8 uProbWinMaxFlag;//�ܿ���Ӯ�ı�־λ��һ�����ʸ������
	Uint8 uZhahuFlag;
	Uint8 uNextActiveFlag;

	Uint8 uZhahuCarefulFlag;
}GAME_PARAM,*PGAME_PARAM;

#endif
