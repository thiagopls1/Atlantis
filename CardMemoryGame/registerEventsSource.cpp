#include <allegro5/allegro5.h>
#include <queue>
#include "registerEventsSource.h"

void registerEventsSource(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer, ALLEGRO_TIMER* scoreTimer, ALLEGRO_TIMER* cardTimer) {
    al_install_mouse();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(cardTimer));
    al_register_event_source(queue, al_get_timer_event_source(scoreTimer));
}