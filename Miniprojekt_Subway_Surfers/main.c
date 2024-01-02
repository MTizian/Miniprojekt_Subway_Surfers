//////////////////////////////////////////
//										//
//		Subway Surfers Miniprojekt		//
//										//
//		Nico H�fle			311063		//
//		Tizian M�ller		310315		//
//										// 
//		Das Programm ist Open Source	//
//										//
//////////////////////////////////////////

#include "ColorPalette.h"
#include "gameFunctions.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SCREEN_HEIGHT		25
#define SCREEN_WIDTH		55
#define STEP_SIZE			18
#define TRAIN_LENGTH_X		13
#define TRAIN_LENGTH_Y		10
#define LINE1				0
#define LINE2				18
#define LINE3				36
#define LINE4				54

int main() {
	setbuf(stdout, NULL);
	char user_input = ' ';
	bool exit = FALSE;
	int score = 0;

	position menu_map[SCREEN_HEIGHT][SCREEN_WIDTH];

	setStartMenu(menu_map);
	printMap(menu_map);

	do {
		//Spieler Eingabe
		if (_kbhit()) {
			user_input = _getch();
			switch (user_input) {
			case 'n':
				printf("Danke fuers spielen\n");
				exit = TRUE;
				fflush(stdin);
				break;
			case 'y':
				loadingAnimation();
				score = mainGame();
				setEndMenu(menu_map, score);
				printMap(menu_map);
				exit = FALSE;
				fflush(stdin);
				break;
			default:
				break;
			}
		}
	} while (exit != TRUE);


	
	
	 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//	Algorithmus f�r die Platzierung der Z�ge fehlt noch
	//	
	//	Flackern im terminal wegbekommen
	// 
	// collision text weg
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}