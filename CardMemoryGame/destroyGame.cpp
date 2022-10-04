#include "destroyGame.h"
#include <allegro5/allegro5.h>
#include <queue>

void destroyGame(ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_BITMAP* bitmap) {
	al_destroy_display(display);
	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_bitmap(bitmap);
}