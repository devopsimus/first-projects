#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <process.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

enum key1 {
	up = 72, down = 80, rigth1 = 77, left1 = 75, ENTER = 13, ESC = 27,
};

const int pacManDefaultVerticalPos = 6;
const int pacManDefaultHorizontalPos = 8;
const int ghostDefaultVerticalPos = 15;
const int ghostDefaultHorizontal = 14;
const int boost1VerticalPos = 1, boost1HorizontalPos = 1;
const int boost2VerticalPos = 1, boost2HorizontalPos = 8;
const int boost3VerticalPos = 1, boost3HorizontalPos = 15;
const int boost4VerticalPos = 8, boost4HorizontalPos = 3;
const int boost5VerticalPos = 8, boost5HorizontalPos = 13;
const int boost6VerticalPos = 15, boost6HorizontalPos = 1;
const int boost7VerticalPos = 15, boost7HorizontalPos = 8;
const int boost8VerticalPos = 15, boost8HorizontalPos = 15;
const char boost = 15, wall = 219, path = 249, packDude = 2, ghost = 1, emptyPath = ' ';
int scoreDisplay = 0;

void Blinking();
void setColorOnGrid(char grabbedChar, int amountAllowed);
void toQuitTheGame(bool &run);
void clearBuffer(char &movingDirection);
void clearScreen();
void Game(bool &reset);
void setcolor(unsigned short color);
void HighScores(int score);
void GameMenu(bool &exitGame);
void Loading();
void lifeDecrementation(int &numberOfLives);
void pacmansLives(int numberOfLives, char packDude);
void gameOverLink();
void ghostDudeChasing(int &ghostPos1, int &ghostPos2, int pacManPos1, int pacManPos2, char grid[17][17], int &pathReplace1, int &pathReplace2);
void movePacMan(int &pacManVerticalPos, int &pacManHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn, bool &run);
void grabUserInputForPac(char &userInput);
void pacManSwap(int &pacManVerticalPos, int &pacManHorizontalPos, int moveVerticalPos, int moveHorizontalPos, char grid[17][17], char userInput, int &score, int &m, bool &boostOn);
void scores(int moveVerticalPos, int moveHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn);
void pacManChangePosValue(int &pacManVerticalPos, int &pacManHorizontalPos, char userInput);
void pacManAndGhostContact(int &pacManVerticalPos, int &pacManHorizontalPos, int &ghostVerticalPos, int &ghostHorizontalPos, int &lives, int pathReplace1, int pathReplace2, char grid[17][17]);
void resetValues(int &pacManVerticalPos, int &pacManHorizontalPos, int &ghostVerticalPos, int &ghostHorizontalPos);
bool validateGhostMove(char test);
bool validatePacManMove(char test);
void replaceCharsAfterSwap(int pathReplace1, int pathReplace2, int pacManPos1, int pacManPos2, int ghostPos1, int ghostPos2, char grid[17][17]);
void shortCutAcrossGrid(int &verticalPos, int &horizontalPos, char grid[17][17]);
void ghostRetreat(int &ghostPos1, int &ghostPos2, char grid[17][17], int &ghostTravelPathY, int &ghostTravelPathX, char ghost, int pathReplace1, int pathReplace2, bool &ghostPath1, bool &ghostPath2, bool &ghostPath3, bool &ghostPath4, bool &ghostPath5, bool &ghostPath6, bool &ghostPath7, bool &ghostPath8, char boostOn);


int main() {
	Blinking();
	Loading();
	ifstream fin(R"(C:\Users\PacmanTotalScores.txt)");
	ofstream sout(R"(C:\Users\PacmanHighScores.txt)");
	bool exitGame = false;
	do {
		GameMenu(exitGame);
	} while (exitGame != true);
	return 0;
}



void Game(bool &reset) {
	int h = 0;
	int x = 0;
	char ghost = 1;
	bool run = true;
	char logo = ' ';
	int pathReplace1 = 0;
	int pathReplace2 = 0;
	int ghostPos1 = ghostDefaultVerticalPos;
	int ghostPos2 = ghostDefaultHorizontal;
	int ghost2Pos1 = 1;
	int ghost2Pos2 = 11;
	int ghostIncrementForSpeed = 0;
	int ghostSpeedLimit = 2;
	int m = 0;
	int pelletCounter = 0;
	int pacManVerticalPos = pacManDefaultVerticalPos;
	int pacManHorizontalPos = pacManDefaultHorizontalPos;
	int score = 0;
	char characterForColorCheck = ' ';
	char temp;
	char tempTwo;
	char posForBoost;
	char whereToMove = ' ';
	bool boostOn = false;

	vector<char> Vector;

	char crystal = 3;
	int CountDownTimeForGhostKilling = 18;
	const int Time = 20;
	int clockTicker = Time;
	int lives = 3;
	int loopRepeats = 0;
	int clik = 0;
	char wallLeftTrasport = 29;
	char wallRightTrasport = 29;
	bool coolColors = false;
	int bonusY = 11;
	int bonusX = 8;
	int bonusTravelPathY = 1;
	int bonusTravelPathX = 15;
	int ghostTravelPathY = 2;
	int ghostTravelPathX = 1;
	bool followPath1 = true;
	bool followPath2 = true;
	bool followPath3 = true;
	bool followPath4 = true;
	bool followPath5 = true;
	bool followPath6 = true;
	bool followPath7 = true;
	bool followPath8 = true;
	bool ghostPath1 = true;
	bool ghostPath2 = true;
	bool ghostPath3 = true;
	bool ghostPath4 = true;
	bool ghostPath5 = true;
	bool ghostPath6 = true;
	bool ghostPath7 = true;
	bool ghostPath8 = true;
	char bonus = 36;
	int amountAllowed = 0;

	char grid[17][17] = {
		{ wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall },
		{ wall,wall,path,path,path,path,path,path,wall,path,path,path,path,path,path,wall,wall },
		{ wall,path,wall,wall,path,wall,wall,wall,path,wall,wall,wall,path,wall,wall,path,wall },
		{ wall,path,path,path,path,path,path,wall,path,path,path,path,path,path,wall,path,wall },
		{ wallLeftTrasport,path,wall,path,wall,wall,path,path,path,wall,crystal,wall,wall,path,path,path,wallRightTrasport },
		{ wall,path,path,path,wall,wall,path,wall,path,wall,wall,wall,wall,path,wall,path,wall },
		{ wall,path,wall,path,path,path,path,path,path,path,path,path,path,path,wall,path,wall },
		{ wall,path,wall,wall,wall,path,wall,wall,wall,wall,wall,path,wall,wall,wall,path,wall },
		{ wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall },
		{ wall,path,wall,wall,wall,path,wall,wall,wall,wall,wall,path,wall,wall,wall,path,wall },
		{ wall,path,path,wall,path,path,path,path,wall,path,path,path,wall,path,path,path,wall },
		{ wall,path,path,path,path,wall,wall,path,path,path,wall,path,wall,path,wall,path,wall },
		{ wallLeftTrasport,path,wall,wall,path,wall,wall,wall,path,wall,wall,path,path,path,path,path,wallRightTrasport },
		{ wall,path,wall,path,path,path,path,path,path,path,path,path,wall,wall,wall,path,wall },
		{ wall,path,wall,path,wall,wall,wall,path,wall,wall,wall,path,wall,wall,wall,path,wall },
		{ wall,path,path,path,path,path,path,path,path,path,path,path,path,path,path,path,wall },
		{ wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall,wall },
	};

	grid[boost1VerticalPos][boost1HorizontalPos] = boost;
	grid[boost2VerticalPos][boost2HorizontalPos] = boost;
	grid[boost3VerticalPos][boost3HorizontalPos] = boost;
	grid[boost4VerticalPos][boost4HorizontalPos] = boost;
	grid[boost5VerticalPos][boost5HorizontalPos] = boost;
	grid[boost6VerticalPos][boost6HorizontalPos] = boost;
	grid[boost7VerticalPos][boost7HorizontalPos] = boost;
	grid[boost8VerticalPos][boost8HorizontalPos] = boost;

	while (run == true) {
		grid[ghostPos1][ghostPos2] = ghost;
		grid[pacManVerticalPos][pacManHorizontalPos] = packDude;
		if (time(0)) {
			m++;
		}
		for (int row = 0; row < 17; row++) {
			for (int col = 0; col < 17; col++) {
				amountAllowed++;
				movePacMan(pacManVerticalPos, pacManHorizontalPos, grid, score, m, boostOn, run);
				if (grid[4][16] != packDude) {
					grid[4][16] = wallRightTrasport;
				}
				if (grid[12][16] != packDude) {

					grid[12][16] = wallRightTrasport;
				}
				if (grid[4][0] != packDude) {
					grid[4][0] = wallLeftTrasport;
				}

				if (grid[12][0] != packDude) {
					grid[12][0] = wallLeftTrasport;
				}
				if (grid[4][10] != packDude) {
					grid[4][10] = crystal;
				}
				characterForColorCheck = grid[row][col];
				setColorOnGrid(characterForColorCheck, amountAllowed);
				if (boostOn == true) {
				}
				if (m == 18) {
					boostOn = false;
					ghost = 1;
				}
				cout << grid[row][col];
				if (grid[row][col] == path || grid[row][col] == boost) {
					pelletCounter++;
				}
			}
			cout << endl;
		}
		if (pelletCounter == 0) {
			gameOverLink();
			run = false;
		}
		else if (pelletCounter > 0) {
			run = true;
		}
		pelletCounter = 0;
		setcolor(15);
		pacmansLives(lives, packDude);
		if (ghostIncrementForSpeed == ghostSpeedLimit) {
			ghostDudeChasing(ghostPos1, ghostPos2, pacManVerticalPos, pacManHorizontalPos,
				grid, pathReplace1, pathReplace2);
			ghostIncrementForSpeed = 0;
		}
		ghostIncrementForSpeed++;
		cout << endl << "Player Score " << score;
		loopRepeats++;
		pacManAndGhostContact(pacManVerticalPos, pacManHorizontalPos,
			ghostPos1, ghostPos2, lives, pathReplace1, pathReplace2, grid);
		scoreDisplay = score;
		Sleep(200);
		system("CLS");
	}
	setColorOnGrid(characterForColorCheck, amountAllowed);
	int b = 0;
	int c = 0;
	coolColors = true;
}

void setcolor(unsigned short color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void SetPos(int x, int y) {
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void Blinking() {
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void ghostRetreat(int &ghostPos1, int &ghostPos2, char grid[17][17], int &ghostTravelPathY, int &ghostTravelPathX, char ghost, int pathReplace1, int pathReplace2, bool &ghostPath1, bool &ghostPath2, bool &ghostPath3, bool &ghostPath4, bool &ghostPath5, bool &ghostPath6, bool &ghostPath7, bool &ghostPath8, char boostOn) {
	char wall = 219;
	char tempTwo = ' ';
	if (boostOn == true) {
		if (ghostPos1 < ghostTravelPathY && grid[ghostPos1 + 1][ghostPos2] != wall) {
			pathReplace1 = ghostPos1 + 1;
			pathReplace2 = ghostPos2;
			tempTwo = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = ghost;
			grid[ghostPos1][ghostPos2] = tempTwo;
			ghostPos1++;
		}
		if (ghostPos1 > ghostTravelPathY && grid[ghostPos1 - 1][ghostPos2] != wall) {
			pathReplace1 = ghostPos1 - 1;
			pathReplace2 = ghostPos2;
			tempTwo = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = ghost;
			grid[ghostPos1][ghostPos2] = tempTwo;
			ghostPos1--;
		}
		if (grid[ghostPos1 + 1][ghostPos2] == wall) {
			if (grid[ghostPos1][ghostPos2 - 1] != wall) {
				pathReplace2 = ghostPos2 - 1;
				pathReplace1 = ghostPos1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos2--;
			}
			if (grid[ghostPos1][ghostPos2 + 1] != wall) {
				pathReplace2 = ghostPos2 + 1;
				pathReplace1 = ghostPos1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos2++;
			}
		}
		else if (grid[ghostPos1 - 1][ghostPos2] == wall) {
			if (grid[ghostPos1][ghostPos2 - 1] != wall) {
				pathReplace2 = ghostPos2 - 1;
				pathReplace1 = ghostPos1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos2--;
			}
			if (grid[ghostPos1][ghostPos2 + 1] != wall) {
				pathReplace2 = ghostPos2 + 1;
				pathReplace1 = ghostPos1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos2++;
			}
		}
		if (ghostPos2 < ghostTravelPathX && grid[ghostPos1][ghostPos2 + 1] != wall) {
			pathReplace2 = ghostPos2 + 1;
			pathReplace1 = ghostPos1;
			tempTwo = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = ghost;
			grid[ghostPos1][ghostPos2] = tempTwo;
			ghostPos2++;
		}
		else if (ghostPos2 > ghostTravelPathX && grid[ghostPos1][ghostPos2 - 1] != wall) {
			pathReplace2 = ghostPos2 - 1;
			pathReplace1 = ghostPos1;
			tempTwo = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = ghost;
			grid[ghostPos1][ghostPos2] = tempTwo;
			ghostPos2--;
		}
		if (grid[ghostPos1][ghostPos2 - 1] == wall) {
			if (grid[ghostPos1 - 1][ghostPos2] != wall) {
				pathReplace2 = ghostPos2;
				pathReplace1 = ghostPos1 - 1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos1--;
			}
			if (grid[ghostPos1 + 1][ghostPos2] != wall) {
				pathReplace2 = ghostPos2;
				pathReplace1 = ghostPos1 + 1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos1++;
			}
		}
		else if (grid[ghostPos1][ghostPos2 - 1] == wall) {
			if (grid[ghostPos1 - 1][ghostPos2] != wall) {
				pathReplace2 = ghostPos2;
				pathReplace1 = ghostPos1 - 1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos1--;
			}
			if (grid[ghostPos1 + 1][ghostPos2] != wall) {
				pathReplace2 = ghostPos2;
				pathReplace1 = ghostPos1 + 1;
				tempTwo = grid[pathReplace1][pathReplace2];
				grid[pathReplace1][pathReplace2] = ghost;
				grid[ghostPos1][ghostPos2] = tempTwo;
				ghostPos1++;
			}
		}
		if (grid[ghostPos1][ghostPos2] == grid[8][1] && ghostPath1 == true) {
			ghostTravelPathY = 15;
			ghostTravelPathX = 15;
			ghostPath1 = false;
			ghostPath2 = false;
		}
		if (grid[ghostPos1][ghostPos2] == grid[8][15] && ghostPath1 == true) {
			ghostTravelPathY = 15;
			ghostTravelPathX = 15;
			ghostPath1 = false;
			ghostPath2 = false;
		}
		if (grid[ghostPos1][ghostPos2] == grid[2][1] && ghostPath1 == true) {
			ghostTravelPathY = 15;
			ghostTravelPathX = 15;
			ghostPath1 = false;
			ghostPath2 = false;
		}
		else if (grid[ghostPos1][ghostPos2] == grid[15][15] && ghostPath2 == false) {
			ghostTravelPathY = 1;
			ghostTravelPathX = 15;
			ghostPath2 = true;
			ghostPath3 = false;
		}

		else if (grid[ghostPos1][ghostPos2] == grid[1][15] && ghostPath3 == false) {
			ghostTravelPathY = 15;
			ghostTravelPathX = 1;
			ghostPath3 = true;
			ghostPath4 = false;
		}
		if (grid[ghostPos1][ghostPos2] == grid[1][8] && ghostPath4 == false) {
			ghostTravelPathY = 8;
			ghostTravelPathX = 1;
			ghostPath4 = true;
			ghostPath5 = false;
		}
		if (grid[ghostPos1][ghostPos2] == grid[15][8] && ghostPath4 == false) {
			ghostTravelPathY = 8;
			ghostTravelPathX = 1;
			ghostPath4 = true;
			ghostPath5 = false;
		}
		if (grid[ghostPos1][ghostPos2] == grid[15][1] && ghostPath4 == false) {
			ghostTravelPathY = 8;
			ghostTravelPathX = 1;
			ghostPath4 = true;
			ghostPath5 = false;
		}
		else if (grid[ghostPos1][ghostPos2] == grid[8][1] && ghostPath5 == false) {
			ghostTravelPathY = 8;
			ghostTravelPathX = 8;
			ghostPath5 = true;
			ghostPath6 = false;
		}
		else if (grid[ghostPos1][ghostPos2] == grid[8][8] && ghostPath6 == false) {
			ghostTravelPathY = 2;
			ghostTravelPathX = 1;
			ghostPath1 = true;
			ghostPath2 = true;
			ghostPath3 = true;
			ghostPath4 = true;
			ghostPath5 = true;
			ghostPath6 = true;
		}
	}
}

void ghostDudeChasing(int &ghostPos1, int &ghostPos2, int pacManPos1, int pacManPos2, char grid[17][17], int &pathReplace1, int &pathReplace2) {
	char temp = ' ';
	char wall = 219;
	if ((ghostPos1 > pacManPos1) && (validateGhostMove(grid[ghostPos1 - 1][ghostPos2]) == true)) {
		pathReplace1 = ghostPos1 - 1;
		pathReplace2 = ghostPos2;
		if (grid[pathReplace1][pathReplace2] != packDude) {
			temp = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
			grid[ghostPos1][ghostPos2] = temp;
			ghostPos1--;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
	}
	else if ((ghostPos1 < pacManPos1) && (validateGhostMove(grid[ghostPos1 + 1][ghostPos2]) == true)) {
		pathReplace1 = ghostPos1 + 1;
		pathReplace2 = ghostPos2;
		if (grid[pathReplace1][pathReplace2] != packDude) {
			temp = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
			grid[ghostPos1][ghostPos2] = temp;
			ghostPos1++;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
	}
	else if ((ghostPos2 > pacManPos2) && (validateGhostMove(grid[ghostPos1][ghostPos2 - 1]) == true)) {
		pathReplace1 = ghostPos1;
		pathReplace2 = ghostPos2 - 1;
		if (grid[pathReplace1][pathReplace2] != packDude) {
			temp = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
			grid[ghostPos1][ghostPos2] = temp;
			ghostPos2--;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
	}
	else if ((ghostPos2 < pacManPos2) && (validateGhostMove(grid[ghostPos1][ghostPos2 + 1]) == true)) {
		pathReplace1 = ghostPos1;
		pathReplace2 = ghostPos2 + 1;
		if (grid[pathReplace1][pathReplace2] != packDude) {
			temp = grid[pathReplace1][pathReplace2];
			grid[pathReplace1][pathReplace2] = grid[ghostPos1][ghostPos2];
			grid[ghostPos1][ghostPos2] = temp;
			ghostPos2++;
		}
		replaceCharsAfterSwap(pathReplace1, pathReplace2, pacManPos1, pacManPos2, ghostPos1, ghostPos2, grid);
	}
}

void replaceCharsAfterSwap(int pathReplace1, int pathReplace2, int pacManPos1, int pacManPos2, int ghostPos1, int ghostPos2, char grid[17][17]) {
	if (grid[pathReplace1][pathReplace2] == packDude) {
		grid[pacManPos1][pacManPos2] = ' ';
		grid[ghostPos1][ghostPos2] = grid[pathReplace1][pathReplace2];
	}
}

void movePacMan(int &pacManVerticalPos, int &pacManHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn, bool &run) {
	char userInput = ' ';
	int moveVerticalPos = 0;
	int moveHorizontalPos = 0;
	grabUserInputForPac(userInput);
	if (userInput == up) {
		moveVerticalPos = pacManVerticalPos - 1;
		moveHorizontalPos = pacManHorizontalPos;
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	else if (userInput == down) {
		moveVerticalPos = pacManVerticalPos + 1;
		moveHorizontalPos = pacManHorizontalPos;
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	else if (userInput == left1) {
		moveVerticalPos = pacManVerticalPos;
		moveHorizontalPos = pacManHorizontalPos - 1;
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	else if (userInput == rigth1) {
		moveVerticalPos = pacManVerticalPos;
		moveHorizontalPos = pacManHorizontalPos + 1;
		pacManSwap(pacManVerticalPos, pacManHorizontalPos, moveVerticalPos, moveHorizontalPos, grid, userInput,
			score, m, boostOn);
	}
	else if (userInput == ESC) {
		toQuitTheGame(run);
	}
	clearBuffer(userInput);
}

void grabUserInputForPac(char &userInput) {
	if (_kbhit()) {
		userInput = _getch();
	}
}

void pacManSwap(int &pacManVerticalPos, int &pacManHorizontalPos, int moveVerticalPos, int moveHorizontalPos, char grid[17][17], char userInput, int &score, int &m, bool &boostOn) {
	char temp = ' ';
	const char emptyPath = ' ';
	const char wall = 219;
	if (validatePacManMove(grid[moveVerticalPos][moveHorizontalPos]) == true) {
		scores(moveVerticalPos, moveHorizontalPos, grid, score, m, boostOn);
		temp = grid[pacManVerticalPos][pacManHorizontalPos];
		grid[pacManVerticalPos][pacManHorizontalPos] = emptyPath;
		grid[moveVerticalPos][moveHorizontalPos] = temp;
		pacManChangePosValue(pacManVerticalPos, pacManHorizontalPos, userInput);
	}
	shortCutAcrossGrid(pacManVerticalPos, pacManHorizontalPos, grid);
}

void scores(int moveVerticalPos, int moveHorizontalPos, char grid[17][17], int &score, int &m, bool &boostOn) {
	const char path = 249;
	const char boost = 15;
	if (grid[moveVerticalPos][moveHorizontalPos] == path) {
		score++;
	}
	if (grid[moveVerticalPos][moveHorizontalPos] == boost) {
		score += 50;
		m = 0;
		boostOn = true;
	}
}

void pacManChangePosValue(int &pacManVerticalPos, int &pacManHorizontalPos, char userInput) {
	if (userInput == 'H') {
		pacManVerticalPos--;
	}
	else if (userInput == 'P') {
		pacManVerticalPos++;
	}
	else if (userInput == 'K') {
		pacManHorizontalPos--;
	}
	else if (userInput == 'M') {
		pacManHorizontalPos++;
	}
}

void shortCutAcrossGrid(int &verticalPos, int &horizontalPos, char grid[17][17]) {
	if (verticalPos == 4 && horizontalPos == 0) {
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 4;
		horizontalPos = 16;
	}
	else if (verticalPos == 4 && horizontalPos == 16) {
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 4;
		horizontalPos = 0;
	}
	else if (verticalPos == 12 && horizontalPos == 0) {
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 12;
		horizontalPos = 16;
	}
	else if (verticalPos == 12 && horizontalPos == 16) {
		grid[verticalPos][horizontalPos] = ' ';
		verticalPos = 12;
		horizontalPos = 0;
	}
}

bool validateGhostMove(char test) {
	bool toMove = true;
	if (test == wall) {
		toMove = false;
	}
	else {
		toMove = true;
	}
	return toMove;
}

bool validatePacManMove(char test) {
	bool toMove = true;
	if (test == wall) {
		toMove = false;
	}
	else if (test == ghost) {
		toMove = false;
	}
	else {
		toMove = true;
	}
	return toMove;
}

void setColorOnGrid(char grabbedChar, int amountAllowed) {
	char pacDude = 2;
	char wall = 219;
	char path = 249;
	char ghost = 1;
	char boost = 15;
	char crystal = 249;
	char bonus = 249;
	char wallLeftTrasport = 174;
	char wallRightTrasport = 175;
	if (grabbedChar == pacDude) {
		setcolor(14);
	}
	if (grabbedChar == wall) {
		setcolor(9);
	}
	else if (grabbedChar == path) {
		setcolor(14);
	}
	else if (grabbedChar == ghost) {
		setcolor(12);
	}
	else if (grabbedChar == crystal) {
		setcolor(14);
	}
	else if (grabbedChar == wallLeftTrasport) {
		setcolor(12);
	}
	else if (grabbedChar == wallRightTrasport) {
		setcolor(12);
	}
	else if (grabbedChar == boost) {
		setcolor(14);
	}
}

void clearBuffer(char &movingDirection) {
	movingDirection = ' ';
}

void clearScreen() {
	system("CLS");
}

void HighScores(int score) {
	int FirstPlace = 0;
	int SecondPlace = 0;
	int ThirdPlace = 0;
	int ArrayPosition = 0;
	string PlayersName = " ";
	ifstream fin(R"(C:\Users\ТурсунхановАл\Desktop\PacmanTotalScores.txt)");
	ofstream sout(R"(C:\Users\ТурсунхановАл\Desktop\PacmanHighScores.txt)");
	cout << "Please type your name" << endl;
	cin >> PlayersName;
	int ScoresArray[] = { FirstPlace, SecondPlace, ThirdPlace, score };
	sout << "Player's Name\t";
	sout << "Player's Scores" << endl;
	clearScreen();
	cout << "Congratulations! You're winner chicken dinner!" << endl << endl;
	cout << "\t" << PlayersName << "  " << score << endl << endl;
	sout << PlayersName << "\t\t\t" << score << endl;
	system("Pause");
	return;
}

void pacManAndGhostContact(int &pacManVerticalPos, int &pacManHorizontalPos, int &ghostVerticalPos, int &ghostHorizontalPos, int &lives, int pathReplace1, int pathReplace2, char grid[17][17]) {
	if ((pacManVerticalPos == pathReplace1) && (pacManHorizontalPos == pathReplace2)) {
		lifeDecrementation(lives);
		resetValues(pacManVerticalPos, pacManHorizontalPos, ghostVerticalPos, ghostHorizontalPos);
	}
}

void resetValues(int &pacManVerticalPos, int &pacManHorizontalPos, int &ghostVerticalPos, int &ghostHorizontalPos) {
	pacManVerticalPos = pacManDefaultVerticalPos;
	pacManHorizontalPos = pacManDefaultHorizontalPos;
	ghostVerticalPos = ghostDefaultVerticalPos;
	ghostHorizontalPos = ghostDefaultHorizontal;
}


void gameOverLink() {
	bool newGameQuestion = false;
	int counter = 100;
	int displayCount = 0;
	clearScreen();
	setcolor(15);
	cout << "Your Score: " << scoreDisplay << endl << endl;
	cout << "GAME OVER" << endl << endl << endl;
	Sleep(1500);
	clearScreen();
	HighScores(scoreDisplay);
	clearScreen();
	GameMenu(newGameQuestion);
}

void lifeDecrementation(int &numberOfLives) {
	numberOfLives--;
	if (numberOfLives >= 0) {
		clearScreen();
		if (numberOfLives > 1) {
			cout << "You Have " << numberOfLives << " lives Left";
		}
		else if (numberOfLives == 1) {
			cout << "You Have " << numberOfLives << " LIFE Left";
		}
		else {
			cout << "LAST LIFE";
		}
		cout << endl << endl;
		system("pause");
	}
	else if (numberOfLives < 0) {
		gameOverLink();
	}
}

void pacmansLives(int numberOfLives, char packDude) {
	cout << "Lives Left: ";
	for (int x = numberOfLives; x > 0; x--) {
		cout << packDude;
	}
}

void toQuitTheGame(bool &run) {
	clearScreen();
	int key;
	int menu = 1;
	bool repeat = false;
	setcolor(0x08);
	cout << "Are you sure you want to quit the game?" << endl;
	setcolor(0x06);
	cout << "->" << " YES" << endl;
	setcolor(0x08);
	cout << "  " << " NO" << endl;
	while (true) {
		if (_kbhit()) {
			key = _getch();
			if (key == down) {
				if (menu == 1) {
					menu = 2;
					clearScreen();
					setcolor(0x08);
					cout << "Are you sure you want to quit the game?" << endl;
					setcolor(0x08);
					cout << "  " << " YES" << endl;
					setcolor(0x06);
					cout << "->" << " NO" << endl;
				}
				else if (menu == 2) {
					menu = 1;
					clearScreen();
					setcolor(0x08);
					cout << "Are you sure you want to quit the game?" << endl;
					setcolor(0x06);
					cout << "->" << " YES" << endl;
					setcolor(0x08);
					cout << "  " << " NO" << endl;
				}
			}
			if (key == up) {
				if (menu == 1) {
					menu = 2;
					clearScreen();
					setcolor(0x08);
					cout << "Are you sure you want to quit the game?" << endl;
					setcolor(0x08);
					cout << "  " << " YES" << endl;
					setcolor(0x06);
					cout << "->" << " NO" << endl;
				}
				else if (menu == 2) {
					menu = 1;
					clearScreen();
					setcolor(0x08);
					cout << "Are you sure you want to quit the game?" << endl;
					setcolor(0x06);
					cout << "->" << " YES" << endl;
					setcolor(0x08);
					cout << "  " << " NO" << endl;
				}
			}
			if (key == ENTER) {
				clearScreen();
				if (menu == 1) {
					main();
				}
				else if (menu == 2) {
					repeat = true;
				}
			}
		}
	}
	clearScreen();
}

void Loading() {
	cout << "PACMAN by Alisher & Aknur" << endl;
	cout << "All rigths reserved." << endl << endl;
	cout << "\tLoading";
	for (int i = 6; i > 0; i--) {
		cout << ".";
		Sleep(500);
	}
}

void GameMenu(bool &exitGame) {
	clearScreen();
	int key;
	int menu = 1;
	setcolor(0x08);
	cout << " PACMAN MAIN MENU " << endl;
	setcolor(0x06);
	cout << "->" << " PLAY GAME" << endl;
	setcolor(0x08);
	cout << "  " << " QUIT" << endl;
	while (true) {
		if (_kbhit()) {
			key = _getch();
			clearScreen();
			if (key == down) {
				if (menu == 1) {
					menu = 2;
					setcolor(0x08);
					cout << " PACMAN MAIN MENU " << endl;
					setcolor(0x08);
					cout << "  " << " PLAY GAME" << endl;
					setcolor(0x06);
					cout << "->" << " QUIT" << endl;
				}
				else if (menu == 2) {
					menu = 1;
					setcolor(0x08);
					cout << " PACMAN MAIN MENU " << endl;
					setcolor(0x06);
					cout << "->" << " PLAY GAME" << endl;
					setcolor(0x08);
					cout << "  " << " QUIT" << endl;
				}
			}
			if (key == up) {
				if (menu == 1) {
					menu = 2;
					setcolor(0x08);
					cout << " PACMAN MAIN MENU " << endl;
					setcolor(0x08);
					cout << "  " << " PLAY GAME" << endl;
					setcolor(0x06);
					cout << "->" << " QUIT" << endl;
				}
				else if (menu == 2) {
					menu = 1;
					setcolor(0x08);
					cout << " PACMAN MAIN MENU " << endl;
					setcolor(0x06);
					cout << "->" << " PLAY GAME" << endl;
					setcolor(0x08);
					cout << "  " << " QUIT" << endl;
				}
			}
			if (key == ENTER) {
				clearScreen();
				if (menu == 1) {
					bool reset = true;
					Game(reset);
					break;
				}
				else if (menu == 2) {
					clearScreen();
					exitGame = true;
					setcolor(0x04);
					cout << "E";
					Sleep(200);
					cout << "X";
					Sleep(200);
					cout << "I";
					Sleep(200);
					cout << "T";
					Sleep(200);
					cout << "!";
					exit(0);
				}
			}
		}
	}
}
