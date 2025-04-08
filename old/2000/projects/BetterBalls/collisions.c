
/*
 * collisions.c
 * routines for collision detection of circles
 */

#include <allegro.h>
#include "circles.h"
#include "collisions.h"

/*
 * function: checkCircle
 * purpose:  check to see if c1 has collided with c2
 * returns:  1 if a collision has occurred
 *			 0 if no collision has occured
 */
int coll_checkCircle (CIRCLE_T *c1, CIRCLE_T *c2) {
	
	int watch_x = 0;		/* dirty x flag */
	int watch_y = 0;		/* dirty y flag */

	/* check if c1->x is within c2's x */
	/* c1.rhs > c2.lhs && c1.rhs < c2.rhs */
	if ( ( (c1->x + c1->r) >= (c2->x - c2->r) ) && 
		 ( (c1->x + c1->r) <= (c2->x + c2->r) ) )
		{ watch_x = 1; }							/* watch_x! */
	/* c1.lhs > c2.lhs && c1.lhs > c2.rhs */
	else if ( ( (c1->x - c1->r) >= (c2->x - c2->r) ) && 
		      ( (c1->x - c1->r) <= (c2->x + c2->r) ) )
		{ watch_x = 1; }							/* watch_x! */

	/* check if c1->y is within c2 */				
	/* c1.top > c2.bot && c1.top < c2.top */
	if ( ( (c1->y - c2->r) <= (c2->y + c2->r) ) && 
		 ( (c1->y - c1->r) >= (c2->y - c2->r) ) )
		{ watch_y = 1; }							/* watch_y! */
	/* c1.bot > c2.bot && c1.bot < c2.top */
	else if ( ( (c1->y + c1->r) <= (c2->y + c2->r) ) && 
		      ( (c1->y + c1->r) >= (c2->y - c2->r) ) )
		{ watch_y = 1; }							/* watch_y! */

	/* if the x and the y are both within the circle's range... */
	if (watch_x==1 && watch_y==1)
		{
			//textprintf(screen, font, c1->x, c1->y, makecol(255, 0, 0), "x:%d y:%d r:%dBAD!", c1->x, c1->y, c1->r);
			//readkey();
			return 1; }	/* a collision has occured */
	else
		{ return 0; }	/* there is no collision */
}

/*
 * function: checkWalls
 * purpose:  Check to see if circle has collided with a wall.
 *			 Changes the direction if there is a collision
 */
void coll_checkWalls (CIRCLE_T *circle) {

	/* we don't check the exact edge of the wall, to make it 
	   look a little more realistic */
    if (circle->x+circle->r > SCREEN_W-5)
		{ circle->xs *= -1; }

    if (circle->y+circle->r > SCREEN_H-5)
		{ circle->ys *= -1; }

    if (circle->x-circle->r < 5)
		{ circle->xs *= -1; }

    if (circle->y-circle->r < 5)
		{ circle->ys *= -1;} 
}

/*
 * function: checkWalls
 * purpose:  Bounce c1 off of c2.  
 *			 Simplified physics model here... just switch the velocities.
 */
void coll_bounceCircles(CIRCLE_T *c1, CIRCLE_T*c2) {
	
	int xs_temp, ys_temp;		/* temp variables for velocity vector */

	/* save c1's velocity vector */
	xs_temp = c1->xs;
	ys_temp = c1->ys;

	/* determine c1's new velocity */
	c1->xs = c2->xs;
	c1->ys = c2->ys;

	/* determine c2's new velocity */
	c2->xs = xs_temp;
	c2->ys = ys_temp;

	/* that's all she wrote */
}
