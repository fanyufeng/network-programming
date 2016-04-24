#ifndef _GAME_BASIC_H_
#define _GAME_BASIC_H_

//#include "game_basic.h"


void NewAddToCard(Uint8 uCardIn,PGAME_PARAM pGameParam);
void CardStatByValue(PGAME_PARAM pGameParam);
void CardStatByFlush(PGAME_PARAM pGameParam);
void CardStatByStraight(PGAME_PARAM pGameParam);
void strategy_flop(PGAME_PARAM pGameParam);
void strategy_turn(PGAME_PARAM pGameParam);
void strategy_river(PGAME_PARAM pGameParam);
int  random_rate(Uint16 max, Uint16 refer);
int randoma(Uint16 max);

Uint8 pipei_fiveinfive(PGAME_PARAM pGameParam);
Uint8 pipei_fiveinsix(PGAME_PARAM pGameParam);
void pipei_fourinfive(PGAME_PARAM pGameParam);
void pipei_fourinsix(PGAME_PARAM pGameParam);
Uint8 pipei_fiveinseven(PGAME_PARAM pGameParam);



#endif
