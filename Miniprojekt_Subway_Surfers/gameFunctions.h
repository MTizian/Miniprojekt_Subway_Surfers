#ifndef GAMEFUNKTIONS_H
#define GAMEFUNKTIONS_H

typedef struct {
	int x, 
		y;
	color farbe;
	char symbol;
}position;


void	printPixel(color farbe);
void	setGameField(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]);
void	printMap(position coloredPixels[5 * SCREEN_HEIGHT][SCREEN_WIDTH]);
void	setTrain(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position *train);
void	setPlayer(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position *player);
int		checkCollision(position *train_1, position *train_2, position *train_3, position *player);
int		randomNumber();
void	printScoreboard(int *score);
void	setStartMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]);
int		mainGame();
void	loadingAnimation();
void	setEndMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], int *score);

#endif
