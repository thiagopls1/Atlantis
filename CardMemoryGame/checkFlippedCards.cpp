#include "checkFlippedCards.h"

int checkFlippedCards(int firstCard, int secondCard){
	if (firstCard == secondCard) {
		return 1;
	}
	if(firstCard != secondCard) {
		return 0;
	}
}