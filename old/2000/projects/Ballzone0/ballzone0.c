/*
 * ballzone0.c - includes init, input, output, and process functions
 *
 * Author: ssd
 * Modification History
 * By:		Date:		Action:
 * ---		-----		-------
 * ssd		11sep00		created this file.
 * ssd		19sep00		'fixed' mouse input.
 */

/* include some important libraries */
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include <math.h>

/* include our header files */
#include "ballzone0.h"
#include "screenshot.h"
#include "circles.h"
#include "collisions.h"
#include "input.h"

/* global variable declarations */
int end_game = 0;				// end game flag... 1 is game on, 0 is end game
BITMAP *offScreen;				// off screen bitmap used for double buffering
CIRCLE_T *myBall;				// the user's circle (red)
CIRCLE_T *enemyBall;			// the braindead computer ball (blue)
int mouseFlag;					// mouse button has been pressed
/* end global variable declarations */

int main(int argc, char *argv[]) {
	
	allegro_init();

	init();						// initialize our 'game'

	do {						// game loop
		input();				// get input
		process();				// process inputs
		output();				// show output
	} while (!end_game);		// until end_game flag is set

	cleanup();					// clean up everything we made

	return 0;
}
END_OF_MAIN();

void init(void) {

	int good_circle=0;			// flag to determine if a circle is good

	srand(time(NULL));
	
	install_timer();
	install_keyboard();
	install_mouse();

	set_color_depth(8);

	if ( set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0 ) {
		allegro_exit();
		allegro_message("Error setting graphics mode:\n%s\n", allegro_error);

		exit(1);
	}

	/* allocate offScreen double buffer bitmap */
    offScreen = create_bitmap(SCREEN_W, SCREEN_H);
    if (offScreen == NULL) {
		allegro_exit();
		allegro_message("Not enough memory to allocate double buffer!\n");
		exit(1);
    }
    clear(offScreen);
	myBall = circle_init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	enemyBall = circle_init(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	
	/* initialize the balls */
	myBall->r    = 25.0;	// radii...
	enemyBall->r = 25.0;

	/* while the balls aren't good... */
	do {
		good_circle = 0;

		myBall->x = 100.0; //(float)(rand() % SCREEN_W - 25);
		myBall->y = 100.0; //(float)(rand() % SCREEN_H - 25);

		enemyBall->x = 540.0; //(float)(rand() % SCREEN_W - 25);
		enemyBall->y = 380.0; //(float)(rand() % SCREEN_H - 25);

		/* make sure the circles aren't sitting on the walls... */
		if ((myBall->x - myBall->r) <= 0)
			{ myBall->x = myBall->x + myBall->r + 50.0; }
		if ((myBall->x + myBall->r) >= SCREEN_W)
			{ myBall->x  = SCREEN_W - (SCREEN_W-myBall->x) - myBall->r - 50.0; }
		
		if ((myBall->y - myBall->r) <= 0)
			{ myBall->y = myBall->y - myBall->r - 50.0; }
		if ((myBall->y + myBall->r) >= SCREEN_H)
			{ myBall->y = SCREEN_H + (SCREEN_H-myBall->y) + myBall->r + 50.0; }


		if ((enemyBall->x - enemyBall->r) <= 0)
			{ enemyBall->x = enemyBall->x + enemyBall->r + 50.0; }
		if ((enemyBall->x + enemyBall->r) >= SCREEN_W)
			{ enemyBall->x  = SCREEN_W - (SCREEN_W-enemyBall->x) - enemyBall->r - 50.0; }
		
		if ((enemyBall->y - enemyBall->r) <= 0)
			{ enemyBall->y = enemyBall->y - enemyBall->r - 50.0; }
		if ((enemyBall->y + enemyBall->r) >= SCREEN_H)
			{ enemyBall->y = SCREEN_H + (SCREEN_H-enemyBall->y) + enemyBall->r + 50.0; }

		if (coll_checkCircle(myBall, enemyBall) || coll_checkCircle(myBall, enemyBall))
			{ good_circle = 1; }
	} while (good_circle == 1);

	/* these variables are safe to do once per circle */
		
	myBall->col = makecol(255,0,0);
	enemyBall->col = makecol(0,0,255);

	myBall->xs = 0;
	myBall->ys = 0;
	enemyBall->xs = (float)((rand() % 3) +3);
	enemyBall->ys = (float)((rand() % 3) +3);

	
	/* show the circles as they're drawn */
	circle_draw(myBall, offScreen);
	circle_draw(enemyBall, offScreen);

} /* end of init */

void input(void) {

	int key;		// our keypress
	
	// check for key presses
	if (keypressed()) {
		key = readkey();
		if (key >> 8 == KEY_F1)
			{ takeScreenshot(); }
		else if (key >> 8 == KEY_SPACE) {
			enemyBall->x = 99;
			enemyBall->y = 99;
			enemyBall->xs = 0;
			enemyBall->ys = 0;
		}
		else 
			{ end_game++; }
	}

	// check for mouse button presses

	if (mouse_b) {
		// right mouse button presses
		mouseFlag = mouse_b;	// a button has been pressed!
	}
} /* end of input */

void process(void) {
	
	int collision=0;	// collision detection... assume no collisions at start

	if (mouseFlag) {
		// deal with the mouse button press
		if (mouseFlag & 2) {
			// RMB sets myBall's XY coords to the XY coords of the mouse 
			// and myBall's speed vector to 0
			mouseFlag = 0;					// reset mouseFlag
			myBall->x = (float)mouse_x;		// move myBall to pointer
			myBall->y = (float)mouse_y;
			myBall->xs = 0.0;				// set myBall speed to 0.0
			myBall->ys = 0.0;
		} // end right mouse button

		if (mouseFlag & 1) {
			// LMB sets myBall's speed vector to the mouse's current 
			// position divided by the screen width/height
			mouseFlag = 0;

			myBall->xs = (mouse_x - myBall->x);
			myBall->ys = (mouse_y - myBall->y);
		} // end left mouse button

	} // end mice

	// check for border collision
	coll_checkWalls(myBall);
	coll_checkWalls(enemyBall);
	
	// check for collisions with all other circles
	collision = coll_checkCircle(myBall, enemyBall);

	// bounce the balls if a collision is detected
	if (collision) { 
	coll_bounceCircles(myBall, enemyBall);
		collision = 0;
	}

	// finally, update the circle's position
	circle_update(myBall);
	circle_update(enemyBall);
	textprintf(offScreen, font, 150, 150, makecol(0, 0, 0), "              ");
	textprintf(offScreen, font, 150, 150, makecol(255, 0, 0), "x:%d y:%d", (int)myBall->x, (int)myBall->y);

	
} /* end of process */

void output(void) {

	show_mouse(NULL);

	/* erase the circles... */
	circle_erase(myBall, offScreen);
	circle_erase(enemyBall, offScreen);

	/* ...then draw the circles! */
    
	circle_draw(myBall, offScreen);
	circle_draw(enemyBall, offScreen);

	show_mouse(offScreen);

    show_double_buffer();

} /* end of output */

void cleanup(void) {

	/* destroy all of the circles and the double buffer bitmap */
    circle_destroy(myBall);
	circle_destroy(enemyBall);
	
    destroy_bitmap(offScreen);
}

void show_double_buffer(void) {
    vsync();
    blit(offScreen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}