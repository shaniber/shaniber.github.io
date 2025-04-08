
/*
 * circles.c - Standard reusable functions to move a circle
 * 
 * Author: vivace tutorial
 * Modification History
 * By:		Date:		Action:
 * ---		-----		-------
 * ssd133	13jul00		modified for floating-point physics.
 */

#include <stdlib.h>
#include <allegro.h>
#include "circles.h"

CIRCLE_T *circle_init(float new_x, float new_y, float new_radius,
		      float new_col, float new_xs, float new_ys)
{
    CIRCLE_T *temp;

    /* Allocate memory for the circle. If unsuccessful, return NULL. */
    temp = malloc(sizeof(CIRCLE_T));

    if (!temp)
		return NULL;

    temp->x = new_x;
    temp->y = new_y;
    temp->r = new_radius;
    temp->col = new_col;
    temp->xs = new_xs;
    temp->ys = new_ys;
    temp->dx = temp->dy = 0.0;

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
}

void circle_update(CIRCLE_T * circle)
{
    // update the position of the circle...
    circle->x += circle->xs;
    circle->y += circle->ys;
}

void circle_erase(CIRCLE_T * circle, BITMAP * bmp)
{
	circlefill(bmp, circle->dx, circle->dy, circle->r, 0);
}
