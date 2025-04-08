#include <allegro.h>

void takeScreenshot (void) {
	/*
	 * Function:  takeScreenshot
	 * Purpose:   Capture a screenshot from the running program 
	 *            and save it to a pcx file.
	 * Returns:   void
	 */

	BITMAP *screenshot;		/* temporary screenshot bitmap */
	PALETTE pal;

	get_palette(pal);

	screenshot = create_sub_bitmap(screen, 0, 0, SCREEN_W, SCREEN_H);

	save_pcx("screen.pcx", screenshot, pal);

	destroy_bitmap(screenshot);

} /* end function takeScreenshot */

int main(int argc, char *argv[])
{
	char string[] = "We're making Bitmaps today!";
	int midpoint = 0;
	int key;

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

	/* check for key presses... too obfuscated? */
	while (1==1) {

		key = readkey();
		
		if (key >> 8 == KEY_F1) {
			takeScreenshot();
		}
		else if (key >> 8 == KEY_Q) {
			return 0;
		}
	}

}
END_OF_MAIN();

