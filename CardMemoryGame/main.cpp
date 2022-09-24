#include <allegro5\allegro5.h>
#include <queue>

int main() {

    al_init();
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
    al_set_window_title(display, "Memory Game");
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos


    bool running = true;
    while (running) {
        al_clear_to_color(al_map_rgb(255, 150, 220));
        al_flip_display();

        //Gera os Eventos
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            running = false;
        }
    }

    al_destroy_display(display);
    return 0;
}