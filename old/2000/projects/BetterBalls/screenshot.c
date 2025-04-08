
/*
 * screenshot.c
 */

#include <allegro.h>
#include "screenshot.h"

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