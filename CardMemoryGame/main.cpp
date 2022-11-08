// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>

// Funções
#include "destroyGame.h"
#include "registerEventsSource.h"
#include "drawCards.h"
#include "mapCards.h"
#include "checkFlippedCards.h"

// Structs
#include "cardPos.h"
#include "deck.h"

// Bibliotecas padrões do C
#include "stdlib.h"
#include "time.h"
#include <string.h>
#include <stdio.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    //-------------------------------VARIÁVEIS LOCAIS---------------------------------//

    int mouseX = 0, mouseY = 0;
    int dialogStep = 0;

    int catX = 40, catY = 418;


    int firstCard = NULL;
    bool hasFlippedCard = false;
    int movement = 0, score = 0;

    char dialogText[1000] = {"Olá Seja bem vindo(a) ao nosso jogo da memória!!!."};
    char winText[1000] = { "Parabéns, você ganhou!" };
    char scoreText[3];
    char movementsText[15] = { "Movimentos: " };
    int gameState = 3;
    /* 
    Sobre o gameState:
    0 = Menu,
    1 = Level Select,
    2 = "Tutorial/Presentation",
    3 = Playing,
    4 = Finished Level,
    5 = Exit
    */

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

    //-------------------------------VARIÁVEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_BITMAP* cat; //VARIÁVEL DOS GATOS
    ALLEGRO_FONT* font = al_load_ttf_font("./assets/font/alterebro-pixel.ttf", 40, 0);
    ALLEGRO_FONT* biggerFont = al_load_ttf_font("./assets/font/alterebro-pixel.ttf", 80, 0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos
    ALLEGRO_EVENT_QUEUE* awaitCardTimer = al_create_event_queue();

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

 //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer);

    al_hide_mouse_cursor(display);
    al_set_window_title(display, "Memory Game");
    bitmap = al_load_bitmap("./assets/bg/tile.png");
    cat = al_load_bitmap("./assets/cat/cat1r.png");

    assert(display != NULL);
    al_start_timer(timer);

    while(gameState != 5){

        ALLEGRO_EVENT event; //Gera os Eventos
        al_wait_for_event(queue, &event);
       
        if (event.timer.source == timer){

            // Sempre vai ser renderizado (Não colocar condição de gameState)
            al_clear_to_color(al_map_rgb(0, 150, 220));
            al_draw_bitmap(bitmap, 0, 0, 0);
            //----

            if (gameState == 0) {
                // TODO: Menu
            }

            if (gameState == 3 || gameState == 4) {
                al_draw_bitmap(cat, catX, catY, 0);
                drawCards(card, cardData);
                al_draw_rectangle(320, 700, 1250, 600, al_map_rgb(255, 255, 255), 3); // Caixa de diálogo
                al_draw_text(font, al_map_rgb(255, 255, 255), 330, 600, 0, dialogText);
                al_draw_text(font, al_map_rgb(255, 255, 255), 800, 10, 0, "Movimentos: ");
                al_draw_textf(font, al_map_rgb(255, 255, 255), 940, 10, 0, "%d", movement);
                al_draw_text(font, al_map_rgb(255, 255, 255), 1000, 10, 0, "Pontos: ");
                al_draw_textf(font, al_map_rgb(255, 255, 255), 1090, 10, 0, "%d", score);
                if (score >= 4) {
                    gameState = 4;
                    al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0, 0, 0, 155));
                    al_draw_text(biggerFont, al_map_rgb(255, 255, 255), displayX / 2 - 220, displayY / 2 - 50, 0, winText);
                    al_draw_text(
                        font,
                        al_map_rgb(255, 255, 255),
                        displayX / 2 - 235,
                        displayY / 2 + 30,
                        0,
                        "Jogar Novamente");
                    al_draw_rectangle(
                        displayX / 2 - 250,
                        displayY / 2 + 20,
                        displayX / 2 - 35,
                        displayY / 2 + 85,
                        al_map_rgb(255, 255, 255),
                        3
                    ); //Retângulo do "Jogar Novamente"
                    al_draw_text(
                        font,
                        al_map_rgb(255, 255, 255),
                        displayX / 2 + 200,
                        displayY / 2 + 30,
                        0,
                        "Sair"
                    );//Retângulo do "Sair"
                    al_draw_rectangle(
                        displayX / 2 + 150, displayY / 2 + 20,
                        displayX / 2 + 285, displayY / 2 + 85,
                        al_map_rgb(255, 255, 255),
                        3
                    );
                    for (int i = 0; i < 8; i++) {
                        card[i].locked = true;
                    }
                }
            }

            // Sempre vai ser renderizado (Não colocar condição de gameState)
            al_draw_circle(mouseX, mouseY, 5, al_map_rgb(255, 255, 255), 2);
            al_flip_display();
            //----
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            //-------------------------------DIÁLOGO DE TEXTO---------------------------------//
            if (mouseX >= 320 && mouseX <= 1250 && mouseY <= 700 && mouseY >= 600) {
                switch (dialogStep) {
                case 0: 
                    strcpy_s(dialogText, "Neste jogo da memória voce aprenderá Inglês por assimilação");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat1r.png");
                break;
                case 1:
                    strcpy_s(dialogText, "Teste de Texto 2");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat2r.png");
                    catX = 15, catY = 458;
                break;
                case 2:
                    strcpy_s(dialogText, "Teste de Texto 3");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat3r.png");
                    catX = 40, catY = 418;
                break;
                case 3:
                    strcpy_s(dialogText, "Teste de Texto 4");
                    dialogStep = 0;
                break;
                }
            }

            for (int i = 0; i < 8; i++) {
                if (score == 0 && movement == 0) {
                    card[i].locked = false;
                }
                if (mouseX >= card[i].x1 && mouseX <= card[i].x2 && mouseY >= card[i].y1 && mouseY <= card[i].y2 && !card[i].locked && gameState == 3) {
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
                        } else {
                            card[i].flipped = true;
                            while (al_get_timer_count(timer) % 60 != 59) {
                                drawCards(card, cardData);
                                al_flip_display();
                            }
                            card[i].flipped = false;
                            card[firstCard].flipped = false;
                            card[firstCard].locked = false;
                        }
                        hasFlippedCard = false;
                        movement++;
                        firstCard = NULL;
                    }                    
                }
            }
            if (
                mouseX >= displayX / 2 - 250 && mouseY >= displayY / 2 + 20 && 
                mouseX <= displayX / 2 - 35 &&  mouseY <= displayY / 2 + 85 && 
                gameState == 4) { // TENTAR NOVAMENTE
                mapCards(card);
                movement = 0;
                score = 0;
                gameState = 3;
            }
            if (mouseX >= displayX / 2 + 150 && mouseY >= displayY / 2 + 20 && 
                mouseX <= displayX / 2 + 285 && mouseY <= displayY / 2 + 85  && 
                gameState == 4) { // SAIR
                // TODO: Colocar para voltar para o menu
                gameState = 5;
            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gameState = 5; }
    }

    destroyGame(display, timer, bitmap, font);
    return 0;
}