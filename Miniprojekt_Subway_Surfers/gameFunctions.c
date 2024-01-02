#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "ColorPalette.h"
#include "gameFunctions.h"


#define SCREEN_HEIGHT		25
#define SCREEN_WIDTH		55
#define STEP_SIZE			18
#define TRAIN_LENGTH_X		13
#define TRAIN_LENGTH_Y		10
#define LINE1				0
#define LINE2				18
#define LINE3				36
#define LINE4				54
#define PFEIL_TASTE_LINKS	75
#define	PFEIL_TASTE_RECHTS	77

void printPixel(color farbe) {
	//Farbige Ausgabe
	printf("\x1b[48;2;%d;%d;%dm\x1b[30m%c\x1b[0m", farbe.r, farbe.g, farbe.b, ' ');
	printf("\x1b[0m");  // Setzt die Farben zur�ck
}

void setPixel(char field[200][55], int x, int y, int r, int g, int b) {
	field[y][x] = "\x1b[48;2;%d;%d;%dm";
}

void setGameField(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	//Erstellung vom Spielfeld mit schwarzer fl�che
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			feld[i][j].farbe = dark_green;
			feld[i][j].symbol = ' ';
		}
	}

	//Spielfeld Linien setzen

	//1.Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][LINE1].farbe = white;
	}

	//2.Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][LINE2].farbe = white;
	}

	//3.Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][LINE3].farbe = white;
	}

	//4. Linie
	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		feld[i][LINE4].farbe = white;
	}
}

void printMap(position feld[][SCREEN_WIDTH]) {
	for (int i = 0; i < SCREEN_HEIGHT; ++i) {
		for (int j = 0; j < SCREEN_WIDTH; ++j) {
			printf("\x1b[%d;%dH\x1b[48;2;%d;%d;%dm\x1b[30m%c\x1b[0m", feld[i][j].y, feld[i][j].x,
				feld[i][j].farbe.r, feld[i][j].farbe.g, feld[i][j].farbe.b, feld[i][j].symbol);

			
		}
		printf("\r");
	}
	printf("\x1b[0m");  // Setzt die Farben zur�ck
}

void setTrain(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position train, int len_x, int len_y, color farbe) {
	// �berpr�fen Sie, ob der Zug im sichtbaren Bereich des Spielfelds liegt
	if (train.y + len_y >= 0 && train.y < SCREEN_HEIGHT) {
		// Zug nur setzen, wenn er sichtbar ist
		for (int i = 0; i < len_y; i++) {
			for (int j = 0; j < len_x; j++) {
				// �berpr�fung ob die Position im sichtbaren Bereich liegt
				if (train.y + 1 + i >= 0 && train.y + 1 + i < SCREEN_HEIGHT && train.x + j >= 0 && train.x + j < SCREEN_WIDTH) {
					feld[train.y + 1 + i][train.x + j].farbe = farbe;
				}
			}
		}
	}
}

void setPlayer(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position player, color farbe) {
	feld[player.y][player.x].farbe = farbe;

	//Gr��erer Spieler (eig. �nn�tig)
	feld[player.y - 1][player.x + 1].farbe = farbe;
	feld[player.y-1][player.x - 1].farbe = farbe;
	feld[player.y-1][player.x].farbe = farbe;
	
}

int checkCollision(position train_1, position train_2, position train_3, position player) {
	int collisionMap[200][55];


	//Initalisierung Collision Map
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			collisionMap[i][j] = 0;
		}
	}

	//Setze Z�ge auf eins
	for (int i = 0; i < TRAIN_LENGTH_Y; i++)
	{
		for (int j = 0; j < TRAIN_LENGTH_X; j++)
		{
			collisionMap[train_1.y + i][train_1.x + j] = 1;
			collisionMap[train_2.y + i][train_2.x + j] = 1;
			collisionMap[train_3.y + i][train_3.x + j] = 1;
		}
	}

	//Wenn Kollision gebe eins zur�ck
	if (collisionMap[player.y][player.x] == 1) {
		return 1; 
	}
}

int randomNumber(int max, int min) {
	//Initialisierung ZUfallsgenerator
	srand(time(NULL));

	return rand() % max + min;
}

void printScoreboard(int score, int coins) {

	printf(" Score:    %2d | ", score);
	printf("Coins:    %2d\n", coins);
}

void setStartMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	position block_1, block_2, header_block;
	char startText[] = "Start [y]";
	char quitText[] = "Quit [n]";
	char headerText[] = "Subway Surfers";
	
	block_1.x = 7;
	block_2.x = 33;
	block_1.y = block_2.y = 17;
	block_1.farbe = block_2.farbe = header_block.farbe = grey;

	header_block.x = 7; header_block.y = 4;


	//Erstellung vom Spielfeld mit Wei�er fl�che
	for (int i = 0; i < SCREEN_HEIGHT; i++){
		for (int j = 0; j < SCREEN_WIDTH; j++){
			feld[i][j].farbe = white;
			feld[i][j].symbol = ' ';
		}
	}

	//Header Block �berschrift

	//Text setzen
	for (int n = 0; n < strlen(headerText); n++) {
		feld[header_block.y + 1][header_block.x + n + 1].symbol = headerText[n];
	}
	//Fareb setzen
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y + 1][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < strlen(headerText) + 2; j++){
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
	int coins = 0;
	char user_input = ' ';
	//Startposition des Spielers
	position player;
	player.x = 27,
	player.y = 3;
	position train_1;
	train_1.x = 3;
	position train_2;
	train_2.x = 21;
	position train_3;
	train_3.x = 39;
	position game_map[SCREEN_HEIGHT][SCREEN_WIDTH];
	int randNumber,
		randMax = 100,
		randMin = 25;
	//F�r die zunehmende Geschwindigkeit
	int duration = 400;


	train_1.y = randomNumber(randMax, randMin);
	train_2.y = randomNumber(randMax, randMin)+25;
	train_3.y = randomNumber(randMax, randMin) + 50;


	//Spielschleife
	while (user_input != '\x1B') {
		system("cls");

		printScoreboard(score, coins);

		setGameField(game_map);


		//Z�ge PLatzieren in der game map
		setTrain(game_map, train_1, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, cyan);
		setTrain(game_map, train_2, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, cyan);
		setTrain(game_map, train_3, TRAIN_LENGTH_X, TRAIN_LENGTH_Y, black);

		//Spieler Platzieren
		setPlayer(game_map, player, red);


		if (checkCollision(train_1, train_2, train_3, player) == 1) {
			printf("Collision detected! Game Over\n");
			Sleep(1000);
			break;
		}

		//Spieler Eingabe
		if (_kbhit()) {
			user_input = _getch();

			switch (user_input) {
			case 'a': case PFEIL_TASTE_LINKS:
				if (player.x != 9) {
					player.x = (player.x - STEP_SIZE + SCREEN_WIDTH) % SCREEN_WIDTH;
				}
				break;
			case 'd': case PFEIL_TASTE_RECHTS:
				if (player.x != 45) {
					player.x = (player.x + STEP_SIZE) % SCREEN_WIDTH;
				}
				break;
			default:
				break;
			}
		}

		score++;

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
	return score;
}


void loadingAnimation() {
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
}

void setEndMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], int score) {
	position block_1, block_2, header_block;
	block_1.x = 7;
	block_2.x = 33;
	block_1.y = block_2.y = 17;
	block_1.farbe = block_2.farbe = header_block.farbe  = grey;

	header_block.x = 7; header_block.y = 4;



	const char	againText[] = "Again [y]";
	const char	quitText[] = "Quit [n]";
	const char	headerText[] = "Subway Surfers"; 
	char		scoreText[30] = "Your Score ";
	char		scoreitoc[20]; // Score Buffer


	sprintf_s(scoreText, sizeof(scoreText), "Your Score: %d", score);
	strcat_s(scoreText, sizeof(scoreText), " ");



	system("cls");

	//Erstellung vom Spielfeld mit Wei�er fl�che
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			feld[i][j].farbe = white;
			feld[i][j].symbol = ' ';
		}
	}




	//Header Block �berschrift

	//Text setzen
	for (int n = 0; n < strlen(headerText); n++) {
		feld[header_block.y + 1][header_block.x + n + 1].symbol = headerText[n];
	}
	//Score setzen
	for (int n = 0; n < strlen(scoreText); n++) {
		feld[header_block.y + 3][header_block.x + n + 1].symbol = scoreText[n];
	}

	//Fareb setzen
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y + 1][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y + 2][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y + 3][j + header_block.x].farbe = header_block.farbe;
	}
	for (int j = 0; j < strlen(headerText) + 2; j++) {
		feld[header_block.y + 4][j + header_block.x].farbe = header_block.farbe;
	}


	//Block mit Start

	//Text setzen
	for (int n = 0; n < strlen(againText); n++) {
		feld[block_1.y + 1][block_1.x + n + 1].symbol = againText[n];
	}
	//Farbe setzen
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
