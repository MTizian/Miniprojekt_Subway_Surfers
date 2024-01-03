#ifndef GAMEFUNKTIONS_H
#define GAMEFUNKTIONS_H

typedef struct {
	int x, 
		y;
	color farbe;
	char symbol;
}position;

#define SCREEN_HEIGHT		25
#define SCREEN_WIDTH		55


void	printPixel(color farbe);
void	setGameField(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]);
void	setPixel(char field[200][55], int x, int y, int r, int g, int b);
void	printMap(position coloredPixels[][SCREEN_WIDTH]);
void	setTrain(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position train, int len_x, int len_y, color farbe);
void	setPlayer(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], position player, color farbe);
int		checkCollision(position train_1, position train_2, position train_3, position player);
int		randomNumber(int max, int min);
void	printScoreboard(int score, int coins);
void	setStartMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH]);
int		mainGame();
void	loadingAnimation();
void	setEndMenu(position feld[SCREEN_HEIGHT][SCREEN_WIDTH], int score);

#endif
