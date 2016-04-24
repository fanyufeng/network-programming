//全局变量头文件

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

#define STRAIGHT_FLUSH 31 //同花顺
#define FOUR_OF_A_KIND 32 //四条
#define FULL_HOUSE 33 //葫芦
#define FLUSH 34 //同花
#define STRAIGHT 35 //顺子
#define THREE_OF_A_KIND 36 //三条
#define TWO_PAIR 37 //两对
#define ONE_PAIR 38 //一对
#define HIGH_CARD 39 //高牌

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
int client_socket_fd;        //套接字传参链接
//char *decision;              //决策


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

//盲注消息
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

//手牌消息
typedef struct Holden{
	Uint8 card; 
}HoldMsg;

//询问消息
typedef struct Inquire{
	Uint32 pid;
	Uint32 jetton;
	Uint32 money;
	Uint32 bet;
	int  strategy;//6种策略，上面有宏定义
}InquireMsg;

//公共牌消息
typedef struct Flopen{
	Uint8 card; 
}FlopMsg;

//转牌消息
typedef struct Turn{
	Uint8 card;
}TurnMsg;

//河牌信息
typedef struct River{
	Uint8 card;
}RiverMsg;

//彩池分配信息
typedef struct Potwin{
	Uint32 pid;
	Uint32 num;
}PotwinMsg;

typedef struct _GAME_PARAM
{
	Uint16 uId;
	char Name[20];
	
	//座次信息
	SeatMsg button_message;
	SeatMsg small_blind_message;
	SeatMsg big_blind_message;
	SeatMsg common_message1;
	SeatMsg common_message2;
	SeatMsg common_message3;
	SeatMsg common_message4;
	SeatMsg common_message5;
	
	//盲注信息
	BlindMsg sblind_msg;//小盲注信息
	BlindMsg bblind_msg;//大盲注信息
	
	//询问信息
	InquireMsg inquire_msg[8];
	Uint32 inquire_pop;//消息中携带的奖池金额
	
	//两张手牌信息
	HoldMsg hold_msg[2];

	//三张公共牌信息
	FlopMsg flop_msg[3];
	
	//转牌信息
	TurnMsg turn_msg;
	
	//河牌信息
	RiverMsg river_msg;
	
	//摊牌信息
//	ShowdownMsg showdown_msg;
	
	//彩池分配信息
	PotwinMsg potwin_msg[8];
	
	Uint8 uGameState;//状态指示
	Uint8 uGameNum;//已比场次数
	
	Uint8 uPlayerNum;//当前未破产玩家数
	Uint8 uCurrentNum;//当前牌局剩余玩家数
	Uint8 uCardNum;//当前已出牌数
	Uint8 uCard[5][15];//卡牌单元
	Uint8 uSelfCard[2];
	Uint8 uCommonCard[5];
	
	
	Uint8 uStraight[11];//从1开始有效，表示该牌值开始+4范围内的现有牌数
	Uint8 uFlushStraight[5][11];//从[x][1]开始有效，表示某花色+4范围内的现有牌数
	Uint32 uSelfChip;//自身筹码
	Uint32 uSelfGold;//自身金币
	Uint32 uPopChip;//奖池筹码
	Uint32 uMaxChip;//其他牌手当前环节最大投注额
	Uint32 uSumChip;//自己本环节当前投注额
	Uint8 uOneNum;//单张个数
	Uint8 uTwoNum;//成对个数
	Uint8 uThreeNum;//三条个数
	Uint8 uFourNum;//四条个数
	Uint8 One[7];//单张排序牌数组
	Uint8 Two[3];//两张排序牌数组
	Uint8 Three[2];//三条排序牌数组
	Uint8 Four;//四条排序牌
	Uint8 uStraightNum;//顺子匹配最多时的牌数
	Uint8 uFlushStraightNum;//从1开始有效，同花顺匹配最多时的牌数
	Uint8 uFlushStraightColor;
	Uint8 uStraightMin;//顺子匹配牌数最多时的最小牌
	Uint8 uFlushStraightMin;//从1开始有效，同花顺匹配牌数最多时的最小牌
	Uint8 uFlushNum;//同花最大数目
	Uint8 uFlushColor;
	Uint8 Flush[13];//同花牌记录数组
	
	Uint8 uWinFlag;
	Uint8 uIsAllFlag;
	Uint16 uModelValue;

	Uint8 total_num  ;     //当前底池总金额
	//当前下注策略
	Uint8 uStrategy;
	Uint32 uRaiseNum;//加注金额
	Uint32 uLastChip;//自己的上次下注金额
	Uint32 uWholeChip;//自己本局已押注数
	
	Uint8 uStakeTime;
	Uint8 uSeatNum;
	
	Uint8 uFoldFlag;
	Uint8 uCheckFlag;
	Uint8 uCallFlag;
	Uint8 uRaiseFlag;
	Uint8 uAllinFlag;
	Uint8 uMustWinFlag;//需要跟到最后的标志位，认为肯定赢
	Uint8 uProbWinMaxFlag;//很可能赢的标志位，一定概率跟到最后
	Uint8 uZhahuFlag;
	Uint8 uNextActiveFlag;

	Uint8 uZhahuCarefulFlag;
}GAME_PARAM,*PGAME_PARAM;

#endif
