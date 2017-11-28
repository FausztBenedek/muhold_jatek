#ifndef FUNC_UPD_AND_DRW_H
#define FUNC_UPD_AND_DRW_H

#include "GameStatusSpecific/GameStatus.h"
#include "GameStatusSpecific/GameStatusChangingFunctions.h"
#include "GameStatusSpecific/SETTING/HelpingPlots.h"
#include "GameStatusSpecific/MENU/Menu.h"
#include "GameStatusSpecific/GAMEOVER/gameover.h"
#include "GameStatusSpecific/WINNING/winning.h"
#include "GameStatusSpecific/Button.h"
#include "Storage/Data.h"

void updMENU(Satellite *sat, Menu *menu, Data *data, Button *toMenu, enum gameStatus *gameStatus, SDL_Event ev);

#endif //FUNC_UPD_AND_DRW_H
