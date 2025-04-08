
/*
 * ballzone0.h - headers for bz0.c
 *
 * Author: ssd
 * Modification History
 * By:		Date:		Action:
 * ---		-----		-------
 * ssd		11sep00		created this file.
 */

/* external variable declarations */
extern int end_game;
extern BITMAP *offScreen;

/* function prototypes */
int main(int argc, char *argv[]);
void init(void);
void input(void);
void process(void);
void output(void);
void cleanup(void);
void show_double_buffer(void);
