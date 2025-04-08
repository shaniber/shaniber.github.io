#include <allegro.h>

int main(int argc, char *argv[])
{
	char string[] = "Hello, World!";
	int midpoint = 0;

	install_allegro(SYSTEM_AUTODETECT, &errno, atexit);

	if ( install_keyboard() )
	{
		allegro_exit();
		allegro_message("Error installing keyboard handler.\nExiting...\n");
		
		return -1;
	}

	set_color_depth(8);

	if ( 0 > set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) )
	{
		allegro_exit();
		allegro_message("Error setting graphics mode.\nExiting...\n");

		return -1;
	}

	clear(screen);

	midpoint = (SCREEN_W - text_length(font, string)) /2;

	textout(screen, font, string, midpoint, SCREEN_H/2, makecol(255, 0, 0));

	readkey();

	return 0;

}
END_OF_MAIN();
