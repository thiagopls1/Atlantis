#include "mapCards.h"
#include "cardPos.h"

void mapCards(cardPos card[8]){
    int x, y;
    x = 400;
    y = 50;
    for (int i = 0; i < 4; i++) {
        card[i] = { i, false, x, y, x + 150, y + 200 };
        x += 200;
    }
    x = 400;
    y = 300;
    for (int i = 4; i < 8; i++) {
        card[i] = { i, false, x, y, x + 150, y + 200 };
        x += 200;
    }
}