#include "mapCards.h"
#include "cardInfo.h"

void mapCards(cardInfo card[8]){
    int x, y;
    x = 400;
    y = 50;
    for (int i = 0; i < 4; i++) {
        card[i] = { NULL, i, false, al_map_rgb(200, 200, 200), x, y, x + 150, y + 200 };
        x += 200;
    }
    x = 400;
    y = 300;
    for (int i = 4; i < 8; i++) {
        card[i] = { NULL, i, false, al_map_rgb(200, 200, 200), x, y, x + 150, y + 200 };
        x += 200;
    }
}