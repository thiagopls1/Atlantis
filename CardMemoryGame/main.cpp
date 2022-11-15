
// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

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

    int catX = 40, catY = 440;

    int timeLeft = 15;


    int firstCard = NULL;
    bool hasFlippedCard = false;
    int movement = 0, score = 0;

    int cardsFlipped = 0;

    char dialogText[1000] = {"Olá Seja bem vindo(a) ao nosso jogo da memória!!!."}; // MENSAGEM DE BOAS VINDAS (Precisa arrumar a digitação e colocar a quebra de linha)
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

    //-------------------------------DISPLAY E ADDONs---------------------------------//

    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio(); //Addon de audio
    al_init_acodec_addon(); //Addon que da suporte as extensoes de áudio

    //-------------------------------VARIÁVEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0/60);
    ALLEGRO_TIMER* cardTimer = al_create_timer(2.5);
    ALLEGRO_TIMER* scoreTimer = al_create_timer(1);
    ALLEGRO_BITMAP* bitmap;
    ALLEGRO_BITMAP* cat; //VARIÁVEL DOS GATOS
    ALLEGRO_FONT* font = al_load_ttf_font("./assets/font/alterebro-pixel.ttf", 40, 0);
    ALLEGRO_FONT* biggerFont = al_load_ttf_font("./assets/font/alterebro-pixel.ttf", 80, 0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos
    //ALLEGRO_AUDIO_STREAM* musicaFundo = NULL; //Variável da música de fundo
    ALLEGRO_SAMPLE_INSTANCE* songInstance = NULL;
    ALLEGRO_SAMPLE* song = NULL;

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

 //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer);
    al_register_event_source(queue, al_get_timer_event_source(cardTimer));
    al_register_event_source(queue, al_get_timer_event_source(scoreTimer));
    al_hide_mouse_cursor(display);
    al_set_window_title(display, "Memory Game");
    bitmap = al_load_bitmap("./assets/bg/tile.png");
    cat = al_load_bitmap("./assets/cat/cat1r.png");

    //-------------------------------ÁUDIOS-----------------------------------------//

    al_reserve_samples(1);
    song = al_load_sample("./asstes/sfx/songTest.wav");
    songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    

    //-----------------------------------------------------------------------------//

    assert(display != NULL);
    al_start_timer(scoreTimer);
    al_start_timer(cardTimer);
    al_start_timer(timer);

    while(gameState != 5){

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
       
        

        if (event.type == ALLEGRO_EVENT_TIMER) {
            
            if (event.timer.source == scoreTimer) {
                if (al_get_timer_count(scoreTimer) >= 15) {
                    al_set_timer_count(scoreTimer, 0);
                    strcpy_s(dialogText, "Tempo esgotado! você perdeu 2 pontos!");
                    score -= 2;
                }
            }

            if (event.timer.source == timer) {
                // Sempre vai ser renderizado (Não colocar condição de gameState)
                al_draw_bitmap(bitmap, 0, 0, 0); //DESENHA O TILE (BACKGROUND)
                //-------------------------------------------------------------//

                if (gameState == 0) {
                    // Menu
                }

                if (gameState == 1) {
                    // Level Select
                }

                if (gameState == 2) {
                    // Tutorial
                }


                if (gameState == 3 || gameState == 4) {
                    al_draw_bitmap(cat, catX, catY, 0);
                    drawCards(card, cardData);
                    al_draw_rectangle(320, 700, 1250, 600, al_map_rgb(255, 255, 255), 3); // Caixa de diálogo
                    al_draw_text(font, al_map_rgb(255, 255, 255), 330, 600, 0, dialogText);
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 10, 0, "Tempo restante: %d", timeLeft - al_get_timer_count(scoreTimer));
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 10, 0, "Movimentos: %d", movement);
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 10, 0, "Pontos: %d", score);
                    if(cardsFlipped == 8){
                        al_stop_timer(scoreTimer);
                        al_set_timer_count(scoreTimer, 0);
                        gameState = 4;
                        al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0, 0, 0, 155));
                        al_draw_text(biggerFont, al_map_rgb(255, 255, 255), displayX / 2, displayY / 2 - 50, ALLEGRO_ALIGN_CENTRE, winText);
                        al_draw_text(
                            font,
                            al_map_rgb(255, 255, 255),
                            displayX / 2 - 270,
                            displayY / 2 + 30,
                            0,
                            "Jogar Novamente");
                        //Retângulo do "Jogar Novamente"
                        al_draw_rectangle(
                            displayX / 2 - 285,
                            displayY / 2 + 20,
                            displayX / 2 - 65,
                            displayY / 2 + 85,
                            al_map_rgb(255, 255, 255),
                            3
                        );
                        al_draw_text(
                            font,
                            al_map_rgb(255, 255, 255),
                            displayX / 2 + 200,
                            displayY / 2 + 30,
                            0,
                            "Sair"
                        );
                        //Retângulo do "Sair"
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
            
        }

        //-------------------------------LOCALIZAÇÃO DO MOUSE---------------------------------//

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            //-------------------------------DIÁLOGO DE TEXTO---------------------------------//
            if (mouseX >= 320 && mouseX <= 1250 && mouseY <= 700 && mouseY >= 600) {
                switch (dialogStep) {
                case 0: 
                    strcpy_s(dialogText, "Neste jogo da memória voce aprenderá Inglês por assimilação (GATO 1)");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat1r.png");
                break;
                case 1:
                    strcpy_s(dialogText, "GATO 2");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat2r.png");
                    catX = 15, catY = 458;
                break;
                case 2:
                    strcpy_s(dialogText, "GATO 3");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat3r.png");
                    catX = 40, catY = 418;
                break;
                case 3:
                    strcpy_s(dialogText, "GATO 3 DNV");
                    catX = 50, catY = 430;
                    dialogStep = 0;
                break;
                }
            }

            //-------------------------------CARTA CLICADA---------------------------------//
            for (int i = 0; i < 8; i++) {
                cardsFlipped = 0;
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
                            al_stop_timer(scoreTimer);
                            score = (timeLeft - al_get_timer_count(scoreTimer)) + score;
                            score++;
                            card[i].flipped = true;
                            card[i].locked = true;
                        }
                        else {
                            score -= 5;
                            al_stop_timer(scoreTimer);
                            card[i].flipped = true;
                            al_set_timer_count(cardTimer, 0);
                            while(al_get_timer_count(cardTimer) < 1) {
                                drawCards(card, cardData);
                                al_flip_display();
                            }
                            card[i].flipped = false;
                            card[firstCard].flipped = false;
                            card[firstCard].locked = false;
                        }
                        al_set_timer_count(scoreTimer, 0);
                        al_start_timer(scoreTimer);
                        hasFlippedCard = false;
                        movement++;
                        firstCard = NULL;
                    }                    
                }
            }
            for (int i = 0; i < 8; i++) {
                if (card[i].flipped) {
                    cardsFlipped++;
                }
            }
            if (
                mouseX >= displayX / 2 - 250 && mouseY >= displayY / 2 + 20 && 
                mouseX <= displayX / 2 - 35 &&  mouseY <= displayY / 2 + 85 && 
                gameState == 4) { // TENTAR NOVAMENTE
                al_start_timer(scoreTimer);
                cardsFlipped = 0;
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
    al_destroy_timer(scoreTimer);
    al_destroy_timer(cardTimer);
    al_destroy_sample_instance(songInstance);
    al_destroy_sample(song);
    return 0;
}