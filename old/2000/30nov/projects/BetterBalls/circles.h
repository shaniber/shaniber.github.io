
/*
 * circles.h
 * Headers for standard reusable functions to move a circle
 * (from the vivace allegro tutorial)
 */

typedef struct circle_t CIRCLE_T;

struct circle_t {
   int x,y,r;         /* x, y, radius */
   int col;           /* colour */
   int xs,ys;         /* x speed, y speed */
   int dx,dy;         /* drawn x, drawn y */
   };

CIRCLE_T *circle_init(int new_x, int new_y, int new_radius,
                      int new_col, int new_xs, int new_ys);
void circle_destroy (CIRCLE_T *circle);
void circle_draw (CIRCLE_T *circle, BITMAP *bmp);
void circle_update (CIRCLE_T *circle);
void circle_erase (CIRCLE_T *circle, BITMAP *bmp);
