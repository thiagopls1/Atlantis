#pragma once
#include <allegro5/allegro.h>

struct cardInfo{
	int cardId;
	int cardPos;
	bool cardFlipped;
	ALLEGRO_COLOR color;
	int x1, y1, x2, y2;
};
cardInfo;
