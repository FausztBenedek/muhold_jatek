#ifndef GAME_STATUS_H
#define GAME_STATUS_H

///@defgroup gameStatusValues Játék állopotai

/**A játék lehetséges állapotait tartalmazó enum.
*A fő programban egyetlen egy gameStatus változó van, aminek az értékét ellenőrzni kell,
*és ez dönti el, hogy melyik állapotban van a játék.
*/
enum gameStatus {
    QUITTING,///<Kilépés
    RUNNING,///<Megy a műhold
    SETTING,///<Bolygók beállítása
    MENU,///<Menü
    WINNING,///<"Sikerült" képernyő
    GAMEOVER///<"Vesztettél" képernyő
};

#endif // GAME_STATUS_H
