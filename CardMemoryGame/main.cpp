// Funções
#include "destroyGame.h"
#include "registerEventsSource.h"
#include "drawCards.h"
#include "mapCards.h"
#include "checkFlippedCards.h"

// Structs
#include "cardPos.h"
#include "deck.h"

// Bibliotecas do allegro
#include <allegro5\allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <queue>
#include <allegro5/allegro_audio.h> 
#include <allegro5/allegro_acodec.h>

// Bibliotecas padrões do C
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <locale.h>


int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    //-------------------------------DISPLAY E ADDONs---------------------------------//
    al_init(); //Inicia o Allegro e os seus Addons
    al_init_image_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_audio(); //Addon de audio
    al_init_acodec_addon(); //Addon que da suporte as extensoes de áudio

    //-------------------------------VARIÁVEIS DO ALLEGRO---------------------------------//

    ALLEGRO_DISPLAY* display = al_create_display(1280, 720); //Dimensões do Display
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER* cardTimer = al_create_timer(2.5);
    ALLEGRO_TIMER* scoreTimer = al_create_timer(1);
    ALLEGRO_BITMAP* bitmap; // Background
    ALLEGRO_BITMAP* cat; //VARIÁVEL DOS GATOS
    ALLEGRO_BITMAP* mainMenu; // Menu principal
    ALLEGRO_BITMAP* instructionsMenu;
    ALLEGRO_FONT* font = al_load_ttf_font("./assets/font/alterebro-pixel.ttf", 40, 0);
    ALLEGRO_FONT* biggerFont = al_load_ttf_font("./assets/font/alterebro-pixel.ttf", 80, 0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue(); //Cria uma fila de eventos
    //ALLEGRO_AUDIO_STREAM* musicaFundo = NULL; //Variável da música de fundo
    ALLEGRO_SAMPLE_INSTANCE* songInstance = NULL;
    ALLEGRO_SAMPLE* song = NULL;

    int displayX = al_get_display_width(display);
    int displayY = al_get_display_height(display);

    //-------------------------------FILA DE EVENTOS---------------------------------//
    registerEventsSource(queue, display, timer, scoreTimer, cardTimer);
    al_set_window_title(display, "Memory Game");
    al_hide_mouse_cursor(display);
    bitmap = al_load_bitmap("./assets/bg/tile.png");
    cat = al_load_bitmap("./assets/cat/cat1r.png");
    mainMenu = al_load_bitmap("./assets/bg/main_menu.png");
    instructionsMenu = al_load_bitmap("./assets/bg/instructions.png");

    //-------------------------------VARIÁVEIS LOCAIS---------------------------------//
    int mouseX = 0, mouseY = 0;
    int dialogStep = 1;

    int catX = 40, catY = 440;

    int timeLeft = 15;
    int timeOverPenalty = 2;
    int wrongCardPenalty = 5;

    int firstCard = NULL;
    bool hasFlippedCard = false;
    int movement = 0, score = 0;
    int cardsFlipped = 0;

    char dialogText[1000] = {"Olá! Bem-vindo ao nosso jogo da memória! (Clique para continuar)"}; // MENSAGEM DE BOAS VINDAS (Precisa arrumar a digitação e colocar a quebra de linha)
    int gameState = 0;

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

    deck cardEasy[16];
    deck cardMedium[16];
    deck cardHard[16];
    
    deck currentCards[16];
    
    //-------------------------------EASY---------------------------------//
    cardEasy[0] = { 0, al_load_bitmap("./assets/card/easy/amigo.png"), 0};
    cardEasy[1] = { 1, al_load_bitmap("./assets/card/easy/bola.png") , 0 };
    cardEasy[2] = { 2, al_load_bitmap("./assets/card/easy/cachorro.png"), 0 };
    cardEasy[3] = { 3, al_load_bitmap("./assets/card/easy/cadeira.png"), 0 };
    cardEasy[4] = { 3, al_load_bitmap("./assets/card/easy/espada.png"), 0 };
    cardEasy[5] = { 3, al_load_bitmap("./assets/card/easy/gato.png"), 0 };
    cardEasy[6] = { 3, al_load_bitmap("./assets/card/easy/ola.png"), 0 };
    cardEasy[7] = { 3, al_load_bitmap("./assets/card/easy/peixe.png"), 0 };

    cardEasy[8] = { 0,  al_load_bitmap("./assets/card/easy/friend.png"), 1 };
    cardEasy[9] = { 1,  al_load_bitmap("./assets/card/easy/ball.png"), 1 };
    cardEasy[10] = { 2, al_load_bitmap("./assets/card/easy/dog.png"), 1 };
    cardEasy[11] = { 3, al_load_bitmap("./assets/card/easy/chair.png"), 1 };
    cardEasy[12] = { 3, al_load_bitmap("./assets/card/easy/sword.png"), 1 };
    cardEasy[13] = { 3, al_load_bitmap("./assets/card/easy/cat.png"), 1 };
    cardEasy[14] = { 3, al_load_bitmap("./assets/card/easy/hello.png"), 1 };
    cardEasy[15] = { 3, al_load_bitmap("./assets/card/easy/fish.png"), 1 };

    //-------------------------------MEDIUM---------------------------------//
    cardMedium[0] = { 0, al_load_bitmap("./assets/card/medium/obrigado.png"), 0 };
    cardMedium[1] = { 1, al_load_bitmap("./assets/card/medium/morango.png") , 0 };
    cardMedium[2] = { 2, al_load_bitmap("./assets/card/medium/framboesa.png"), 0 };
    cardMedium[3] = { 3, al_load_bitmap("./assets/card/medium/banheiro.png"), 0 };
    cardMedium[4] = { 3, al_load_bitmap("./assets/card/easy/espada.png"), 0 };
    cardMedium[5] = { 3, al_load_bitmap("./assets/card/easy/gato.png"), 0 };
    cardMedium[6] = { 3, al_load_bitmap("./assets/card/easy/ola.png"), 0 };
    cardMedium[7] = { 3, al_load_bitmap("./assets/card/easy/peixe.png"), 0 };

    cardMedium[8] = { 0,  al_load_bitmap("./assets/card/medium/thankyou.png"), 1 };
    cardMedium[9] = { 1,  al_load_bitmap("./assets/card/medium/strawberry.png"), 1 };
    cardMedium[10] = { 2, al_load_bitmap("./assets/card/medium/raspberry.png"), 1 };
    cardMedium[11] = { 3, al_load_bitmap("./assets/card/medium/restroom.png"), 1 };
    cardMedium[12] = { 3, al_load_bitmap("./assets/card/easy/sword.png"), 1 };
    cardMedium[13] = { 3, al_load_bitmap("./assets/card/easy/cat.png"), 1 };
    cardMedium[14] = { 3, al_load_bitmap("./assets/card/easy/hello.png"), 1 };
    cardMedium[15] = { 3, al_load_bitmap("./assets/card/easy/fish.png"), 1 };

    //-------------------------------HARD---------------------------------//
    cardHard[0] = { 3, al_load_bitmap("./assets/card/hard/cve.png"), 0 };
    cardHard[1] = { 3, al_load_bitmap("./assets/card/hard/dove.png"), 0 };
    cardHard[2] = { 3, al_load_bitmap("./assets/card/hard/evp.png"), 0 };
    cardHard[3] = { 3, al_load_bitmap("./assets/card/hard/qesn.png"), 0 };
    cardHard[4] = { 0, al_load_bitmap("./assets/card/medium/obrigado.png"), 0 };
    cardHard[5] = { 1, al_load_bitmap("./assets/card/medium/morango.png") , 0 };
    cardHard[6] = { 2, al_load_bitmap("./assets/card/medium/framboesa.png"), 0 };
    cardHard[7] = { 3, al_load_bitmap("./assets/card/medium/banheiro.png"), 0 };
        
    cardHard[8] = { 3,  al_load_bitmap("./assets/card/hard/hay.png"), 1 };
    cardHard[9] = { 3,  al_load_bitmap("./assets/card/hard/wayf.png"), 1 };
    cardHard[10] = { 3, al_load_bitmap("./assets/card/hard/igt.png"), 1 };
    cardHard[11] = { 3, al_load_bitmap("./assets/card/hard/wiyn.png"), 1 };
    cardHard[12] = { 0, al_load_bitmap("./assets/card/medium/thankyou.png"), 1 };
    cardHard[13] = { 1, al_load_bitmap("./assets/card/medium/strawberry.png"), 1 };
    cardHard[14] = { 2, al_load_bitmap("./assets/card/medium/raspberry.png"), 1 };
    cardHard[15] = { 3, al_load_bitmap("./assets/card/medium/restroom.png"), 1 };

    //-------------------------------ÁUDIOS-----------------------------------------//
    al_reserve_samples(1);
    song = al_load_sample("./asstes/sfx/songTest.wav");
    songInstance = al_create_sample_instance(song);
    al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
    //-----------------------------------------------------------------------------//

    assert(display != NULL);
    al_start_timer(cardTimer);
    al_start_timer(timer);

    while(gameState != 5){

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            
            if (event.timer.source == scoreTimer) {
                if (al_get_timer_count(scoreTimer) >= timeLeft) {
                    al_set_timer_count(scoreTimer, 0);
                    if (timeOverPenalty == 1) {
                        sprintf_s(dialogText, "Tempo esgotado! você perdeu %d ponto!", timeOverPenalty);
                        cat = al_load_bitmap("./assets/cat/cat3r.png");
                        catX = 40, catY = 418;
                    }
                    else {
                        sprintf_s(dialogText, "Tempo esgotado! você perdeu %d pontos!", timeOverPenalty);
                        cat = al_load_bitmap("./assets/cat/cat3r.png");
                        catX = 40, catY = 418;
                    }
                    score -= timeOverPenalty;
                }
            }

            if (event.timer.source == timer) {
                // Sempre vai ser renderizado (Não colocar condição de gameState)
                al_draw_bitmap(bitmap, 0, 0, 0); //DESENHA O TILE (BACKGROUND)
                //---------------------------------------------------------------

                if (gameState == 0) {
                    al_draw_bitmap(mainMenu, 0, 0, 0); 
                }

                if (gameState == 2) {
                    al_draw_bitmap(instructionsMenu, 0, 0, 0);
                }

                if (gameState == 1) {
                    al_draw_text(biggerFont, al_map_rgb(255, 255, 255), displayX / 2, 50, ALLEGRO_ALIGN_CENTRE, "Selecione a dificuldade:");
                    al_draw_rectangle(
                        displayX / 2 - 355, displayY / 2 - 20,
                        displayX / 2 - 155, displayY / 2 + 70,
                        al_map_rgb(255, 255, 255),
                        3
                    );
                    al_draw_text(
                        font,
                        al_map_rgb(255, 255, 255),
                        displayX / 2 - 255,
                        displayY / 2,
                        ALLEGRO_ALIGN_CENTRE,
                        "Fácil"
                    );
                    al_draw_rectangle(
                        displayX / 2 - 100, displayY / 2 - 20,
                        displayX / 2 + 100, displayY / 2 + 70,
                        al_map_rgb(255, 255, 255),
                        3
                    );
                    al_draw_text(
                        font,
                        al_map_rgb(255, 255, 255),
                        displayX / 2,
                        displayY / 2,
                        ALLEGRO_ALIGN_CENTRE,
                        "Médio"
                    );
                    al_draw_rectangle(
                        displayX / 2 + 155, displayY / 2 - 20,
                        displayX / 2 + 355, displayY / 2 + 70,
                        al_map_rgb(255, 255, 255),
                        3
                    );
                    al_draw_text(
                        font,
                        al_map_rgb(255, 255, 255),
                        displayX / 2 + 255,
                        displayY / 2,
                        ALLEGRO_ALIGN_CENTRE,
                        "Difícil"
                    );
                }


                if (gameState == 3 || gameState == 4) {
                    al_draw_bitmap(cat, catX, catY, 0);
                    drawCards(card, currentCards);
                    al_draw_rectangle(38, 16, 98, 48, al_map_rgb(255, 255, 255), 3);
                    al_draw_rectangle(320, 700, 1250, 600, al_map_rgb(255, 255, 255), 3); // Caixa de diálogo
                    al_draw_text(font, al_map_rgb(255, 255, 255), 330, 600, 0, dialogText);
                    al_draw_text(font, al_map_rgb(255, 255, 255), 70, 10, ALLEGRO_ALIGN_CENTRE, "Sair");
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 400, 10, 0, "Tempo restante: %d", timeLeft - al_get_timer_count(scoreTimer));
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 800, 10, 0, "Movimentos: %d", movement);
                    al_draw_textf(font, al_map_rgb(255, 255, 255), 1000, 10, 0, "Pontos: %d", score);
                    if(cardsFlipped == 8){
                        al_stop_timer(scoreTimer);
                        al_set_timer_count(scoreTimer, 0);
                        gameState = 4;
                        al_draw_filled_rectangle(0, 0, 1280, 720, al_map_rgba(0, 0, 0, 155));
                        if (score < 0) {
                            al_draw_text(biggerFont, al_map_rgb(255, 255, 255), displayX / 2, displayY / 2 - 50, ALLEGRO_ALIGN_CENTRE, "Que pena, você perdeu =(");
                        }
                        else {
                            al_draw_text(biggerFont, al_map_rgb(255, 255, 255), displayX / 2, displayY / 2 - 50, ALLEGRO_ALIGN_CENTRE, "Parabéns, você ganhou!");
                        }
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
                //---------------------------------------------------------------
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
                    al_set_timer_count(scoreTimer, 0);
                    al_stop_timer(scoreTimer);
                    strcpy_s(dialogText, "Olá! Bem-vindo ao nosso jogo da memória! (Clique para continuar)");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat1r.png");
                break;
                case 1:
                    al_set_timer_count(scoreTimer, 0);
                    al_stop_timer(scoreTimer);
                    strcpy_s(dialogText, "Nele você aprenderá inglês por assimilação.");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat2r.png");
                    catX = 15, catY = 458;
                break;
                case 2:
                    strcpy_s(dialogText, "Clique em duas cartas, se elas forem iguais você ganhará pontos!");
                    dialogStep++;
                    cat = al_load_bitmap("./assets/cat/cat3r.png");
                    catX = 40, catY = 418;
                break;
                case 3:
                    strcpy_s(dialogText, "É isso, Boa sorte! E cuidado para não deixar o tempo acabar!");
                    cat = al_load_bitmap("./assets/cat/cat1r.png");
                    catX = 15, catY = 458;
                    al_start_timer(scoreTimer);
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
                            sprintf_s(dialogText, "Boa! Você ganhou %d pontos", (timeLeft - al_get_timer_count(scoreTimer)) + 1);
                            cat = al_load_bitmap("./assets/cat/cat1r.png");
                            catX = 15, catY = 458;
                            score++;
                            card[i].flipped = true;
                            card[i].locked = true;
                        }
                        else {
                            score -= wrongCardPenalty;
                            sprintf_s(dialogText, "Puts! Você perdeu %d pontos", wrongCardPenalty);
                            cat = al_load_bitmap("./assets/cat/cat2r.png");
                            catX = 15, catY = 458;
                            al_stop_timer(scoreTimer);
                            card[i].flipped = true;
                            al_set_timer_count(cardTimer, 0);
                            while(al_get_timer_count(cardTimer) < 1) {
                                drawCards(card, currentCards);
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
            //----------------------------------------------------------------------------//

            //-------------------------------BOTÕES DO GAME STATE 1 (Level Select)---------------------------------//
            if (mouseX >= displayX / 2 - 355 && mouseY >= displayY / 2 - 20 &&
                mouseX <= displayX / 2 - 155 && mouseY <= displayY / 2 + 70 &&
                gameState == 1
                ) {
                // Dificuldade: Fácil
                dialogStep = 1;
                for (int i = 0; i < 16; i++) {
                    currentCards[i] = cardEasy[i];
                }
                timeLeft = 20;
                timeOverPenalty = 1;
                wrongCardPenalty = 3;

                cardsFlipped = 0;
                gameState = 3;
                mapCards(card);
                al_start_timer(scoreTimer);
            }
            if (mouseX >= displayX / 2 - 100 && mouseY >= displayY / 2 - 20 &&
                mouseX <= displayX / 2 + 100 && mouseY <=  displayY / 2 + 70 &&
                gameState == 1
                ){
                // Dificuldade: Média
                dialogStep = 1;
                for (int i = 0; i < 16; i++) {
                    currentCards[i] = cardMedium[i];
                }
                timeLeft = 15;
                timeOverPenalty = 2;
                wrongCardPenalty = 5;

                cardsFlipped = 0;
                gameState = 3;
                mapCards(card);
                al_start_timer(scoreTimer);
            }
            if (mouseX >= displayX / 2 + 155 && mouseY >= displayY / 2 - 20 &&
                mouseX <= displayX / 2 + 355 && mouseY <= displayY / 2 + 70 &&
                gameState == 1
                ) {
                // Dificuldade: Difícil
                dialogStep = 1;
                for (int i = 0; i < 16; i++) {
                    currentCards[i] = cardHard[i];
                }
                timeLeft = 8;
                timeOverPenalty = 4;
                wrongCardPenalty = 9;

                cardsFlipped = 0;
                gameState = 3;
                mapCards(card);
                al_start_timer(scoreTimer);
            }

            //-------------------------------BOTÕES DO GAME STATE 4 (Finished Level)---------------------------------//
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
                gameState == 4
                ){ 
                // SAIR
                movement = 0;
                score = 0;
                gameState = 0;
            }
            //-------------------------------BOTÕES DO GAME STATE 3 (Playing)---------------------------------//
            if (mouseX >= 38 && mouseY >= 16 &&
                mouseX <= 98 && mouseY <= 48 &&
                gameState == 3
                ) {
                // SAIR
                gameState = 0;
            }
            //-------------------------------BOTÕES DO GAME STATE 2 (Instructions)---------------------------------//
            if (mouseX >= 250 && mouseY >= 140 &&
                mouseX <= 300 && mouseY <= 190 &&
                gameState == 2
                ) {
                gameState = 0;
            }
            //-------------------------------BOTÕES DO GAME STATE 0 (Main Menu)---------------------------------//
            if (mouseX >= 510 && mouseY >= 340 &&
                mouseX <= 855 && mouseY <= 375 &&
                gameState == 0
                ) {
                gameState = 1;
            }
            if (mouseX >= 510 && mouseY >= 440 &&
                mouseX <= 855 && mouseY <= 475 &&
                gameState == 0
                ) {
                gameState = 2;
            }if (mouseX >= 510 && mouseY >= 575 &&
                mouseX <= 855 && mouseY <= 630 &&
                gameState == 0
                ) {
                gameState = 5;
            }
        }
        // Se o usuário clicar no "X", o gameState será 5 e irá fechar o jogo
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { gameState = 5; }
    }

    destroyGame(display, timer, scoreTimer, cardTimer, bitmap, font);
    return 0;
}