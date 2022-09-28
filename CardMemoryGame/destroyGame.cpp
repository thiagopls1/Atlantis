#include "destroyGame.h"
#include <allegro5/allegro5.h>
#include <queue>

void destroyGame(ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer) {
	al_destroy_display(display);
	al_destroy_timer(timer);
}