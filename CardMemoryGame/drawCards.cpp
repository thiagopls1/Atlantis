#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro5.h>
#include "drawCards.h"
#include "cardInfo.h"

void drawCards(struct cardInfo card[8]) {
    for (int i = 0; i < 8; i++) {
        al_draw_filled_rectangle(card[i].x1, card[i].y1, card[i].x2, card[i].y2, card[i].color);
    }
}