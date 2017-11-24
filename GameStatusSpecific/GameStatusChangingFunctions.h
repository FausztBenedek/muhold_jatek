#ifndef GAME_STATUS_CHANGER_H
#define GAME_STATUS_CHANGER_H

#include "../Sprite/Satellite.h"
#include "MENU/Menu.h"
#include "GAMEOVER/gameover.h"
#include "GameStatus.h"
#include "../Storage/Data.h"
#include "WINNING/winning.h"

///@defgroup gameStatus A játékállapotot megváltoztató függvények
///@{

/**Inputra elindítja a műholdat. Input lehet SPACE billentyű vagy jobb gomb az egérrel.
*/
void game_status_from_SETTING_to_RUNNING(enum gameStatus *gameStatus, SDL_Event ev, Satellite *s);

/**Inputra visszaugrik tervező állapotba a GameOver képernyő megjelenése nélkül.
*@param *data A sikertertelen próbálkozások száma nő.
*/
void game_status_from_RUNNING_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite *s, Data *data);

/**Megnyitja a menüben kiválasztott szintet. Fájlkezelő függvényt hív meg.
*@param *data Beállítja az aktuális szintet
*/
void game_status_from_MENU_to_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite *s, Menu *Menu, Data *data);

/**A GameOver-ből lép át menübe vagy vissza tervező módba egy újrapróbálkozás keretein belül.
* A GameOver gombjainak funkcionalitását definiálja.
*@param s Viszzállítja az akadályokra mutató pointereket NULL-ba, gyakorlatilag újrainicializálja a műholdat, ha a toMenu gombra klikkelünk.
*@param gameOverScreen A GameOverScreen struktúra gombjainak funkcionalitását kezeli.
*@ingroup gameOverScreen
*/
void game_status_from_GAMEOVER_to_MENU_or_SETTING(enum gameStatus *gameStatus, SDL_Event ev, Satellite *s, GameOverScreen gameOverScreen);

/**Ellenőrzi, hogy a műhold áthaladt-e a kapun/célvonalon.
*@param *data Beállítja, hogy a pálya sikeresen el lett végezve. Ezt az információt a *data tárolja.
*/
void game_status_from_RUNNING_to_WINNING(enum gameStatus *gameStatus, Satellite *s, Data *data);

/**A műhold ütközéseket vizsgálja:
*   1. Bolygóhoz ütközik
*   2. Falhoz ütközik
*@param *data A sikertertelen próbálkozások száma nő.
*/
void game_status_from_RUNNING_to_GAMEOVER(enum gameStatus *gameStatus, Satellite *const s, Data *data);

/**A WINNING állapotból lép továb a képernyőn lévő két gomb lenyomásától függően.
*@param winningScreen Ez a függvény kezeli a winningScreen struktúra két gombját.
*@param s Viszzállítja az akadályokra mutató pointereket NULL-ba, gyakorlatilag újrainicializálja a műholdat, ha a toMenu gombra klikkelünk.
*@param *data Az aktív szintet meg kell változtatni, amit a data tárol.
*@ingroup winningScreen
*/
void game_status_from_WINNING_to_MENU_or_NEXTLEVEL(enum gameStatus *gameStatus, SDL_Event ev, Satellite *s,
                                                   WinningScreen winningScreen, Data *data, Menu *Menu);

/**Az állandóan látható menü gomb frissítéséért és a menübe lépésért felelős. (bal felső sarok)
*@param s Viszzállítja az akadályokra mutató pointereket NULL-ba, gyakorlatilag újrainicializálja a műholdat, ha a toMenu gombra klikkelünk.
*@param *b A menübe lépés gombja
*/
void game_status_button_toMenuButton_upd(Button *b, SDL_Event ev, Satellite *s, enum gameStatus *gameStatus);

///@}

#endif // GAME_STATUS_CHANGER_H
