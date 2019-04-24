/**
 * Author: Brandon Aldridge
 *
 * Tetris implementing GLUT
 * Created for the final for Graphics
 * */

#include <GL/glut.h> 
#include <stdlib.h> 
//#include <math.h>

#define GRID_X 10
#define GRID_Y 20 
#define BLOCK_SIZE 30

GLsizei winWidth = BLOCK_SIZE * GRID_X, winHeight = BLOCK_SIZE * GRID_Y;

int speed = 1;
int speedThreshold = 30;
int speedCounter = 0;

//boolean array basically
int board[GRID_X][GRID_Y];

//contains the coords of the active block
int activeBlockPoints[4][2];


void keyboard(unsigned char key, int x, int y) {

	//TODO do stuff here on key input

	glutPostRedisplay(); //redraws the scene instantly
}

void tetris() {

	if (blockPlace() > 0) {

		int pointsToAdd = checkLineClears();
		if (pointsToAdd > 0) {

			addPoints(pointsToAdd);
		}
	}

	if (speed >= speedThreshold) {

		speedCounter = 0;
		moveBlockDown();
	}

	addBlockToBoard();

	glutPostRedisplay();

	removeBlockFromBoard();
	incrementCounters();

}

int main(int argc, char ** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(50, 50);

	glutInitWindowSize(winWidth, winHeight);



	glutCreateWindow("TETRIS");



	//init();


	glutKeyboardFunc(keyboard);
	glutIdleFunc(tetris);
	glutDisplayFunc(displayFcn); //TODO implement display function
	//glutReshapeFunc(winReshapeFcn);



	glutMainLoop();

	return 0;
}


//adds a number of points to the score
void addPoints(int pointsToAdd) {

	//TODO add points
}


//returns the number of lines
int checkLineClears() {

	int numberOfClears = 0;

	for (int i = GRID_Y - 1; i > 0; i--) {

		int lineCount = 0;
		for (int j = 0; j < GRID_X; j++) {

			lineCount += board[i][j];
		}

		if (lineCount >= GRID_X) {

			clearLine(i);
			numberOfClears++;
		}
	}

	return numberOfClears;
}


/**clears the line and moves everything above it one line down
 * */
void clearLine(int row) {

	for (int y = row; y < GRID_Y - 1; y++) {

		for (int x = 0; x < GRID_X; x++) {

			board[x][y] = board[x + 1][y];
		}
	}

	for (int x = 0; x < GRID_X; x++) {

		board[x][GRID_Y - 1] = 0;
	}
}


/**increments all the counter flags
 * */
void incrementCounters() {

	speedCounter++;
}


/**moves the active block down one space
 * */
void moveBlockDown() {

	for (int i = 0; i < 4; i++) {

		activeBlockPoints[i][1]--;
	}
}


/**checks if the block would clip with an existing block if it would move
 * if it does, place the block
 * */
int blockPlace() {

	for (int i = 0; i < 4; i++) {

		int tempBlockX = activeBlockPoints[i][0];
		int tempBlockY = activeBlockPoints[i][1] - 1;

		if (tempBlockY < 0 || board[tempBlockX][tempBlockY]) {

			addBlockToBoard();
			createNewBlock();
			return 1;
		}
	}

	return 0;
}


/** creates a new block at the top
 * */
void createNewBlock() {

	//TODO implement
}



/** Adds the block to the board
 * --note: Must be removed before doing more logic
 * */
void addBlockToBoard() {

	for (int i = 0; i < 4; i++) {

		board[activeBlockPoints[i][0]][activeBlockPoints[i][1]] = 1;
	}
}


//Removes the block from the board
void removeBlockFromBoard() {

	for (int i = 0; i < 4; i++) {

		board[activeBlockPoints[i][0]][activeBlockPoints[i][1]] = 0;
	}
}


//INTERRUPT -- implement after everything else works
void rotateBlock() {

	//rotate the activeBlock
}


//INTERRUPT
void moveBlock(int isMoveRight) {

	int tempBlock[4][2];

	for (int i = 0; i < 4; i++) {

		if (isMoveRight) {

			if (tempBlock[i][0] + 1 >= GRID_X) {

				return;
			}
			tempBlock[i][0]++;
		}
		else {

			if (tempBlock[i][0] + 1 <= 0) {

				return;
			}
			tempBlock[i][0]--;
		}
	}

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 2; j++) {

			activeBlockPoints[i][j] = tempBlock[i][j];
		}
	}
}