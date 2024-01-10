#ifndef CONSTANTS_H
#define CONSTANTS_H



//Ausgabe gr��en
#define SCREEN_HEIGHT			25	//Gr��e prinzipiell egal
#define SCREEN_WIDTH			55	//muss in 3er schritten vergr��ert werden und f�ngt bei 1 an und nicht bei 0


//DYNAMISCHE GR��EN
extern int step_size;
extern int train_len_x;
extern int train_len_y;
extern int line_1;
extern int line_2;
extern int line_3;
extern int line_4;











//Spezielle Tasten
#define PFEILTASTE_LINKS		75
#define PFEILTASTE_RECHTS		77
#define	ESC_KEY					'\x1B'




//Menu Farben
#define	PRIMARY_MENU_COLOR		gray
#define	SECONDARY_MENU_COLOR	white

//Spielfarben
#define	LOADING_COLOR			green
#define	GAME_MAP_COLOR			dark_green
#define LINE_COLOR				white
#define	PLAYER_COLOR			red
#define	TRAIN_COLOR				dark_gray






#endif
