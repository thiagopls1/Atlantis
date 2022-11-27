#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro5.h>
#include "drawCards.h"
#include "cardPos.h"
#include "deck.h"

void drawCards(struct cardPos card[8], struct deck cardData[16]) {
    ALLEGRO_BITMAP* cardBack;
    cardBack = al_load_bitmap("./assets/card/card_back.png");

    for (int i = 0; i < 8; i++) {
        if (card[i].flipped) {
            if (card[i].language == 0) {
                al_draw_bitmap(cardData[card[i].id].image, card[i].x1, card[i].y1, 0);
            }
            if (card[i].language == 1) {
                al_draw_bitmap(cardData[card[i].id + 8].image, card[i].x1, card[i].y1, 0);
            }
        }
        else {
            al_draw_bitmap(cardBack, card[i].x1, card[i].y1, 0);
        }
        
    }
}