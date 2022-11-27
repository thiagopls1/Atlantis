#ifndef DESTROY_GAME
#define DESTROY_GAME
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

void destroyGame(ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* scoreTimer, ALLEGRO_TIMER* cardTimer, ALLEGRO_BITMAP* bitmap, ALLEGRO_FONT* font);
#endif