#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "ColorPalette.h"
#include "constants.h"
#include "gameFunctions.h"


void printPixel(color farbe) {
	//Farbige Ausgabe mit Ansi Escape Code
	printf("\x1b[48;2;%d;%d;%dm\x1b[30m%c\x1b[0m", farbe.r, farbe.g, farbe.b, ' ');
	printf("\x1b[0m");  // Setzt die Farben zurück
}

void setGameField(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	//Erstellung vom Spielfeld mit schwarzer fläche
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			feld[i][j].farbe = GAME_MAP_COLOR; //Spielfeldfarbe
			feld[i][j].symbol = ' ';
		}
	}

	//Spielfeld Linien setzen

	//1.Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][line_1].farbe = LINE_COLOR;
	}

	//2.Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][line_2].farbe = LINE_COLOR;
	}

	//3.Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][line_3].farbe = LINE_COLOR;
	}

	//4. Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][line_4].farbe = LINE_COLOR;
	}
}

void printMap(position feld[5 * SCREEN_HEIGHT][SCREEN_WIDTH]) {
	for (int i = 0; i < SCREEN_HEIGHT; ++i) {
		for (int j = 0; j < SCREEN_WIDTH; ++j) {
			//Attribute mithilfe von Ansi Escape Code
			printf("\x1b[%d;%dH\x1b[48;2;%d;%d;%dm\x1b[30m%c\x1b[0m", 
				feld[i][j].y, feld[i][j].x,
				feld[i][j].farbe.r, feld[i][j].farbe.g, feld[i][j].farbe.b, 
				feld[i][j].symbol);
		}
		printf("\n");
	}
	printf("\x1b[0m");  // Setzt die Farben zurück
}

void setTrain(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position *train) {
	// Überprüfen Sie, ob der Zug im sichtbaren Bereich des Spielfelds liegt
	if (train->y + train_len_y >= 0 && train->y < SCREEN_HEIGHT) {
		// Zug nur setzen, wenn er sichtbar ist
		for (int i = 0; i < train_len_y; i++) {
			for (int j = 0; j < train_len_x; j++) {
				// Überprüfung ob die Position im sichtbaren Bereich liegt
				if (train->y + 1 + i >= 0 && train->y + 1 + i < SCREEN_HEIGHT && train->x + j >= 0 && train->x + j < SCREEN_WIDTH) {
					feld[train->y + 1 + i][train->x + j].farbe = TRAIN_COLOR;
				}
			}
		}
	}
}

void setPlayer(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position *player) {
	feld[player->y][player->x].farbe = PLAYER_COLOR;

	//Größerer Spieler (eig. ünnötig)
	feld[player->y - 1][player->x + 1].farbe = PLAYER_COLOR;
	feld[player->y - 1][player->x - 1].farbe = PLAYER_COLOR;
	feld[player->y - 1][player->x].farbe = PLAYER_COLOR;
}

int checkCollision(position *train_1, position *train_2, position *train_3, position *player) {
	int collisionMap[5 * SCREEN_HEIGHT][SCREEN_WIDTH]; //Verbracuht viel PLatz

	//Initalisierung der Collision Map auf 0
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			collisionMap[i][j] = 0;
		}
	}

	//Setze positionen der Züge auf eins
	for (int i = 0; i < train_len_y; i++){
		for (int j = 0; j < train_len_x; j++){
 			collisionMap[train_1->y + i][train_1->x + j] = 1;
			collisionMap[train_2->y + i][train_2->x + j] = 1;
			collisionMap[train_3->y + i][train_3->x + j] = 1;
		}
	}

	//Wenn Kollision gebe eins zurück
	if (collisionMap[player->y][player->x] == 1) {
		return 1; 
	}
	return 0;
}


void initializeRandom() {
	srand(time(NULL));
}

int randomNumber() {
	int randMax = 100, randMin = 25;
	return rand() % (randMax - randMin + 1) + randMin;
}

void printScoreboard(int *score) {
	printf(" Score:    %2d", *score);
	printf("\n");
}

void setStartMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	position block_1, block_2, header_block;
	char startText[] = "Start [y]";
	char quitText[] = "Quit [n]";
	char headerText[] = "Subway Surfers";
	
	block_1.x = SCREEN_WIDTH / 4;	//Position 1. Block
	block_2.x = 3 * SCREEN_WIDTH / 4 - (strlen(quitText) + 2); //Position vom 2.ten Block
	block_1.y = block_2.y = 17;
	block_1.farbe = block_2.farbe = header_block.farbe = SECONDARY_MENU_COLOR;

	header_block.x = SCREEN_WIDTH / 4; header_block.y = 4;


	//Erstellung vom Spielfeld mit Weißer fläche
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			feld[i][j].farbe = PRIMARY_MENU_COLOR;
			feld[i][j].symbol = ' ';
		}
	}

	//Header Block Überschrift

	//Text setzen
	for (int n = 0; n < strlen(headerText); n++) {
		feld[header_block.y + 1][header_block.x + n + 1].symbol = headerText[n];
	}
	//Farbe setzen
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y + 1][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < SCREEN_WIDTH / 2; j++){
		feld[header_block.y + 2][j + header_block.x].farbe = header_block.farbe;
	}


	//Block mit Start

	//Text setzen
	for (int n = 0; n < strlen(startText); n++) {
		feld[block_1.y + 1][block_1.x + n + 1].symbol = startText[n];
	}
	//Farbe setzen
	for (int j = 0; j < strlen(startText) + 2; j++) {
		feld[block_1.y][j + block_1.x].farbe = block_1.farbe;
	}
	for (int j = 0; j < strlen(startText) + 2; j++) {
		feld[block_1.y + 1][j + block_1.x].farbe = block_1.farbe;
	}
	for (int j = 0; j < strlen(startText) + 2; j++) {
		feld[block_1.y + 2][j + block_1.x].farbe = block_1.farbe;
	}


	//Block mit quit

	//Text setzen
	for (int n = 0; n < strlen(quitText); n++) {
		feld[block_2.y + 1][block_2.x + n + 1].symbol = quitText[n];
	}
	//Fareb setzen
	for (int j = 0; j < strlen(quitText) + 2; j++) {
		feld[block_2.y][j + block_2.x].farbe = block_2.farbe;
	}
	for (int j = 0; j < strlen(quitText) + 2; j++) {
		feld[block_2.y + 1][j + block_2.x].farbe = block_2.farbe;
	}
	for (int j = 0; j < strlen(quitText) + 2; j++) {
		feld[block_2.y + 2][j + block_2.x].farbe = block_2.farbe;
	}
}

int mainGame() {
	int score = 0;
	char user_input = ' ';
	int iterations = 0;
	//Startposition des Spielers
	position player;
	player.x = SCREEN_WIDTH / 2,
	player.y = 3;

	position train_1;
	train_1.x = 3;
	position train_2;
	train_2.x = SCREEN_WIDTH / 3 + 3; //21
	position train_3;
	train_3.x = 2 * (SCREEN_WIDTH / 3) + 3; // 39
	position game_map[SCREEN_HEIGHT][SCREEN_WIDTH];
	
	//Wartezeit bis zur nächsten spielschleife
	int duration = 200;

	initializeRandom();

	//////////////// Vorübergehend
	train_1.y = randomNumber();
	train_2.y = randomNumber();
	train_3.y = randomNumber();
	/////////////

	//Spielschleife
	while (user_input != ESC_KEY) {
		system("cls"); //Bildschirm leeren
		printScoreboard(&score);//Score ausgeben
		setGameField(game_map);//farben setzen


		//Züge PLatzieren auf der game map
		//       Zielort   was		Länge x			Länge y			Farbe
		setTrain(game_map, &train_1);
		setTrain(game_map, &train_2);
		setTrain(game_map, &train_3);

		//Spieler Platzieren
		//		  Zielort	was		Farbe
		setPlayer(game_map, &player);


		//Falls Kollision entdeckt gebe game over aus und warte 1s
		if (checkCollision(&train_1, &train_2, &train_3, &player) == 1) {
			printf("Collision detected! Game Over\n");
			Sleep(1000);
			break;
		}



		//Spieler Eingabe

		if (_kbhit()) { //Falls tastenanschlag
			//Übergebe char an user_input
			user_input = _getch();
			switch (user_input) {
			case 'a': case PFEILTASTE_LINKS:
				//falls der Spieler nicht ganz Links gehe nach links
				if (player.x != (SCREEN_WIDTH / 6)) {
					player.x = (player.x - step_size+ SCREEN_WIDTH) % SCREEN_WIDTH;
				}
				break;
			case 'd': case PFEILTASTE_RECHTS:
				//falls der spieler nicht ganz rechts gehe nach rechts
				if (player.x != ((SCREEN_WIDTH / 6) * 5)) {
					player.x = (player.x + step_size) % SCREEN_WIDTH;
				}
				break;
			default:
				break;
			}
		}

		
		//Iterationen Counter
		iterations++;
		if (iterations == 10) {
			//Für 10 Iterationen erhöht sich der score
			score++;
			//Setze iterationen zurück
			iterations = 0;
		}

		//Ausgabe des Feldes
		printMap(game_map);


		//Bewege Zuege nach oben
		train_1.y--; train_2.y--; train_3.y--;

		//Warte in mSd
		Sleep(duration);

		//Wiederholungen der schleife wird bei jeder weiderholung um eine mS schneller bis sie bei 10mS ist
		if (duration != 10) {
			duration--;
		}
	}
	return score;
}

void loadingAnimation() {
	system("cls");	//Bildschirm leren
	printf("Loading\n");

	//Loading animation
	printf("|");
	//Schleife für das erstellen von farbigen Pixeln
	for (int i = 0; i < 15; i++) {
		Sleep(50);
		printPixel(LOADING_COLOR);
	}
	printf("|");
	system("cls"); // Bildschirm leeren
}

void setEndMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], int *score) {
	const char	againText[] = "Again [y]";
	const char	quitText[] = "Quit [n]";
	const char	headerText[] = "Subway Surfers";
	char		scoreText[30] = "Your Score ";

	position block_1, block_2, header_block;
	block_1.x = SCREEN_WIDTH / 4;	//Position 1. Block
	block_2.x = 3 * SCREEN_WIDTH / 4 - (strlen(quitText) + 2); //Position vom 2.ten Block
	block_1.y = block_2.y = 17;
	block_1.farbe = block_2.farbe = header_block.farbe = SECONDARY_MENU_COLOR;

	header_block.x = SCREEN_WIDTH / 4; header_block.y = 4;

	

	//Ähnlich wie printf nur das die formatierte zeichenkette nicht ausgegeben wird sondern in einer anderen gespeichert wird
	//Dabei wird der score an den bereits vorhandenen string drangesetzt
	//	     Zielort	 größe des Array	format			  %d
	sprintf_s(scoreText, sizeof(scoreText), "Your Score: %d", *score);
	//anhängen von einer Zeichenkette in dem Fall ein Leerzeichen
	strcat_s(scoreText, sizeof(scoreText), " ");


	system("cls");	//Bildschirmn leeren

	//Erstellung vom Spielfeld mit Weißer fläche
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			feld[i][j].farbe = PRIMARY_MENU_COLOR;
			feld[i][j].symbol = ' ';
		}
	}

	//Header Block 
	//Text setzen
	for (int n = 0; n < strlen(headerText); n++) {
		feld[header_block.y + 1][header_block.x + n + 1].symbol = headerText[n];
	}
	//Score setzen
	for (int n = 0; n < strlen(scoreText); n++) {
		feld[header_block.y + 3][header_block.x + n + 1].symbol = scoreText[n];
	}
	//Farbe setzen	(5 Zeilen)
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y + 1][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y + 2][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y + 3][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < SCREEN_WIDTH / 2; j++) {
		feld[header_block.y + 4][j + header_block.x].farbe = header_block.farbe;
	}


	//Block mit Start

	//Text setzen
	for (int n = 0; n < strlen(againText); n++) {
		feld[block_1.y + 1][block_1.x + n + 1].symbol = againText[n];
	}
	//Farbe setzen	(3 Setzen)
	for (int j = 0; j < strlen(againText) + 2; j++) {
		feld[block_1.y][j + block_1.x].farbe = block_1.farbe;
	}
	for (int j = 0; j < strlen(againText) + 2; j++) {
		feld[block_1.y + 1][j + block_1.x].farbe = block_1.farbe;
	}
	for (int j = 0; j < strlen(againText) + 2; j++) {
		feld[block_1.y + 2][j + block_1.x].farbe = block_1.farbe;
	}


	//Block mit quit

	//Text setzen
	for (int n = 0; n < strlen(quitText); n++) {
		feld[block_2.y + 1][block_2.x + n + 1].symbol = quitText[n];
	}
	//Farbe setzen	(3 Zeilen)
	for (int j = 0; j < strlen(quitText) + 2; j++) {
		feld[block_2.y][j + block_2.x].farbe = block_2.farbe;
	}
	for (int j = 0; j < strlen(quitText) + 2; j++) {
		feld[block_2.y + 1][j + block_2.x].farbe = block_2.farbe;
	}
	for (int j = 0; j < strlen(quitText) + 2; j++) {
		feld[block_2.y + 2][j + block_2.x].farbe = block_2.farbe;	
	}
}