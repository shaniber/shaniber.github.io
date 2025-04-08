
/* 
 * collisions.h - headers for standard functions to detect collisions 
 *                between circles 
 * Author: ssd
 * Modification History
 * By:		Date:		Action:
 * ---		-----		-------
 * ssd		14jul00		created this file.
 * ssd		30jul00		added custom modifications and much nicer physics.
 */

/* function prototypes */
int coll_checkCircle(CIRCLE_T *c1, CIRCLE_T *c2);
void coll_checkWalls(CIRCLE_T *circle);
void coll_bounceCircles(CIRCLE_T *c1, CIRCLE_T *c2);