#include <allegro5/allegro_primitives.h>
#include <allegro5\allegro5.h>
#include "drawCards.h"
#include "cardInfo.h"

void drawCards(struct cardInfo card[8]) {
    //al_draw_filled_rectangle(400, 50, 550, 250, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(600, 50, 750, 250, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(800, 50, 950, 250, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(1000, 50, 1150, 250, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(400, 300, 550, 500, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(600, 300, 750, 500, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(800, 300, 950, 500, al_map_rgb(200, 200, 200));
    //al_draw_filled_rectangle(1000, 300, 1150, 500, al_map_rgb(200, 200, 200));

    for (int i = 0; i < 8; i++) {
        al_draw_filled_rectangle(card[i].x1, card[i].y1, card[i].x2, card[i].y2, card[i].color);
    }
}