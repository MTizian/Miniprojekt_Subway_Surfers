//////////////////////////////////////////
//										//
//		Subway Surfers Miniprojekt		//
//										//
//		Nico Häfele			311063		//
//		Tizian Müller		310315		//
//										// 
//		Das Programm ist Open Source	//
//										//
//////////////////////////////////////////

#include "constants.h"
#include "ColorPalette.h"
#include "gameFunctions.h"

#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdbool.h>


int main() {
	char user_input = ' ';
	bool exit = FALSE;
	int score = 0;

	position menu_map[SCREEN_HEIGHT][SCREEN_WIDTH];

	setStartMenu(menu_map);
	printMap(menu_map);

	do {
		//Spieler Eingabe
		if (_kbhit()) { //Überprüft auf Tasten Eingabe 
			user_input = _getch();
			switch (user_input) {
				//wenn n oder ESC gedrückt
				case 'n': case ESC_KEY:
					printf("Danke fuers spielen\n");
					exit = TRUE;
					break;
				case 'y':
					loadingAnimation();
					score = mainGame();
					setEndMenu(menu_map, &score);
					printMap(menu_map);
					exit = FALSE;
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