//////////////////////////////////////////
//										//
//		Subway Surfers Miniprojekt		//
//										//
//		Nico Häfle			311063		//
//		Tizian Müller		310315		//
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
	char user_input = ' ';

	position menu_map[SCREEN_HEIGHT][SCREEN_WIDTH];
	
	setStartMenu(menu_map);

	printMap(menu_map);

	do {
		//Spieler Eingabe
		if (_kbhit()) {
			user_input = _getch();

			switch (user_input) {
			case 'q':
				printf("Danke fuers spielen\n");
				break;
				break;
			case 's':
				system("cls");
				printf("Loading\n");

				//Loading animation
				printf("|");
				for (int i = 0; i < 25; i++) {
					Sleep(50);
					printPixel(blue);
				}
				printf("|");
				system("cls");


				mainGame();
				//setEndMenu(menu_map);
				
				break;
			default:
				break;
			}
		}
	} while (user_input != 'q' || user_input != 's');

	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//	
	//	Algorithmus für die Platzierung der Züge fehlt noch
	//	
	//	Endmenü Fehlt
	// 
	//	Flackern im terminal wegbekommen
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////





	return 0;
}