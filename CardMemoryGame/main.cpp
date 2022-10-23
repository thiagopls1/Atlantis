#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

#include "destroyGame.h"
#include "registerEventsSource.h"
#include "drawCards.h"
#include "mapCards.h"
#include "checkFlippedCards.h"

#include "cardPos.h"
#include "deck.h"

#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <stdio.h>

int main() {
    srand(time(NULL));
    //-------------------------------VARIÁVEIS LOCAIS---------------------------------//
    int mouseX = 0, mouseY = 0;
    int dialogStep = 0;

    int firstCard = NULL;
    bool hasFlippedCard = false;
    int movement = 0, score = 0;

    char dialogText[1000] = { "Hello World" };
    char scoreText[12] = { "Pontos: " };
    char movementsText[15] = { "Movimentos: " };
    bool running = true;
    //-------------------------------PREENCHENDO O STRUCT---------------------------------//
    cardPos card[8]{};
    deck cardData[4];
    cardData[0] = { 0, al_map_rgb(250, 200, 250) };
    cardData[1] = { 1, al_map_rgb(250, 250, 0) };
    cardData[2] = { 2, al_map_rgb(0, 250, 250) };
    cardData[3] = { 3, al_map_rgb(75, 75, 75) };
    mapCards(card);
    //-------------------------------DISPLAY---------------------------------//
    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();

    // Variáveis do Allegro
    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_FONT* font = al_load_ttf_font("alterebro-pixel.ttf", 40, 0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos


 //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer);
    al_hide_mouse_cursor(display);
    al_set_window_title(display, "Memory Game");
    bitmap = al_load_bitmap("tile.png");
    assert(display != NULL);
    al_start_timer(timer);

    while (running) {

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(al_map_rgb(0, 150, 220));
            al_draw_bitmap(bitmap, 0, 0, 0);
            drawCards(card, cardData);
            al_draw_rectangle(320, 700, 1250, 600, al_map_rgb(255, 255, 255), 3);
            al_draw_text(font, al_map_rgb(255, 255, 255), 330, 600, 0, dialogText);
            al_draw_text(font, al_map_rgb(255, 255, 255), 800, 10, 0, movementsText);
            al_draw_text(font, al_map_rgb(255, 255, 255), 1000, 10, 0, scoreText);
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
            for (int i = 0; i < 8; i++) {
                
                if (mouseX >= card[i].x1 && mouseX <= card[i].x2 && mouseY >= card[i].y1 && mouseY <= card[i].y2 && !card[i].locked) {
                    
                    if (!hasFlippedCard) {
                        firstCard = i;
                        card[i].flipped = true;
                        hasFlippedCard = true;
                        card[i].locked = true;
                    }
                    else {
                        if (card[firstCard].id == card[i].id) {
                            score++;
                            card[i].flipped = true;
                            card[i].locked = true;
                            
                        }
                        else {
                            card[firstCard].flipped = false;
                            card[firstCard].locked = false;
                            
                        }
                        hasFlippedCard = false;
                        movement++;
                        firstCard = NULL;
                    }                    

                }
                
            }

            printf("Score: %d\n", score);
            printf("Movement: %d\n\n", movement);
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){ running = false; }
    }

    destroyGame(display, timer, bitmap, font);
    return 0;
}