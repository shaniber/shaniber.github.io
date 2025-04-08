
/* 
 * bb.h
 * headers for bb.c
 */

/* external constant declarations */
#define MAX_CIRCLES		25

/* external variable declarations */

extern int end_game;
extern BITMAP *offScreen;

/* funtion prototypes */
int main(int argc, char *argv[]);
void init(void);
void input(void);
void process(void);
void output(void);
void cleanup(void);
void show_double_buffer(void);

