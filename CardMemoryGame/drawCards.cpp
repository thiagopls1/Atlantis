#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro5.h>
#include "drawCards.h"
#include "cardPos.h"
#include "deck.h"

void drawCards(struct cardPos card[8], struct deck cardData[4]) {
    ALLEGRO_BITMAP* cardBack;
    cardBack = al_load_bitmap("./assets/card/card_back.png");

    for (int i = 0; i < 8; i++) {
        if (card[i].flipped) {
            al_draw_filled_rectangle(card[i].x1, card[i].y1, card[i].x2, card[i].y2, cardData[card[i].id].color);
        }
        else {
            al_draw_bitmap(cardBack, card[i].x1, card[i].y1, 0);
        }
        
    }
}