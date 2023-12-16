#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#include "ColorPalette.h"
#include "gameFunctions.h"



#define SCREEN_HEIGHT		25
#define SCREEN_WIDTH		55
#define STEP_SIZE			18
#define TRAIN_LENGTH_X		15
#define TRAIN_LENGTH_Y		10
#define LINE1				0
#define LINE2				18
#define LINE3				36
#define LINE4				54


void printPixel(int r, int g, int b, int size) {
	//Farbige Ausgabe
	printf("\x1b[48;2;%d;%d;%dm", r, g, b);
	for (int i = 0; i < size; ++i) {
		printf(" ");
	}
	printf("\x1b[0m");  // Setzt die Farben zurück
}

void setPixel(char field[200][55], int x, int y, int r, int g, int b) {
	field[y][x] = "\x1b[48;2;%d;%d;%dm";
}

void setGameField(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]) {
	//Erstellung vom Spielfeld mit schwarzer fläche
	for (int i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			feld[i][j].farbe = dark_green;
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
			printf("\x1b[%d;%dH\x1b[48;2;%d;%d;%dm ", feld[i][j].y, feld[i][j].x,
				feld[i][j].farbe.r, feld[i][j].farbe.g, feld[i][j].farbe.b);
		}
		printf("\n");
	}
	printf("\x1b[0m");  // Setzt die Farben zurück
}


void setTrain(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position train, int len_x, int len_y, color farbe) {
	//Zug Platzieren
	for (int i = 0; i < len_y; i++) {
		for (int j = 0; j < len_x; j++) {
			feld[train.y + 1 + i][train.x + j].farbe = farbe;
		}
	}

}

void setPlayer(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position player, color farbe) {
	feld[player.y][player.x].farbe = farbe;

	//Größerer Spieler (eig. ünnötig)
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

	//Setze Züge auf eins
	for (int i = 0; i < TRAIN_LENGTH_Y; i++)
	{
		for (int j = 0; j < TRAIN_LENGTH_X; j++)
		{
			collisionMap[train_1.y + i][train_1.x + j] = 1;
			collisionMap[train_2.y + i][train_2.x + j] = 1;
			collisionMap[train_3.y + i][train_3.x + j] = 1;
		}
	}

	//Wenn Kollision gebe eins zurück
	if (collisionMap[player.y][player.x] == 1) {
		return 1; 
	}
}


int randomNumber(int max, int min) {
	//Initialisierung ZUfallsgenerator
	srand(time(NULL));

	return rand() % max + min;
}