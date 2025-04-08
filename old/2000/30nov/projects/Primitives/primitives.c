
#include <allegro.h>
#include "screenshot.h"

int main(int argc, char *argv[])
{
	int key, i;

	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);

	install_keyboard();

	set_color_depth(8);

	if ( set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0 ) {
		allegro_exit();
		allegro_message("Error setting graphics mode.\nExiting...\n");

		return -1;
	}

	clear(screen);

	/* 5 pixels of random colours */
	textout(screen, font, "Points:", 100, 10, makecol(255, 0, 0));
	for (i=0; i<25; i=i+5) {
		putpixel(screen, 250+i, 15, rand()%256);
	}

	/* vertical line */
	textout(screen, font, "Vertical Line:", 100, 35, makecol(255,0,0));
	vline(screen, 250, 35, 20, rand()%256);

	/* horizontal line */
	textout(screen, font, "Horizontal Line:", 100, 50, makecol(255, 0, 0));
	hline(screen, 250, 55, 265, rand()%256);

	/* just a line */
	textout(screen, font, "Generic Line:", 100, 75, makecol(255, 0, 0));
	line(screen, 250, 80, 265, 65, rand()%256);

	/* triangle */
	textout(screen, font, "Triangle:", 100, 100, makecol(255, 0, 0));
	triangle(screen, 250, 110, 250, 95, 275, 103, rand()%256);

	/* rectangle */
	textout(screen, font, "Rectangle:", 100, 125, makecol(255, 0, 0));
	rect(screen, 250, 125, 275, 145, rand()%256);

	/* filled rectangle */
	textout(screen, font, "Filled Rectangle:", 100, 155, makecol(255, 0, 0));
	rectfill(screen, 250, 155, 275, 175, rand()%256);

	/* circle */
	textout(screen, font, "Circle:", 100, 190, makecol(255, 0, 0));
	circle(screen, 260, 195, 10, rand()%256);

	/* filled circle */
	textout(screen, font, "Filled Circle:" ,100, 215, makecol(255, 0, 0));
	circlefill(screen, 260, 220, 10, rand()%256);

	textout (screen, font, "And Many Others...", 100, 235, makecol(255, 0, 0));

	/* check for key presses... this could be in another function!*/
	while (1) {

		key = readkey();
		
		if (key >> 8 == KEY_F1) {
			takeScreenshot();
		}
		else if (key >> 8 == KEY_ENTER) {
			return 0;
		}
	}

}
END_OF_MAIN();
