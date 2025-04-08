
/* 
 * collisions.h
 * headers for standard functions to detect collisions between circles 
 * author:  ssd
 */

/* function prototypes */
int coll_checkCircle(CIRCLE_T *c1, CIRCLE_T *c2);
void coll_checkWalls(CIRCLE_T *circle);
void coll_bounceCircles(CIRCLE_T *c1, CIRCLE_T *c2);