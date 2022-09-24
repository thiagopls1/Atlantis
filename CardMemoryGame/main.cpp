#include <allegro5\allegro5.h>

int main() {

	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
	al_set_window_title(display, "Card Memory Game");

	bool running = true;
	while(running){
		al_clear_to_color(al_map_rgb(255, 150, 220));
		al_flip_display();
	}

	al_destroy_display(display);
	return 0;
}
