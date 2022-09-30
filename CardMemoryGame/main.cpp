#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <queue>
#include "destroyGame.h"
#include "registerEventsSource.h"

int main() {
    int x = 0, y = 0;
    int r = 255, g = 255, b = 255;
//-------------------------------DISPLAY---------------------------------//
    al_init(); //Inicia o Allegro
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    ALLEGRO_BITMAP* bitmap;
    al_set_window_title(display, "Memory Game"); //Da o nome do "Display"
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos

 //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer);

 //-------------------------------INICIALIZAÇÃO DE ADDONS---------------------------------//
    al_hide_mouse_cursor(display);
    al_init_image_addon();
    al_init_primitives_addon();

    bitmap = al_load_bitmap("tile.png");
    assert(display != NULL);

    int displayX = al_get_display_width(display) / 2;
    int displayY = al_get_display_height(display) / 2;
    bool running = true;
    al_start_timer(timer);
    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 150, 220));
            al_draw_bitmap(bitmap, 0, 0, 0);
            al_draw_rectangle(displayX - 100, displayY - 100, displayX + 100, displayY + 100, al_map_rgb(r, g, b), 3);
            al_draw_circle(x, y, 5, al_map_rgb(255, 255, 255), 2);
            al_flip_display();
        }
       
        // Localização do mouse
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            x = event.mouse.x;
            y = event.mouse.y;
        }

        // Exemplo de ação ao clicar
        // DOWN: Clicou no botão
        // UP: Soltou o botão
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button & 1 && x >= displayX - 100 && x <= displayX + 100 && y >= displayY - 100 && y <= displayY + 100) {
                r = 0;
                g = 0;
                b = 0;
            }
            if (event.mouse.button & 2 && x >= displayX - 100 && x <= displayX + 100 && y >= displayY - 100 && y <= displayY + 100) {
                r = 255;
                g = 255;
                b = 255;
            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }
    }

    destroyGame(display, timer, bitmap);
    return 0;
}