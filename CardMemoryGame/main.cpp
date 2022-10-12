#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>
#include <string.h>
#include "destroyGame.h"
#include "registerEventsSource.h"
#include "drawCards.h"
#include "cardInfo.h"
#include "mapCards.h"



int main() {
//-------------------------------VARIÁVEIS LOCAIS---------------------------------//
    int mouseX = 0, mouseY = 0;
    int dialogStep = 0;
    char dialogText[1000] = { "Hello World" };
    bool running = true;
    //-------------------------------PREENCHENDO O STRUCT---------------------------------//
    cardInfo card[8]{};
    mapCards(card);
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
    al_hide_mouse_cursor(display);
    bitmap = al_load_bitmap("tile.png");
    assert(display != NULL);
    al_start_timer(timer);

    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 150, 220));
            al_draw_bitmap(bitmap, 0, 0, 0);
            drawCards(card);
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
            // Diálogo de texto
            if (event.mouse.button = 1 && mouseX >= 320 && mouseX <= 1250 && mouseY <= 700 && mouseY >= 600) {
                switch (dialogStep) {
                case 0:
                    strcpy_s(dialogText, "Teste de Texto 1");
                    dialogStep++;
                break;
                case 1:
                    strcpy_s(dialogText, "Teste de Texto 2");
                    dialogStep++;
                break;
                case 2:
                    strcpy_s(dialogText, "Teste de Texto 3");
                    dialogStep++;
                break;
                case 3:
                    strcpy_s(dialogText, "Teste de Texto 4");
                    dialogStep = 0;
                break;
                }
                
            }
            // Carta clicada
            if (event.mouse.button = 1 && mouseX >= card[0].x1 && mouseX <= card[0].x2 && mouseY >= card[0].y1 && mouseY <= card[0].y2) {
                card[0].color = al_map_rgb(255, 0, 0);
                card[0].cardFlipped = true;
            }
            if (event.mouse.button = 1 && mouseX >= card[1].x1 && mouseX <= card[1].x2 && mouseY >= card[1].y1 && mouseY <= card[1].y2) {
                card[1].color = al_map_rgb(0, 255, 0);
                card[1].cardFlipped = true;
            }
            if (event.mouse.button = 2 && mouseX >= card[2].x1 && mouseX <= card[2].x2 && mouseY >= card[2].y1 && mouseY <= card[2].y2) {
                card[2].color = al_map_rgb(0, 0, 0);
                card[2].cardFlipped = true;
            }
            if (event.mouse.button = 3 && mouseX >= card[3].x1 && mouseX <= card[3].x2 && mouseY >= card[3].y1 && mouseY <= card[3].y2) {
                card[3].color = al_map_rgb(255, 255, 0);
                card[3].cardFlipped = true;
            }
            if (event.mouse.button = 4 && mouseX >= card[4].x1 && mouseX <= card[4].x2 && mouseY >= card[4].y1 && mouseY <= card[4].y2) {
                card[4].color = al_map_rgb(255, 255, 0);
                card[4].cardFlipped = true;
            }
            if (event.mouse.button = 5 && mouseX >= card[5].x1 && mouseX <= card[5].x2 && mouseY >= card[5].y1 && mouseY <= card[5].y2) {
                card[5].color = al_map_rgb(255, 0, 0);
                card[5].cardFlipped = true;
            }
            if (event.mouse.button = 6 && mouseX >= card[6].x1 && mouseX <= card[6].x2 && mouseY >= card[6].y1 && mouseY <= card[6].y2) {
                card[6].color = al_map_rgb(0, 255, 0);
                card[6].cardFlipped = true;
            }
            if (event.mouse.button = 7 && mouseX >= card[7].x1 && mouseX <= card[7].x2 && mouseY >= card[7].y1 && mouseY <= card[7].y2) {
                card[7].color = al_map_rgb(0, 0, 0);
                card[7].cardFlipped = true;
            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            running = false;
        }
    }

    destroyGame(display, timer, bitmap, font);
    return 0;
}