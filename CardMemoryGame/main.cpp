#include <allegro5\allegro5.h>
#include <queue>

int main() {
//-------------------------------DISPLAY---------------------------------//
    al_init(); //Inicia o Allegro
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    al_set_window_title(display, "Memory Game"); //Da o nome do "Display"
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos

 //-------------------------------FILA DE EVENTOS---------------------------------//

    al_register_event_source(queue, al_get_display_event_source(display));

    bool running = true;
    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event); //

        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(255, 150, 220));
            al_flip_display();
        }
       
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Quando aperta "x" a janela fecha
        {
            running = false;
        }
    }

    al_destroy_display(display);
    return 0;
}