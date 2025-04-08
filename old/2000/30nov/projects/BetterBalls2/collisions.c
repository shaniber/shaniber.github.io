
/*
 * collisions.c
 * routines for collision detection of circles
 */

#include <math.h>
#include <allegro.h>
#include "circles.h"
#include "collisions.h"

/*
 * function: coll_checkCircle
 * purpose:  check to see if c1 has collided with c2
 * returns:  1 if a collision has occurred
 *			 0 if no collision has occured
 */
int coll_checkCircle (CIRCLE_T *c1, CIRCLE_T *c2) {

	// if sum of the squares of the differences in the position
	// are <= sum of the squares of the radii...
	if ( ((c1->x-c2->x)*(c1->x-c2->x)  +
		  (c1->y-c2->y)*(c1->y-c2->y)) <=
		  (c1->r+c2->r)*(c1->r+c2->r) )
		//there is a collision!
		{ return 1; }
	else
		{ return 0; }
} // end of checkCircle

/*
 * function: coll_checkWalls
 * purpose:  Check to see if circle will collide with a wall next update.
 *			 Changes the direction if there is a collision
 */
void coll_checkWalls (CIRCLE_T *circle) {

	/* we don't check the exact edge of the wall, to make it 
	   look a little more realistic */
    if (circle->x + circle->r >= SCREEN_W)//-5.0)
		{ circle->xs *= -1; circle->x -= 5;}

    if (circle->y + circle->r >= SCREEN_H)//-5.0)
		{ circle->ys *= -1; circle->y -= 5; }

    if (circle->x - circle->r <= 0)//5.0)
		{ circle->xs *= -1; circle->x += 5;}

    if (circle->y - circle->r <= 0)//5.0)
		{ circle->ys *= -1; circle->y += 5;} 
}

/*
 * function: coll_bounceCircles
 * purpose:  Bounce c1 off of c2.  
 *			 Simplified physics model here... just switch the velocities.
 */
void coll_bounceCircles(CIRCLE_T *c1, CIRCLE_T *c2) {

	float X1, Y1, X2, Y2, dist, velocity, cosine;
	float Hux1, Hux2, Huy1, Huy2;		//u is initial, v is final velocity
	float Hvx1, Hvx2, Hvy1, Hvy2;
	float Vux1, Vux2, Vuy1, Vuy2;		// H horiz, V vert
	float Vvx1, Vvx2, Vvy1, Vvy2;
	//float En1, En2;						// incoming and outgoing energies

	// incoming energy = sum of squares of c1 plus sum of squares of c2
	// note that this isn't used yet.
    //En1 = (c1->xs * c1->xs + c1->ys * c1->ys) + (c2->xs * c2->xs + c2->ys * c2->ys);

	/* .oO c1 Oo. */
	velocity = sqrt((float)(c1->xs * c1->xs + c1->ys * c1->ys));

	// here's where the magic happens... i wish i understood my linear algebra better.

	if (velocity <= 0.000001) {
		// if velocity is REALLY slow, treat it like 0
		X1 = Y1 = 0.0f;
		X2 = Y2 = 0.0f;
		Hux1 = Huy1 = Vux1 = Vuy1 = 0.0f; 
	}
	else {
		X1 = c1->xs/velocity; 
		Y1 = c1->ys/velocity;

		X2 = c2->x - c1->x;
		Y2 = c2->y - c1->y;

		dist = sqrt((float)(X2*X2 + Y2*Y2));  // should not be zero
		X2 /= dist;                           // since they don't overlap
		Y2 /= dist;
		cosine = X1*X2 + Y1*Y2;

		Hux1 = cosine*velocity*X2; 
		Huy1 = cosine*velocity*Y2;
		Vux1 = c1->xs - Hux1; 
		Vuy1 = c1->ys - Huy1;
	}

	/* .oO c2 Oo. */
	velocity = sqrt((float)(c2->xs * c2->xs + c2->ys * c2->ys));

	// here's where the magic happens... i wish i understood my linear algebra better.

	if (velocity <= 0.000001) {
		X1 = Y1 = 0.0f;
		X2 = Y2 = 0.0f;
		Hux2 = Huy2 = Vux2 = Vuy2 = 0.0f; 
	}
	else {
		X1 = c2->xs/velocity; 
		Y1 = c2->ys/velocity;

		X2 = c1->x - c2->x;
		Y2 = c1->y - c2->y;

		dist = sqrt((float)(X2*X2 + Y2*Y2));  // should not be zero
		X2 /= dist;                           // since they don't overlap
		Y2 /= dist;
		
		cosine = X1*X2 + Y1*Y2;

		Hux2 = cosine*velocity*X2; 
		Huy2 = cosine*velocity*Y2;
		Vux2 = c2->xs - Hux2; 
		Vuy2 = c2->ys - Huy2;
	}

	// swap the horizontals
	Hvx1 = Hux2; 
	Hvy1 = Huy2;
	Hvx2 = Hux1; 
	Hvy2 = Huy1;
	
	// Verticals don't change

	Vvx1 = Vux1; 
	Vvy1 = Vuy1;
	Vvx2 = Vux2; 
	Vvy2 = Vuy2;

	// compute the new directions by adding the vectors
	c1->xs = Hvx1 + Vvx1;
	c1->ys = Hvy1 + Vvy1;
	//textprintf(screen, font, 50, 50, makecol(255, 0, 0), "x:%f y:%f", c1->x, c1->y);
	//textprintf(screen, font, 50, 60, makecol(255, 0, 0), "xs:%f ys:%f", c1->xs, c1->ys);
	
	
	c2->xs = Hvx2 + Vvx2;
	c2->ys = Hvy2 + Vvy2;
	//textprintf(screen, font, 50, 80, makecol(255, 0, 0), "x:%f y:%f", c2->x, c2->y);
	//textprintf(screen, font, 50, 90, makecol(255, 0, 0), "xs:%f ys:%f", c2->xs, c2->ys);

	//readkey();

	if ( (c1->xs == c2->xs) && (c1->ys == c2->ys) ) {
		//textprintf(screen, font, c1->x, c1->y, makecol(255, 255, 0), "x:%f y:%f", c1->x, c1->y);
		//textprintf(screen, font, c2->x, c2->y, makecol(255, 255, 0), "x:%f y:%f", c2->x, c2->y);
		//readkey();
	}

	// calculate the outgoing energy... note that this isn't used yet.
	//En2 = (c1->xs*c1->xs + c2->ys*c1->ys) + (c2->xs*c2->xs + c2->ys*c2->ys);
}

/* 
 * function: coll_checkNewCircles
 * purpose:  Check newly generated circles to see if they are touching
 * returns:  1 if touching
 *           0 if not touching
 */

//int coll_checkNewCircles(CIRCLE_T *c1, CIRCLE_T *c2) {
//
//	int watch_x = 0;		/* dirty x flag */
//	int watch_y = 0;		/* dirty y flag */
//
//	/* check if c1->x will be within c2's x after next update */
//	/* c1.rhs > c2.lhs && c1.rhs < c2.rhs */
//	if ( ( (c1->x + c1->r) >= (c2->x - c2->r) ) && 
//		 ( (c1->x + c1->r) <= (c2->x + c2->r) ) )
//		{ watch_x = 1; }							/* watch_x! */
//	/* c1.lhs > c2.lhs && c1.lhs > c2.rhs */
//	else if ( ( (c1->x - c1->r) >= (c2->x - c2->r) ) && 
//		      ( (c1->x - c1->r) <= (c2->x + c2->r) ) )
//		{ watch_x = 1; }							/* watch_x! */
//
//	/* check if c1->y will be within c2's y after next update */				
//	/* c1.top > c2.bot && c1.top < c2.top */
//	if ( ( (c1->y - c2->r) <= (c2->y + c2->r) ) && 
//		 ( (c1->y - c1->r) >= (c2->y - c2->r) ) )
//		{ watch_y = 1; }							/* watch_y! */
//	/* c1.bot > c2.bot && c1.bot < c2.top */
//	else if ( ( (c1->y + c1->r) <= (c2->y + c2->r) ) && 
//		      ( (c1->y + c1->r) >= (c2->y - c2->r) ) )
//		{ watch_y = 1; }							/* watch_y! */
//
//	/* if the x and the y are both within the circle's range... */
//	if (watch_x==1 && watch_y==1)
//		{
//			//textprintf(screen, font, c1->x, c1->y, makecol(255, 0, 0), "x:%f y:%f r:%dBAD!", c1->x, c1->y, c1->r);
//			//readkey();
//			return 1; }	/* a collision has occured */
//	else
//		{ return 0; }	/* there is no collision */
//}