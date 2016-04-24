#ifndef _GAME_PROCESS_H_
#define _GAME_PROCESS_H_

#include "game_process.h"


void GameInit( PGAME_PARAM pGameParam );
void DealSeat(char *ptr,PGAME_PARAM GameParam);
void DealBlind(char *ptrpdb,PGAME_PARAM GameParam);
int  PukePipei(char  color1,char point1 );
void DealHold(char *phold,PGAME_PARAM GameParam);
void DealInquire(char *pask,PGAME_PARAM GameParam);
void DealFlop(char *pflop,PGAME_PARAM GameParam);
void DealTurn(char *ptrturn,PGAME_PARAM GameParam);
void DealRiver(char *ptrriver,PGAME_PARAM GameParam);
void DealPotwin(char *ptrpot,PGAME_PARAM GameParam);

void Strategy_Action(PGAME_PARAM pGameParam,Uint32 maxchip,Uint8 rivalnum);
void GameSeat(PGAME_PARAM GameParam);
void GameBlind(PGAME_PARAM GameParam);
void GameHold(PGAME_PARAM GameParam);
void GameFlop(PGAME_PARAM GameParam);
void GameTurn(PGAME_PARAM GameParam);
void GameRiver(PGAME_PARAM GameParam);
void SendActionMsg(char *sendbuf,int number);
void GameInquire(PGAME_PARAM GameParam);
void GameComplete(PGAME_PARAM GameParam);
void GameShowdown(PGAME_PARAM GameParam);
void GamePotwin(PGAME_PARAM GameParam);

#endif
