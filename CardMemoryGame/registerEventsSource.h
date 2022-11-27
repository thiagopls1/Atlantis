#ifndef REGISTER_EVENTS_SOURCE
#define REGISTER_EVENTS_SOURCE
#include <allegro5/allegro5.h>
#include <queue>

void registerEventsSource(ALLEGRO_EVENT_QUEUE *queue, ALLEGRO_DISPLAY * display, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* scoreTimer, ALLEGRO_TIMER* cardTimer);
#endif