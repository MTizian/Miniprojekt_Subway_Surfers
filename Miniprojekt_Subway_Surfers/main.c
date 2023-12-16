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


	//Startposition des Spielers
	position player;
	player.x = 27,
	player.y = 3;


	position train_1;
	train_1.x = 3;
	train_1.y = 15;
	position train_2;
	train_2.x = 21;
	train_2.y = 15;
	position train_3;
	train_3.x = 39;
	train_3.y = 15;


	//dekleration vom Spielfeld
	position game_map[SCREEN_HEIGHT][SCREEN_WIDTH];



	int duration = 400;

	position train_map[200][SCREEN_WIDTH];

	int randNumber, 
		randMax = 200, 
		randMin = 25;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//	Startmenü Fehlt
	//	Algorithmus für die Platzierung der Züge fehlt noch
	//	Highscore Fehlt
	//	Endmenü Fehlt
	// 
	//	Flackern im terminal wegbekommen
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////














	//Gedanke für zufallszüge
		//Vorgaben:	-max. 2 züge auf drei bahnen
		//
		// Erst Züge in Train_map setzen dann train_map auf game_map übertragen
		// 
		// Zufällige höhe für die platzierung von train auf y-achse
		// 
		//  evtl. array von zügen erstellen ... evtl. damit auch highscore berechnung möglich damit möglich
		//


	train_1.y = randomNumber(randMax, randMin);
	train_2.y = randomNumber(randMax, randMin + TRAIN_LENGTH_Y);
	train_3.y = randomNumber(randMax, randMin);





	//Spielschleife
	while (user_input != '\x1B') {
		system("cls");

		setGameField(game_map);










		

		


		//setTrain(train_map, train_1, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, red);








		//Züge PLatzieren in der game map
		setTrain(game_map, train_1, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, black);
		setTrain(game_map, train_2, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, black);
		setTrain(game_map, train_3, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, black);


		//Spieler Platzieren
		setPlayer(game_map, player, red);


		//Auf Kollision überprüfen
		if (checkCollision(train_1, train_2, train_3, player) == 1) {
			printf("Collision detected! Game Over\n");
			break;
		}


		//Spieler Eingabe
		if (_kbhit()) {
			user_input = _getch();

			switch (user_input) {
			case 'a':
				if (player.x != 9) {
					player.x = (player.x - STEP_SIZE + SCREEN_WIDTH) % SCREEN_WIDTH;
				}
				break;
			case 'd':
				if (player.x != 45) {
					player.x = (player.x + STEP_SIZE) % SCREEN_WIDTH;
				}
				break;
			default:
				break;
			}
		}


		//Ausgabe des Feldes
		printMap(game_map);



		//Bewege Zug nach oben
		train_1.y--;
		train_2.y--;
		train_3.y--;




		//Warte in mSd
		Sleep(duration);

		if (duration != 10) {
			//Wiederholungen der schleife wird bei jeder weiderholung um eine mS schneller bis sie bei 10mS ist
			duration--;
		}
	}

	return 0;
}