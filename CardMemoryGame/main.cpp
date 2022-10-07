#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <queue>
#include "destroyGame.h"
#include "registerEventsSource.h"

int main() {
    int mouseX = 0, mouseY = 0;
    int r = 255, g = 255, b = 255;
//-------------------------------DISPLAY---------------------------------//
    al_init(); //Inicia o Allegro
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimens�es do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    ALLEGRO_BITMAP* bitmap;
    al_set_window_title(display, "Memory Game"); //Da o nome do "Display"
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos

 //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer);

 //-------------------------------INICIALIZA��O DE ADDONS---------------------------------//
    al_hide_mouse_cursor(display);
    al_init_image_addon();
    al_init_primitives_addon();

    bitmap = al_load_bitmap("tile.png");
    assert(display != NULL);

    int dialogStep = 0;
    bool running = true;
    al_start_timer(timer);

    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 150, 220));
            al_draw_bitmap(bitmap, 0, 0, 0);
            al_draw_rectangle(320, 700, 1250, 500, al_map_rgb(r, g, b), 3);
            al_draw_circle(mouseX, mouseY, 5, al_map_rgb(255, 255, 255), 2);
            al_flip_display();
        }
       
        // Localiza��o do mouse
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        // Exemplo de a��o ao clicar
        // DOWN: Clicou no bot�o
        // UP: Soltou o bot�o
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button & 1 && mouseX >= 320 && mouseX <= 1250 && mouseY <= 700 && mouseY >= 500) {
                switch (dialogStep) {
                case 0:
                    r = 0;
                    g = 0;
                    b = 0;
                    dialogStep++;
                break;
                case 1:
                    r = 100;
                    g = 255;
                    b = 100;
                    dialogStep++;
                break;
                case 2:
                    r = 255;
                    g = 125;
                    b = 255;
                    dialogStep = 0;
                break;
                }
                
            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }
    }

    destroyGame(display, timer, bitmap);
    return 0;
}