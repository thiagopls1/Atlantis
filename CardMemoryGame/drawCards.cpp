#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro5.h>
#include "drawCards.h"
#include "cardPos.h"
#include "deck.h"

void drawCards(struct cardPos card[8], struct deck cardData[4]) {
    for (int i = 0; i < 8; i++) {
        if (card[i].flipped) {
            al_draw_filled_rectangle(card[i].x1, card[i].y1, card[i].x2, card[i].y2, cardData[card[i].id].color);
        }
        else {
            al_draw_filled_rectangle(card[i].x1, card[i].y1, card[i].x2, card[i].y2, al_map_rgb(175, 175, 175));
        }
        
    }
}