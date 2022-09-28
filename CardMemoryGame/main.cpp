#include <allegro5\allegro5.h>
#include <queue>
#include "destroyGame.h"

int main() {
//-------------------------------DISPLAY---------------------------------//
    al_init(); //Inicia o Allegro
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    al_set_window_title(display, "Memory Game"); //Da o nome do "Display"
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos

 //-------------------------------FILA DE EVENTOS---------------------------------//
    al_install_mouse();

    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display)); 
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool running = true;
    al_start_timer(timer);
    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(255, 150, 220));
            al_flip_display();
        }
       
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Quando aperta "x" a janela fecha
        {
            running = false;
        }
    }

    destroyGame(display, timer);
    return 0;
}