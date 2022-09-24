#include <allegro5\allegro5.h>

int main() {

	al_init();		//Inicialização do Allegro
	ALLEGRO_DISPLAY* display = al_create_display(1280, 900);		//Criação de "tela"
	al_rest(10);
}
