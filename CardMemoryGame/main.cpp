#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>
#include <string.h>
#include "destroyGame.h"
#include "registerEventsSource.h"

int main() {
//-------------------------------DISPLAY---------------------------------//
    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_FONT* font = al_load_ttf_font("alterebro-pixel.ttf", 40, 0);
    al_set_window_title(display, "Memory Game"); //Da o nome do "Display"
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos

 //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer);

 //-------------------------------INICIALIZAÇÃO DE ADDONS---------------------------------//
    al_hide_mouse_cursor(display);
    bitmap = al_load_bitmap("tile.png");
    assert(display != NULL);

    //-------------------------------VARIÁVEIS LOCAIS---------------------------------//
    int mouseX = 0, mouseY = 0;
    int dialogStep = 0;
    char dialogText[1000] = {"Olha aqui o texto que legal mto brabo ele hein"};
    //-------------------------------------------------------------------------//
    bool running = true;
    al_start_timer(timer);

    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 150, 220));
            al_draw_bitmap(bitmap, 0, 0, 0);
            al_draw_filled_rectangle(400, 50, 550, 250, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(600, 50, 750, 250, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(800, 50, 950, 250, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(1000, 50, 1150, 250, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(400, 300, 550, 500, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(600, 300, 750, 500, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(800, 300, 950, 500, al_map_rgb(200, 200, 200));
            al_draw_filled_rectangle(1000, 300, 1150, 500, al_map_rgb(200, 200, 200));
            al_draw_rectangle(320, 700, 1250, 600, al_map_rgb(255, 255, 255), 3);
            al_draw_text(font, al_map_rgb(255, 255, 255), 330, 600, 0, dialogText);
            al_draw_circle(mouseX, mouseY, 5, al_map_rgb(255, 255, 255), 2);
            al_flip_display();
        }
       
        // Localização do mouse
        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        // Exemplo de ação ao clicar
        // DOWN: Clicou no botão
        // UP: Soltou o botão
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if (event.mouse.button & 1 && mouseX >= 320 && mouseX <= 1250 && mouseY <= 700 && mouseY >= 600) {
                switch (dialogStep) {
                case 0:
                    strcpy_s(dialogText, "Mais texto aqui que legal :D");
                    dialogStep++;
                break;
                case 1:
                    strcpy_s(dialogText, "Mais texto ainda aqui que legal!");
                    dialogStep++;
                break;
                case 2:
                    strcpy_s(dialogText, "Aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa '-'");
                    dialogStep++;
                break;
                case 3:
                    strcpy_s(dialogText, "Hello World.");
                    dialogStep = 0;
                break;
                }
                
            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }
    }

    destroyGame(display, timer, bitmap, font);
    return 0;
}