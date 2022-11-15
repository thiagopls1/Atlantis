#include "mapCards.h"
#include "cardPos.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"

void mapCards(cardPos card[8]){
    int x, y, temp;
    x = 415;
    y = 70;
    int number[4] = {0, 0, 0, 0};
    
    for (int i = 0; i < 4; i++) {
        temp = rand() % 4;
        while (number[temp] >= 2) {
            temp = rand() % 4;
        }
        number[temp]++;

        card[i] = { temp, false, false, x, y, x + 150, y + 200};
        x += 175;
    }
    x = 415;
    y = 295;
    for (int i = 4; i < 8; i++) {
        temp = rand() % 4;
        while (number[temp] >= 2) {
            temp = rand() % 4;
        }
        number[temp]++;

        card[i] = { temp, false, false, x, y, x + 150, y + 200 };
        x += 175;
    }
}