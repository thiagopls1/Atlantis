#include <allegro5/allegro5.h>
#include "checkFlippedCards.h"
#include "cardClicked.h"
#include "cardPos.h"
#include "deck.h"

void cardClicked(cardPos card[8], int c, int mouseX, int mouseY, int firstCard, int secondCard, bool hasFlippedCard, int* score, int* movement, ALLEGRO_EVENT event) {
    if (event.mouse.button = 1 && mouseX >= card[0].x1 && mouseX <= card[0].x2 && mouseY >= card[0].y1 && mouseY <= card[0].y2) {
        card[c].cardFlipped = true;
        hasFlippedCard = true;
        if (firstCard == NULL) {
            firstCard = card[c].cardId;
        }
        else if (secondCard == NULL) {
            secondCard = card[c].cardId;
        }
        if (hasFlippedCard) {
            score += checkFlippedCards(firstCard, secondCard);
            movement++;
        }
    }
}