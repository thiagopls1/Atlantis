#include "destroyGame.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

void destroyGame(ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* scoreTimer, ALLEGRO_TIMER* cardTimer, ALLEGRO_BITMAP* bitmap, ALLEGRO_FONT* font) {
	al_destroy_display(display);
	al_uninstall_mouse();
	al_destroy_timer(timer);
	al_destroy_timer(scoreTimer);
	al_destroy_timer(cardTimer);
	al_destroy_bitmap(bitmap);
	al_destroy_font(font);
}