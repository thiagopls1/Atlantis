#ifndef CARD_CLICKED
#define CARD_CLICKED
#include "cardPos.h"

void cardClicked(cardPos card[8], int c, int mouseX, int mouseY, int firstCard, int secondCard, bool hasFlippedCard, int* score, int* movement, ALLEGRO_EVENT event);
#endif
