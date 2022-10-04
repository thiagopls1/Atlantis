#include <allegro5/allegro5.h>
#include <queue>
#include "displayConfig.h"

void displayConfig(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* display, ALLEGRO_TIMER* timer) {
    al_init(); //Inicia o Allegro
    display = al_create_display(1280, 720); //Dimensões do Display
    timer = al_create_timer(1.0 / 60);
    al_set_window_title(display, "Memory Game"); //Da o nome do "Display"
    queue = al_create_event_queue(); //Cria uma fila de eventos
}