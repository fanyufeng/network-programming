#include "game_global.h"
#include "game_basic.h"
#include "game_process.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//新牌加入存储
void NewAddToCard(Uint8 uCardIn,PGAME_PARAM pGameParam)
{
	Uint8 i;
	
	Uint8 uColor = GetColor(uCardIn);
	Uint8 uValue = GetValue(uCardIn);
	
	//顺子的可能牌处理
	if(uValue==1)
	{
		pGameParam->uFlushStraight[uColor][10]++;
		pGameParam->uFlushStraight[uColor][1]++;
		
		if(pGameParam->uCard[0][uValue]==0)
		{
			pGameParam->uStraight[10]++;
			pGameParam->uStraight[1]++;
		}
	}
	else if(uValue<=5)
	{
		for( i=1; i<=uValue; i++ )
			pGameParam->uFlushStraight[uColor][i]++;

		if(pGameParam->uCard[0][uValue]==0)
		{
			for( i=1; i<=uValue; i++ )
				pGameParam->uStraight[i]++;
		}
	}
	else if(uValue<=10)
	{
		for( i=uValue-4; i<=uValue; i++ )
			pGameParam->uFlushStraight[uColor][i]++;

		if(pGameParam->uCard[0][uValue]==0)
		{
			for( i=uValue-4; i<=uValue; i++ )
				pGameParam->uStraight[i]++;
		}
	}
	else if(uValue<=13)
	{
		for( i=uValue-4; i<=10; i++ )
			pGameParam->uFlushStraight[uColor][i]++;

		if(pGameParam->uCard[0][uValue]==0)
		{
			for( i=uValue-4; i<=10; i++ )
				pGameParam->uStraight[i]++;
		}
	}
	
	pGameParam->uCard[uColor][uValue] = 1;
	pGameParam->uCard[uColor][0]++;
	pGameParam->uCard[0][uValue]++;
	if(uValue==1)
	{
		pGameParam->uCard[uColor][14] = 1;
		pGameParam->uCard[0][14]++;
	}
	
	pGameParam->uCardNum++;

	return;
}

//统计重复类型（单牌，对子，两对，三条，葫芦，炸弹）的关键值
void CardStatByValue(PGAME_PARAM pGameParam)
{
	Uint8 i;
	
	pGameParam->uOneNum = 0;
	pGameParam->uTwoNum = 0;
	pGameParam->uThreeNum = 0;
	pGameParam->uFourNum = 0;
	
	//逻辑值从大到小
	for( i=14; i>=2; i-- )
	{
		switch(pGameParam->uCard[0][i])
		{
		case 0:
			break;
		case 1:
			pGameParam->One[pGameParam->uOneNum++] = i;		
			break;
		case 2:
			pGameParam->Two[pGameParam->uTwoNum++] = i;
			break;
		case 3:
			pGameParam->Three[pGameParam->uThreeNum++] = i;
			break;
		case 4:
			pGameParam->Four = i;
			pGameParam->uFourNum++;
			break;
		default:
			break;
		}
	}
	
	return;
}

//统计同花类型（同花）的关键值
void CardStatByFlush(PGAME_PARAM pGameParam)
{
	Uint8 i,j,k,uColor;
	
	pGameParam->uFlushNum = 0;
	pGameParam->uFlushColor = 0;
	
	for( i=1; i<=4; i++ )
		if( pGameParam->uCard[i][0]>pGameParam->uFlushNum )
	{
			uColor = i;
			pGameParam->uFlushNum = pGameParam->uCard[i][0];
			pGameParam->uFlushColor = uColor;
	}
	
	k=0;
	for( j=14; j>=2; j++ )
	{
		if( pGameParam->uCard[i][j] == 1 )
			pGameParam->Flush[k++] = j;
	}
			
	return;
}

//统计顺子类型（顺子，同花顺）的关键值
void CardStatByStraight(PGAME_PARAM pGameParam)
{
	Uint8 i,j;
	
	pGameParam->uStraightNum = 0;
	pGameParam->uStraightMin = 0;

	pGameParam->uFlushStraightNum = 0;
	pGameParam->uFlushStraightMin = 0;
	pGameParam->uFlushStraightColor = 0;
	
	//普通顺子类型
	for( i=1; i<=10; i++ )
		if( pGameParam->uStraight[i]>=pGameParam->uStraightNum )
		{
			pGameParam->uStraightNum = pGameParam->uStraight[i];
			pGameParam->uStraightMin = i;
		}
	
	//同花顺子类型
	for( i=1; i<=10; i++ )
		for( j=1; j<=4; j++ )
			if( pGameParam->uFlushStraight[j][i]>=pGameParam->uFlushStraightNum )
			{
				pGameParam->uFlushStraightNum = pGameParam->uFlushStraight[j][i];
				pGameParam->uFlushStraightMin = i;
				pGameParam->uFlushStraightColor = j;
			}
	
	return;
}

void strategy_flop(PGAME_PARAM pGameParam)
{
	Uint8 uModel;
	uModel = pipei_fiveinfive(pGameParam);
	
	if(uModel==STRAIGHT_FLUSH || uModel==FOUR_OF_A_KIND)
	{
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_FIVE;
		return;
	}
	else
	{
		if(uModel==FULL_HOUSE)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if(uModel==FLUSH && pGameParam->Flush[2]>=8)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel == STRAIGHT && pGameParam->uStraightMin == 1
			&& GetValue(pGameParam->uSelfCard[0]) != 14
			&& GetValue(pGameParam->uSelfCard[0]) >= 2
			&& GetValue(pGameParam->uSelfCard[1]) >= 2 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel == STRAIGHT && pGameParam->uStraightMin != 1
			&& GetValue(pGameParam->uSelfCard[0]) >= pGameParam->uStraightMin + 1
			&& GetValue(pGameParam->uSelfCard[1]) >= pGameParam->uStraightMin + 1 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && 
			( GetValue(pGameParam->uSelfCard[0])==pGameParam->Three[0]||GetValue(pGameParam->uSelfCard[1])==pGameParam->Three[0]))
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && 
			GetValue(pGameParam->uSelfCard[0])>=13)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}		
		else if( uModel==TWO_PAIR 
			&& GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0] && GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1])
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel==TWO_PAIR 
			&& GetValue(pGameParam->uSelfCard[0]) == GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 11 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel == TWO_PAIR
			&& ( ( pGameParam->Two[0] >= 13 && 
			( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0] 
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0]))
			|| ( pGameParam->Two[1] >= 13 
			&& ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[1]
		  || GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1]) ) ) ) 
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel == ONE_PAIR
			&& GetValue(pGameParam->uSelfCard[0]) == GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 13 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}	
		else if( uModel==FLUSH )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;			
		}
		else if( uModel==STRAIGHT )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && GetValue(pGameParam->uSelfCard[0]) >= 9 )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;				
		}
		else if( uModel==TWO_PAIR )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;				
		}
		else if( uModel==ONE_PAIR && pGameParam->Two[0] >= 9
			&& ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0]
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0]) )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;			
		}
		else if( uModel==THREE_OF_A_KIND )
		{
			pGameParam->uWinFlag = PROB_WIN_MIN;
			pGameParam->uIsAllFlag = FIVE_IN_FIVE;
			return;				
		}
		else
		{
			pipei_fourinfive(pGameParam);
			
			pGameParam->uIsAllFlag = FOUR_IN_FIVE;
			
			return;
		}
	}
}

void strategy_turn(PGAME_PARAM pGameParam)
{
	Uint8 uModel;
	uModel = pipei_fiveinsix(pGameParam);
	
	if(uModel==STRAIGHT_FLUSH)
	{
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_SIX;
		return;
	}
	else if(uModel==FOUR_OF_A_KIND
		&&(GetValue(pGameParam->uSelfCard[0])==pGameParam->Four
		||GetValue(pGameParam->uSelfCard[1])==pGameParam->Four))
	{
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_SIX;
		return;
	}
	else if(uModel==FOUR_OF_A_KIND&&GetValue(pGameParam->uSelfCard[0])==14)
	{
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_SIX;
		return;
	}
	else
	{
		if(uModel==FOUR_OF_A_KIND&&GetValue(pGameParam->uSelfCard[0])>=12)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;			
		}
		else if(uModel==FULL_HOUSE)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if(uModel==FLUSH && pGameParam->Flush[2]>=8)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel == STRAIGHT && pGameParam->uStraightMin == 1
			&& GetValue(pGameParam->uSelfCard[0]) != GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 2
			&& GetValue(pGameParam->uSelfCard[0]) <= 5
			&& GetValue(pGameParam->uSelfCard[1]) >= 2 
			&& GetValue(pGameParam->uSelfCard[1]) <= 5 
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[0])] == 1
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[1])] == 1)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel == STRAIGHT && pGameParam->uStraightMin != 1
			&& GetValue(pGameParam->uSelfCard[0]) != GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= pGameParam->uStraightMin + 1
			&& GetValue(pGameParam->uSelfCard[0]) <= pGameParam->uStraightMin + 4
			&& GetValue(pGameParam->uSelfCard[1]) >= pGameParam->uStraightMin + 1 
			&& GetValue(pGameParam->uSelfCard[1]) <= pGameParam->uStraightMin + 4
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[0])] == 1
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[1])] == 1)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && 
			( GetValue(pGameParam->uSelfCard[0])==pGameParam->Three[0]||GetValue(pGameParam->uSelfCard[1])==pGameParam->Three[0]))
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel==TWO_PAIR 
			&& GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0] && GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1])
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel == TWO_PAIR
			&& GetValue(pGameParam->uSelfCard[0]) == GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 11 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel == TWO_PAIR
			&& ( ( pGameParam->Two[0] >= 13 && 
			( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0] 
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0]))
			|| ( pGameParam->Two[1] >= 13 
			&& ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[1]
		  || GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1]) ) ) ) 
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel == ONE_PAIR
			&& GetValue(pGameParam->uSelfCard[0]) == GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 13 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if(uModel==FOUR_OF_A_KIND&&GetValue(pGameParam->uSelfCard[0])>=8)
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;			
		}
		else if( uModel==FLUSH )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;			
		}
		else if( uModel==STRAIGHT )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && GetValue(pGameParam->uSelfCard[0]) > 9 )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;				
		}//注意匹配
		else if( uModel==TWO_PAIR
			&& ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0]
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0]
			|| GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[1]
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1]))
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;				
		}//注意匹配
		//else if( uModel==TWO_PAIR && GetColor(pGameParam->uSelfCard[0]) != GetColor(pGameParam->uSelfCard[1])
		//&& //注意匹配
		else if( uModel==ONE_PAIR && pGameParam->Two[0] >= 9 
			&& ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0]
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0] ) )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;			
		}//注意匹配
		else if(uModel==FOUR_OF_A_KIND)
		{
			pGameParam->uWinFlag = PROB_WIN_MIN;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;			
		}
		else
		{
			pipei_fourinsix(pGameParam);
			
			pGameParam->uIsAllFlag = FOUR_IN_SIX;
			
			return;
		}
	}	
}

void strategy_river(PGAME_PARAM pGameParam)
{
	Uint8 uModel;
	uModel = pipei_fiveinseven(pGameParam);
	
	if(uModel==STRAIGHT_FLUSH)
	{                                                 
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
		return;
	}
	else if(uModel==FOUR_OF_A_KIND
		&&(GetValue(pGameParam->uSelfCard[0]))==pGameParam->Four
		||(GetValue(pGameParam->uSelfCard[1]))==pGameParam->Four)
	{
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
		return;
	}
	else if(uModel==FOUR_OF_A_KIND&&GetValue(pGameParam->uSelfCard[0])==14)
	{
		pGameParam->uWinFlag = MUST_WIN;
		pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
		return;
	}
	else if(uModel==FULL_HOUSE
		&& pGameParam->uThreeNum == 1
		&& ( GetValue(pGameParam->uSelfCard[0])==pGameParam->Three[0]
		|| GetValue(pGameParam->uSelfCard[1])==pGameParam->Three[0]
		|| GetValue(pGameParam->uSelfCard[0])==pGameParam->Two[0]
		|| GetValue(pGameParam->uSelfCard[1])==pGameParam->Two[0] ))
	{
			pGameParam->uWinFlag = PROB_MUST_WIN;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
	}
	else if(uModel==FULL_HOUSE
		&& pGameParam->uThreeNum == 2
		&& ( GetValue(pGameParam->uSelfCard[0])==pGameParam->Three[0]
		|| GetValue(pGameParam->uSelfCard[1])==pGameParam->Three[0]
		|| GetValue(pGameParam->uSelfCard[0])==pGameParam->Three[1]
		|| GetValue(pGameParam->uSelfCard[1])==pGameParam->Three[1] ))
	{
			pGameParam->uWinFlag = PROB_MUST_WIN;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
	}
	else
	{
		if(uModel==FOUR_OF_A_KIND&&GetValue(pGameParam->uSelfCard[0])>=12)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if(uModel==FULL_HOUSE)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if(uModel==FLUSH && pGameParam->Flush[2]>=8
			&& ( pGameParam->uFlushColor==GetColor(pGameParam->uSelfCard[0])
			|| pGameParam->uFlushColor==GetColor(pGameParam->uSelfCard[1]) ) )//自己手牌的情况
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel == STRAIGHT && pGameParam->uStraightMin == 1
			&& GetValue(pGameParam->uSelfCard[0]) != GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 2//
			&& GetValue(pGameParam->uSelfCard[0]) <= 5//modify
			&& GetValue(pGameParam->uSelfCard[1]) >= 2 
			&& GetValue(pGameParam->uSelfCard[1]) <= 5 //modify
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[0])] == 1
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[1])] == 1)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel == STRAIGHT && pGameParam->uStraightMin != 1
			&& GetValue(pGameParam->uSelfCard[0]) != GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= pGameParam->uStraightMin + 1//也可以等吧
			&& GetValue(pGameParam->uSelfCard[0]) <= pGameParam->uStraightMin + 4
			&& GetValue(pGameParam->uSelfCard[1]) >= pGameParam->uStraightMin + 1 
			&& GetValue(pGameParam->uSelfCard[1]) <= pGameParam->uStraightMin + 4
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[0])] == 1
			&& pGameParam->uCard[0][GetValue(pGameParam->uSelfCard[1])] == 1)
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && 
			( GetValue(pGameParam->uSelfCard[0])==pGameParam->Three[0]||GetValue(pGameParam->uSelfCard[1])==pGameParam->Three[0]))
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel==TWO_PAIR 
			&& GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0] 
			&& GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1])
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel == TWO_PAIR
			&& GetValue(pGameParam->uSelfCard[0]) == GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 11 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel == ONE_PAIR
			&& GetValue(pGameParam->uSelfCard[0]) == GetValue(pGameParam->uSelfCard[1])
			&& GetValue(pGameParam->uSelfCard[0]) >= 13 )
		{
			pGameParam->uWinFlag = PROB_WIN_MAX;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if(uModel==FOUR_OF_A_KIND&&GetValue(pGameParam->uSelfCard[0])>=8)
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SIX;
			return;			
		}
		else if( uModel==FLUSH )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;			
		}
		else if( uModel==STRAIGHT )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;
		}
		else if( uModel==THREE_OF_A_KIND && GetValue(pGameParam->uSelfCard[0]) > 9 )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;				
		}
		else if( uModel==TWO_PAIR
			&& ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0]
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0]
			|| GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[1]
			|| GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[1]))
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;				
		}		
		else if( uModel==ONE_PAIR 
			&& ( ( GetValue(pGameParam->uSelfCard[0]) == pGameParam->Two[0] && pGameParam->Two[0] >= 9 )
			|| ( GetValue(pGameParam->uSelfCard[1]) == pGameParam->Two[0] && pGameParam->Two[0] >= 9 ) ) )
		{
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;			
		}
		else if(uModel==FOUR_OF_A_KIND)
		{
			pGameParam->uWinFlag = PROB_WIN_MIN;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;			
		}
		else if( uModel==THREE_OF_A_KIND )
		{
			pGameParam->uWinFlag = PROB_WIN_MIN;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			return;				
		}
		else
		{
			pGameParam->uWinFlag = PROB_WIN_MIN;
			pGameParam->uIsAllFlag = FIVE_IN_SEVEN;
			
			return;
		}
	}	
}

int random_rate(Uint16 max, Uint16 refer)
{
	Uint16 i;
	srand((unsigned)time(NULL));

	i=(rand()%max);
	if(i<=refer)return 1;
	else return 0;
}

int randoma(Uint16 max)
{
	srand((unsigned)time(NULL));
	
	return (rand()%max);	
}

Uint8 pipei_fiveinfive(PGAME_PARAM pGameParam)
	{	
		Uint8 i;
		Uint16 sum;
		
		if(pGameParam->uFlushStraightNum >= 5)
		{
			pGameParam->uModelValue = 7452 + pGameParam->uFlushStraightMin;
			return STRAIGHT_FLUSH;
		}
			
		if(pGameParam->uFourNum > 0)
		{
			pGameParam->uModelValue = 7452 - (14-pGameParam->Four)*12 - (14-(pGameParam->One[0]<pGameParam->Four?pGameParam->One[0]+1:pGameParam->One[0]));
			return FOUR_OF_A_KIND;
		}
				
		if(pGameParam->uThreeNum > 0 && pGameParam->uTwoNum > 0)
		{
			pGameParam->uModelValue = 7296 - (14-pGameParam->Three[0])*12 - (14-(pGameParam->Two[0]<pGameParam->Three[0]?pGameParam->Two[0]+1:pGameParam->Two[0]));
			return FULL_HOUSE;
		}
		
		if(pGameParam->uFlushNum >= 5)
		{
			sum = 0;
			for(i=6;i<pGameParam->Flush[0];i++)
			{
				sum+=(i-2)*(i-3)*(i-4)*(i-5)/24;
			}
			for(i=5;i<pGameParam->Flush[1];i++)
			{
				sum+=(i-2)*(i-3)*(i-4)/6;
			}
			for(i=4;i<pGameParam->Flush[2];i++)
			{
				sum+=(i-2)*(i-3)/2;
			}
			for(i=3;i<pGameParam->Flush[3];i++)
			{
				sum+=i-2;
			}
			
			sum+=pGameParam->Flush[4]-2;
			
			pGameParam->uModelValue = 5864 + sum;
			
			return FLUSH;
		}
			
		if(pGameParam->uStraightNum >= 5)
		{
			pGameParam->uModelValue = 5853 + pGameParam->uStraightMin;
			return STRAIGHT;
		}
			
		if(pGameParam->uThreeNum > 0 && pGameParam->uTwoNum == 0)
		{
			sum = 0;

			sum += 66 * (pGameParam->Three[0] - 2);
			for(i=3;i<pGameParam->One[0];i++)
			{
				sum+=i>pGameParam->Three[0]?i-3:i-2;;
			}
			sum+=pGameParam->One[1]>pGameParam->Three[0]?pGameParam->One[1]-3:pGameParam->One[1]-2;
			
			pGameParam->uModelValue = 4996 + sum;
			
			return THREE_OF_A_KIND;
		}
			
		if(pGameParam->uTwoNum >= 2)
		{
			sum = 0;
			
			for(i=3;i<pGameParam->Two[0];i++)
			{
				sum+=i-2;
			}
			sum+=pGameParam->Two[1]-2;
			
			sum*=11;
			
			if(pGameParam->One[0]>pGameParam->Two[0])
				sum+=pGameParam->One[0]-4;
			else if(pGameParam->One[0]>pGameParam->Two[1])
				sum+=pGameParam->One[0]-3;
			else
				sum+=pGameParam->One[0]-2;
				
			pGameParam->uModelValue = 4138 + sum;
			
			return TWO_PAIR;
		}
		
		if(pGameParam->uTwoNum == 1)
		{
			sum = 0;
			
			sum+=(pGameParam->Two[0]-2)*12*11*10/6;
			
			for(i=4;i<pGameParam->One[0];i++)
			{
				sum+=i>pGameParam->Two[0]?(i-4)*(i-3)/2:(i-3)*(i-2)/2;
			}
			for(i=3;i<pGameParam->One[1];i++)
			{
				sum+=i>pGameParam->Two[0]?i-3:i-2;
			}
			sum+=pGameParam->One[2]>pGameParam->Two[0]?pGameParam->One[2]-3:pGameParam->One[2]-2;
				
			pGameParam->uModelValue = 1278 + sum;
			
			return ONE_PAIR;
		}
			
		sum = 0;
		for(i=6;i<pGameParam->One[0];i++)
		{
			sum+=(i-2)*(i-3)*(i-4)*(i-5)/24;
		}
		for(i=5;i<pGameParam->One[1];i++)
		{
			sum+=(i-2)*(i-3)*(i-4)/6;
		}
		for(i=4;i<pGameParam->One[2];i++)
		{
			sum+=(i-2)*(i-3)/2;
		}
		for(i=3;i<pGameParam->One[3];i++)
		{
			sum+=i-2;
		}
		
		sum+=pGameParam->One[4]-2;
		
		pGameParam->uModelValue = 1 + sum;
			
		return HIGH_CARD;
	}

void pipei_fourinfive(PGAME_PARAM pGameParam)
{
	Uint32 temp;
	
	if(pGameParam->uFlushStraightNum == 4)
	{
		if(pGameParam->uCard[pGameParam->uFlushStraightColor][pGameParam->uFlushStraightMin+1]==1
			&&pGameParam->uCard[pGameParam->uFlushStraightColor][pGameParam->uFlushStraightMin+2]==1
			&&pGameParam->uCard[pGameParam->uFlushStraightColor][pGameParam->uFlushStraightMin+3]==1)
		{
			if(1==random_rate(250,21))
			{
				pGameParam->uModelValue = pGameParam->uModelValue * 4 / 5 
					+ (7452+pGameParam->uFlushStraightMin)/5;
				pGameParam->uWinFlag = PROB_WIN_MAX;
				return;
			}
		}
		else
		{
			if(1==random_rate(500,21))
			{
				pGameParam->uModelValue = pGameParam->uModelValue * 4 / 5 
					+ (7452+pGameParam->uFlushStraightMin)/5;
				pGameParam->uWinFlag = PROB_WIN_MAX;
				return;
			}
		}
	}
	
	if(pGameParam->uFlushNum == 4)
	{
		if(1==random_rate(100,35))
		{
			pGameParam->uModelValue =
				pGameParam->uModelValue * 4 / 5 + 6502 / 5;
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			return;
		}
	}

	if(pGameParam->uStraightNum == 4)
	{			
		if(pGameParam->uCard[0][pGameParam->uStraightMin+1]>=1
			&&pGameParam->uCard[0][pGameParam->uStraightMin+2]>=1
			&&pGameParam->uCard[0][pGameParam->uStraightMin+3]>=1)
		{
			if(1==random_rate(10,3))
			{
				pGameParam->uModelValue =
					pGameParam->uModelValue * 4 / 5 + (5853 + pGameParam->uStraightMin) / 5;
				pGameParam->uWinFlag = PROB_WIN_MIDDLE;
				return;		
			}
		}
		else
		{
			if(1==random_rate(250,41))
			{
				pGameParam->uModelValue =
					pGameParam->uModelValue * 4 / 5 + (5853 + pGameParam->uStraightMin) / 5;
				pGameParam->uWinFlag = PROB_WIN_MIDDLE;
				return;				
			}				
		}
	}

	pGameParam->uWinFlag = PROB_WIN_MIN;
	
	return;
}

Uint8 pipei_fiveinsix(PGAME_PARAM pGameParam)
{	
	Uint8 i;
	Uint16 sum;
	
	if(pGameParam->uFlushStraightNum >= 5)
	{
		pGameParam->uModelValue = 7452 + pGameParam->uFlushStraightMin;
		return STRAIGHT_FLUSH;
	}
		
	if(pGameParam->uFourNum > 0)
	{
		if(pGameParam->uOneNum>0)
			pGameParam->uModelValue = 7452 - (14-pGameParam->Four)*12 - (14-(pGameParam->One[0]<pGameParam->Four?pGameParam->One[0]+1:pGameParam->One[0]));
		else
			pGameParam->uModelValue = 7452 - (14-pGameParam->Four)*12 - (14-(pGameParam->Two[0]<pGameParam->Four?pGameParam->Two[0]+1:pGameParam->Two[0]));
		return FOUR_OF_A_KIND;
	}
			
	if(pGameParam->uThreeNum == 1 && pGameParam->uTwoNum == 1)
	{
		pGameParam->uModelValue = 7296 - (14-pGameParam->Three[0])*12 - (14-(pGameParam->Two[0]<pGameParam->Three[0]?pGameParam->Two[0]+1:pGameParam->Two[0]));
		return FULL_HOUSE;
	}
	else if(pGameParam->uThreeNum == 2)
	{
		sum = 0;
		for(i=3;i<pGameParam->Three[0];i++)
		{
			sum+=(i-2);
		}
		sum+=pGameParam->Three[1]-2;
		
		pGameParam->uModelValue = 7141 + sum;
			
		return FULL_HOUSE;		
	}
	
	if(pGameParam->uFlushNum >= 5)
	{
		sum = 0;
		for(i=6;i<pGameParam->Flush[0];i++)
		{
			sum+=(i-2)*(i-3)*(i-4)*(i-5)/24;
		}
		for(i=5;i<pGameParam->Flush[1];i++)
		{
			sum+=(i-2)*(i-3)*(i-4)/6;
		}
		for(i=4;i<pGameParam->Flush[2];i++)
		{
			sum+=(i-2)*(i-3)/2;
		}
		for(i=3;i<pGameParam->Flush[3];i++)
		{
			sum+=i-2;
		}
		
		sum+=pGameParam->Flush[4]-2;
		
		pGameParam->uModelValue = 5864 + sum;
		
		return FLUSH;
	}
		
	if(pGameParam->uStraightNum >= 5)
	{
		pGameParam->uModelValue = 5853 + pGameParam->uStraightMin;
		return STRAIGHT;
	}
		
	if(pGameParam->uThreeNum > 0 && pGameParam->uTwoNum == 0)
	{
		sum = 0;

		sum += 66 * (pGameParam->Three[0] - 2);
		for(i=3;i<pGameParam->One[0];i++)
		{
			sum+=i>pGameParam->Three[0]?i-3:i-2;
		}
		sum+=pGameParam->One[1]>pGameParam->Three[0]?pGameParam->One[1]-3:pGameParam->One[1]-2;
		
		pGameParam->uModelValue = 4996 + sum;
		
		return THREE_OF_A_KIND;
	}
		
	if(pGameParam->uTwoNum == 2)
	{
		sum = 0;
		
		for(i=3;i<pGameParam->Two[0];i++)
		{
			sum+=i-2;
		}
		sum+=pGameParam->Two[1]-2;
		
		sum*=11;
		
		if(pGameParam->One[0]>pGameParam->Two[0])
			sum+=pGameParam->One[0]-4;
		else if(pGameParam->One[0]>pGameParam->Two[1])
			sum+=pGameParam->One[0]-3;
		else
			sum+=pGameParam->One[0]-2;
			
		pGameParam->uModelValue = 4138 + sum;
		
		return TWO_PAIR;
	}
	else if(pGameParam->uTwoNum == 3)
	{
		sum = 0;
		
		for(i=4;i<pGameParam->Two[0];i++)
		{
			sum+=(i-2)*(i-3)/2;
		}
		for(i=3;i<pGameParam->Two[1];i++)
		{
			sum+=(i-2);
		}
		sum+=pGameParam->Two[2]-2;
		
		pGameParam->uModelValue = 4138 + sum;
		
		return TWO_PAIR;
	}
	
	if(pGameParam->uTwoNum == 1)
	{
		sum = 0;
		
		sum+=(pGameParam->Two[0]-2)*12*11*10/6;
		
		for(i=4;i<pGameParam->One[0];i++)
		{
			sum+=i>pGameParam->Two[0]?(i-4)*(i-3)/2:(i-3)*(i-2)/2;
		}
		for(i=3;i<pGameParam->One[1];i++)
		{
			sum+=i>pGameParam->Two[0]?i-3:i-2;
		}
		sum+=pGameParam->One[2]>pGameParam->Two[0]?pGameParam->One[2]-3:pGameParam->One[2]-2;
			
		pGameParam->uModelValue = 1278 + sum;
		
		return ONE_PAIR;
	}
		
	sum = 0;
	for(i=6;i<pGameParam->One[0];i++)
	{
		sum+=(i-2)*(i-3)*(i-4)*(i-5)/24;
	}
	for(i=5;i<pGameParam->One[1];i++)
	{
		sum+=(i-2)*(i-3)*(i-4)/6;
	}
	for(i=4;i<pGameParam->One[2];i++)
	{
		sum+=(i-2)*(i-3)/2;
	}
	for(i=3;i<pGameParam->One[3];i++)
	{
		sum+=i-2;
	}
	
	sum+=pGameParam->One[4]-2;
	
	pGameParam->uModelValue = 1 + sum;
		
	return HIGH_CARD;
}

void pipei_fourinsix(PGAME_PARAM pGameParam)
{
	if(pGameParam->uFlushStraightNum == 4)
	{
		if(pGameParam->uCard[pGameParam->uFlushStraightColor][pGameParam->uFlushStraightMin+1]==1
			&&pGameParam->uCard[pGameParam->uFlushStraightColor][pGameParam->uFlushStraightMin+2]==1
			&&pGameParam->uCard[pGameParam->uFlushStraightColor][pGameParam->uFlushStraightMin+3]==1)
		{
			if(1==random_rate(250,11))
			{
				pGameParam->uModelValue = pGameParam->uModelValue * 4 / 5 
					+ (7452+pGameParam->uFlushStraightMin)/5;
				pGameParam->uWinFlag = PROB_WIN_MAX;
				return;
			}
		}
		else
		{
			if(1==random_rate(500,11))
			{
				pGameParam->uModelValue = pGameParam->uModelValue * 4 / 5 
					+ (7452+pGameParam->uFlushStraightMin)/5;
				pGameParam->uWinFlag = PROB_WIN_MAX;
				return;	
			}
		}
	}
	
	if(pGameParam->uFlushNum == 4)
	{
		if(1==random_rate(5,1))
		{
			pGameParam->uModelValue =
				pGameParam->uModelValue * 4 / 5 + 6502 / 5;
			pGameParam->uWinFlag = PROB_WIN_MIDDLE;
			return;			
		}
	}

	if(pGameParam->uStraightNum == 4)
	{			
		if(pGameParam->uCard[0][pGameParam->uStraightMin+1]>=1
			&&pGameParam->uCard[0][pGameParam->uStraightMin+2]>=1
			&&pGameParam->uCard[0][pGameParam->uStraightMin+3]>=1)
		{
			if(1==random_rate(6,1))
			{
				pGameParam->uModelValue =
					pGameParam->uModelValue * 4 / 5 + (5853 + pGameParam->uStraightMin) / 5;
				pGameParam->uWinFlag = PROB_WIN_MIDDLE;
				return;					
			}	
		}
		else
		{
			if(1==random_rate(12,1))
			{
				pGameParam->uModelValue =
					pGameParam->uModelValue * 4 / 5 + (5853 + pGameParam->uStraightMin) / 5;
				pGameParam->uWinFlag = PROB_WIN_MIDDLE;
				return;
			}			
		}
	}

	pGameParam->uWinFlag = PROB_WIN_MIN;
	
	return;
}

Uint8 pipei_fiveinseven(PGAME_PARAM pGameParam)
{	
	Uint8 i;
	Uint16 sum;
	
	if(pGameParam->uFlushStraightNum >= 5)
	{
		pGameParam->uModelValue = 7452 + pGameParam->uFlushStraightMin;
		return STRAIGHT_FLUSH;
	}
		
	if(pGameParam->uFourNum > 0)
	{
		if(pGameParam->uThreeNum>0)
			pGameParam->uModelValue = 7452 - (14-pGameParam->Four)*12 - (14-(pGameParam->Three[0]<pGameParam->Four?pGameParam->Three[0]+1:pGameParam->Three[0]));
		else if(pGameParam->uTwoNum>0&&pGameParam->Two[0]>pGameParam->One[0])
			pGameParam->uModelValue = 7452 - (14-pGameParam->Four)*12 - (14-(pGameParam->Two[0]<pGameParam->Four?pGameParam->Two[0]+1:pGameParam->Two[0]));
		else
			pGameParam->uModelValue = 7452 - (14-pGameParam->Four)*12 - (14-(pGameParam->One[0]<pGameParam->Four?pGameParam->One[0]+1:pGameParam->One[0]));
		
		return FOUR_OF_A_KIND;
	}
			
	if(pGameParam->uThreeNum == 1 && pGameParam->uTwoNum >= 1)
	{
		pGameParam->uModelValue = 7296 - (14-pGameParam->Three[0])*12 - (14-(pGameParam->Two[0]<pGameParam->Three[0]?pGameParam->Two[0]+1:pGameParam->Two[0]));
		return FULL_HOUSE;
	}
	else if(pGameParam->uThreeNum == 2)
	{
		sum = 0;
		for(i=3;i<pGameParam->Three[0];i++)
		{
			sum+=(i-2);
		}
		sum+=pGameParam->Three[1]-2;
		
		pGameParam->uModelValue = 7141 + sum;
			
		return FULL_HOUSE;		
	}
	
	if(pGameParam->uFlushNum >= 5)
	{
		sum = 0;
		for(i=6;i<pGameParam->Flush[0];i++)
		{
			sum+=(i-2)*(i-3)*(i-4)*(i-5)/24;
		}
		for(i=5;i<pGameParam->Flush[1];i++)
		{
			sum+=(i-2)*(i-3)*(i-4)/6;
		}
		for(i=4;i<pGameParam->Flush[2];i++)
		{
			sum+=(i-2)*(i-3)/2;
		}
		for(i=3;i<pGameParam->Flush[3];i++)
		{
			sum+=i-2;
		}
		
		sum+=pGameParam->Flush[4]-2;
		
		pGameParam->uModelValue = 5864 + sum;
		
		return FLUSH;
	}
		
	if(pGameParam->uStraightNum >= 5)
	{
		pGameParam->uModelValue = 5853 + pGameParam->uStraightMin;
		return STRAIGHT;
	}
		
	if(pGameParam->uThreeNum > 0 && pGameParam->uTwoNum == 0)
	{
		sum = 0;

		sum += 66 * (pGameParam->Three[0] - 2);
		for(i=3;i<pGameParam->One[0];i++)
		{
			sum+=i>pGameParam->Three[0]?i-3:i-2;
		}
		sum+=pGameParam->One[1]>pGameParam->Three[0]?pGameParam->One[1]-3:pGameParam->One[1]-2;
		
		pGameParam->uModelValue = 4996 + sum;
		
		return THREE_OF_A_KIND;
	}
		
	if(pGameParam->uTwoNum == 2)
	{
		sum = 0;
		
		for(i=3;i<pGameParam->Two[0];i++)
		{
			sum+=i-2;
		}
		sum+=pGameParam->Two[1]-2;
		
		sum*=11;
		
		if(pGameParam->One[0]>pGameParam->Two[0])
			sum+=pGameParam->One[0]-4;
		else if(pGameParam->One[0]>pGameParam->Two[1])
			sum+=pGameParam->One[0]-3;
		else
			sum+=pGameParam->One[0]-2;
			
		pGameParam->uModelValue = 4138 + sum;
		
		return TWO_PAIR;
	}
	else if(pGameParam->uTwoNum == 3)
	{
		sum = 0;
		
		for(i=4;i<pGameParam->Two[0];i++)
		{
			sum+=(i-2)*(i-3)/2;
		}
		for(i=3;i<pGameParam->Two[1];i++)
		{
			sum+=(i-2);
		}
		sum+=pGameParam->Two[2]-2;
		
		pGameParam->uModelValue = 4138 + sum;
		
		return TWO_PAIR;
	}
	
	if(pGameParam->uTwoNum == 1)
	{
		sum = 0;
		
		sum+=(pGameParam->Two[0]-2)*12*11*10/6;
		
		for(i=4;i<pGameParam->One[0];i++)
		{
			sum+=i>pGameParam->Two[0]?(i-4)*(i-3)/2:(i-3)*(i-2)/2;
		}
		for(i=3;i<pGameParam->One[1];i++)
		{
			sum+=i>pGameParam->Two[0]?i-3:i-2;
		}
		sum+=pGameParam->One[2]>pGameParam->Two[0]?pGameParam->One[2]-3:pGameParam->One[2]-2;
			
		pGameParam->uModelValue = 1278 + sum;
		
		return ONE_PAIR;
	}
		
	sum = 0;
	for(i=6;i<pGameParam->One[0];i++)
	{
		sum+=(i-2)*(i-3)*(i-4)*(i-5)/24;
	}
	for(i=5;i<pGameParam->One[1];i++)
	{
		sum+=(i-2)*(i-3)*(i-4)/6;
	}
	for(i=4;i<pGameParam->One[2];i++)
	{
		sum+=(i-2)*(i-3)/2;
	}
	for(i=3;i<pGameParam->One[3];i++)
	{
		sum+=i-2;
	}
	
	sum+=pGameParam->One[4]-2;
	
	pGameParam->uModelValue = 1 + sum;
		
	return HIGH_CARD;
}
