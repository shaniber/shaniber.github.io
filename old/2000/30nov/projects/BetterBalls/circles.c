/*
 * circles.h
 * Standard reusable functions to move a circle
 * (from the vivace allegro tutorial, with mods by ssd)
 */

#include <stdlib.h>
#include <allegro.h>
#include "circles.h"

CIRCLE_T *circle_init(int new_x, int new_y, int new_radius,
		      int new_col, int new_xs, int new_ys)
{
    CIRCLE_T *temp;

    /* Allocate memory for the circle. If unsuccessful, return NULL. */
    temp = malloc(sizeof(CIRCLE_T));

    if (!temp)
		return NULL;

	/* make sure that all of the circles are completely within the screen */
	//if ((new_x - new_radius) <= 0)
	//	new_x = new_radius+25;
	//if ((new_x + new_radius) >= SCREEN_W)
	//	new_x = SCREEN_W-new_radius-25;
	//if ((new_y - new_radius) <= 0)
	//	new_y = new_radius+25;
	//if ((new_y + new_radius) >= SCREEN_H)
	//	new_y = SCREEN_H-new_radius-25;

    temp->x = new_x;
    temp->y = new_y;
    temp->r = new_radius;
    temp->col = new_col;
    temp->xs = new_xs;
    temp->ys = new_ys;
    temp->dx = temp->dy = 0;

    return temp;
}

void circle_destroy(CIRCLE_T * circle)
{
    if (circle)
	free(circle);
}

void circle_draw(CIRCLE_T *circle, BITMAP *bmp)
{
    circlefill(bmp, circle->x, circle->y, circle->r, circle->col);

    circle->dx = circle->x;
    circle->dy = circle->y;
	//textprintf(bmp, font, circle->x, circle->y+circle->r, makecol(255, 0, 0), "x:%d y:%d r:%d", circle->x, circle->y, circle->r);
}

void circle_update(CIRCLE_T * circle)
{
    // First we update the position of the circle...
    circle->x += circle->xs;
    circle->y += circle->ys;

    // Now we see if it reached the maximum frame border
	//if (circle->x+circle->r > SCREEN_W-5)
	//	circle->xs *= -1;

    //if (circle->y+circle->r > SCREEN_H-5)
	//	circle->ys *= -1;

    //if (circle->x-circle->r < 5)
	//circle->xs *= -1;

    //if (circle->y-circle->r < 5)
	//circle->ys *= -1;
}

void circle_erase(CIRCLE_T * circle, BITMAP * bmp)
{
	circlefill(bmp, circle->dx, circle->dy, circle->r, 0);
	
}
