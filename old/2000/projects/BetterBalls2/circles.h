
/*
 * circles.h
 * Headers for standard reusable functions to move a circle
 * (from the vivace allegro tutorial)
 */

typedef struct circle_t CIRCLE_T;

struct circle_t {
   float x,y,r;         /* x, y, radius */
   float col;           /* colour */
   float xs,ys;         /* x speed, y speed */
   float dx,dy;         /* drawn x, drawn y */
   };

CIRCLE_T *circle_init(float new_x, float new_y, float new_radius,
                      float new_col, float new_xs, float new_ys);
void circle_destroy (CIRCLE_T *circle);
void circle_draw (CIRCLE_T *circle, BITMAP *bmp);
void circle_update (CIRCLE_T *circle);
void circle_erase (CIRCLE_T *circle, BITMAP *bmp);
