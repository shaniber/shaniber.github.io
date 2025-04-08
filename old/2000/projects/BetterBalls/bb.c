
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#include "bb.h"
#include "screenshot.h"
#include "circles.h"
#include "collisions.h"

/* global variable declarations */

int end_game = 0;				/* end game flag... 1 is game on, 0 is end game */
BITMAP *offScreen;				/* off screen bitmap used for double buffering */
CIRCLE_T *circles[MAX_CIRCLES];	/* the list of circles */

/* end global variable declarations */


int main(int argc, char *argv[]) {

	/* install_allegro(SYSTEM_AUTODETECT, &errno, atexit); */
	allegro_init();

	init();						/* initialize our 'game' */

	do {						/* game loop */
		input();				/* get input */
		process();				/* process inputs */
		output();				/* show output */
	} while (!end_game);		/* until end_game flag is set */

	cleanup();					/* clean up everything we made */

	return 0;
}
END_OF_MAIN();

void init(void) {

	int f, g;					/* loop variables */
	CIRCLE_T *new_circle;		/* new circle variable */
	int good_circle=0;			/* flag to determine if a circle is good */
	
	install_keyboard();

	set_color_depth(8);

	if ( set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0) < 0 ) {
		allegro_exit();
		allegro_message("Error setting graphics mode:\n%s\n", allegro_error);

		exit(1);
	}

	srand(time(NULL));

	/* allocate offScreen double buffer bitmap */
    offScreen = create_bitmap(SCREEN_W, SCREEN_H);
    if (offScreen == NULL) {
		allegro_exit();
		allegro_message("Not enough memory to allocate double buffer!\n");
		exit(1);
    }
    clear(offScreen);
	new_circle = circle_init(0, 0, 0, 0, 0, 0);
	
	/* create MAX_CIRCLES circles, making sure that they don't overlap */
    for (f = 0; f < MAX_CIRCLES; f++) {
		
		/* these variables are safe to do once per circle */
		new_circle->r = ((rand() % 20) + 5);
		new_circle->col = ((rand() % 15) + 1);
		new_circle->xs = ((rand() % 7) - 3);
		new_circle->ys = ((rand() % 7) - 3);
		
		/* if we don't have any circles created... */
		if (f==0) {
			new_circle->x = rand() % SCREEN_W-25;
			new_circle->y = rand() % SCREEN_H-25;
		}
		/* ...otherwise check to make sure that the circle isn't stuck in another */
		else {
			/* while the circle isn't good */
			do {
				good_circle = 0;

				new_circle->x = rand() % SCREEN_W-25;
				new_circle->y = rand() % SCREEN_H-25;

				/* check to make sure the new circle isn't resting on a wall */
				if ((new_circle->x - new_circle->r) <= 0)
					{ new_circle->x = new_circle->r + 50; }
				if ((new_circle->x + new_circle->r) >= SCREEN_W)
					{ new_circle->x  = SCREEN_W - new_circle->r + 50; }
				if ((new_circle->y - new_circle->r) <= 0)
					{ new_circle->y = new_circle->r - 50; }
				if ((new_circle->y + new_circle->r) >= SCREEN_H)
					{ new_circle->y = SCREEN_H - new_circle->r - 50; }
				
				/* for each existing circle... */
				for (g=0; g<f; g++) {
					/* check if the new_circle is within an existing circle */
					if (coll_checkCircle(new_circle, circles[g]) || coll_checkCircle(circles[g], new_circle))
						{ good_circle = 1; }
				}
			} while (good_circle == 1);
		}		

		circles[f] = circle_init(new_circle->x, new_circle->y, new_circle->r, 
			                     new_circle->col, new_circle->xs, new_circle->ys);

		/* show the circles as they're drawn */
		circle_draw(circles[f], offScreen);
		//show_double_buffer();

	}

	show_double_buffer();
	readkey();

	/* clean up after ourselves */
	circle_destroy(new_circle);
} /* end of init */

void input(void) {

	int key;		/* our keypress */

	if (keypressed()) {
		key = readkey();
		if (key >> 8 == KEY_F1)
			{ takeScreenshot(); }
		else 
			{ end_game++; }
	}
} /* end of input */

void process(void) {
	int f,g;			/* temp loop variables */
	int collision=0;	/* collision detection... assume no collisions at start */

	for (f=0; f<MAX_CIRCLES; f++) { 
		
		/* check for border collision */
		coll_checkWalls(circles[f]);
		
		/* check for collisions with all other circles */
		for (g=0; g<MAX_CIRCLES; g++) {

			/* don't check if its the same circle! */
			if (g != f) 
				{ collision = coll_checkCircle(circles[f], circles[g]); }
			/* bounce the balls if a collision is detected */
			if (collision) {
				coll_bounceCircles(circles[f], circles[g]);
				collision = 0;
			}
		}

		/* finally, update the circle's position */
		circle_update(circles[f]);
		
		
		
	}
} /* end of process */

void output(void) {
	
	int f;
    
	/* erase the circles... */
	for (f = 0; f < MAX_CIRCLES; f++)
		circle_erase(circles[f], offScreen);

	/* ...then draw the circles! */
    for (f = 0; f < MAX_CIRCLES; f++)
		circle_draw(circles[f], offScreen);

    show_double_buffer();
} /* end of output */

void cleanup(void) {
    int f;

	/* destroy all of the circles and the double buffer bitmap */
    for (f = 0; f < MAX_CIRCLES; f++)
		circle_destroy(circles[f]);

    destroy_bitmap(offScreen);
}

void show_double_buffer(void) {
    vsync();
    blit(offScreen, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}