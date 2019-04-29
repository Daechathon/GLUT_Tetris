/**
 * Author: Brandon Aldridge
 *
 * Tetris implementing GLUT
 * Created for the final for Graphics
 * */
 
#include "Tetris.h"

GLsizei winWidth = GRID_X * BLOCK_SIZE, winHeight = GRID_Y * BLOCK_SIZE;
GLfloat xMin = 0.0, xMax = 300.0, yMin = 0.0, yMax = 600.0;

//the corners of the drawn polygon and the centre of it relative to the window, not the other blocks
class block {
public:
	GLfloat centreX, centreY;
	GLfloat matrix[4][3];
};

int speed = 1;
int speedThreshold = 100;
int speedCounter = 0;

int score = 0;

//boolean array basically
int board[GRID_X][GRID_Y + NEW_BLOCK_BUFFER];

//contains the coords of the active block
int activeBlockPoints[4][2] = { { 5,10 },{ 5,11 },{ 5,12 },{ 6,11 } };

void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 'w':
		rotateBlock();
		break;
	case 'a':
		moveBlock(false);
		break;
	case 'd':
		moveBlock(true);
		break;
	case ' ':
		hardDrop();
		break;
	default:
		break;
	}

	glutPostRedisplay(); //redraws the scene instantly
}

void hardDrop() {


}

void displayFcn() {

	draw();
}

void tetris() {


	if (blockPlace() > 0) {

		int pointsToAdd = checkLineClears();
		if (pointsToAdd > 0) {

			addPoints(pointsToAdd);
			
		}
		glutPostRedisplay();
	}

	if (speedCounter >= speedThreshold) {

		speedCounter = 0;
		moveBlockDown();
		glutPostRedisplay();
	}

	incrementCounters();
	Sleep(10);
}

int main(int argc, char ** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("TETRIS");

	init();

	glutKeyboardFunc(keyboard);
	glutIdleFunc(tetris);
	glutDisplayFunc(displayFcn); 
	glutReshapeFunc(reshapeFcn);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glutMainLoop();

	return 0;
}


//adds a number of points to the score
void addPoints(int pointsToAdd) {

	score += pointsToAdd;
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

			board[x][y] = board[x][y + 1];
		}
	}

	for (int x = 0; x < GRID_X; x++) {

		board[x][GRID_Y - 1] = 0;
	}
}


/**increments all the counter flags
 * */
void incrementCounters() {

	speedCounter += speed;
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


/** spawns a new block at the top
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


//Emily is implementing
void rotateBlock() {

	//rotate the activeBlock
}


void moveBlock(bool isMoveRight) {

	int tempBlock[4][2];

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 2; j++) {

			tempBlock[i][j] = activeBlockPoints[i][j];
		}
	}

	for (int i = 0; i < 4; i++) {

		if (isMoveRight) {

			if (tempBlock[i][0] + 1 >= GRID_X) {

				return;
			}
			tempBlock[i][0]++;
		}
		else {

			if (tempBlock[i][0] - 1 < 0) {

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

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xMin, xMax, yMin, yMax);
}


block createBlock(int x, int y) {
	block block;

	block.centreX = (BLOCK_SIZE / 2.0) + (x * BLOCK_SIZE);
	block.centreY = (BLOCK_SIZE / 2.0) + (y * BLOCK_SIZE);

	//bottom left vertex
	block.matrix[0][0] = block.centreX - 15;
	block.matrix[0][1] = block.centreY - 15;
	//bottom right vertex
	block.matrix[1][0] = block.centreX + 15;
	block.matrix[1][1] = block.centreY - 15;
	//top right vertex
	block.matrix[2][0] = block.centreX + 15;
	block.matrix[2][1] = block.centreY + 15;
	//top left vertex
	block.matrix[3][0] = block.centreX - 15;
	block.matrix[3][1] = block.centreY + 15;

	return block;
}



void drawBlock(block block) {
	//draw a square of solid colour
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	for (GLint i = 0; i < 4; i++) {
		glVertex2f(block.matrix[i][0], block.matrix[i][1]);
	}
	glEnd();

	//draw a border
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(2);
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	for (GLint i = 0; i < 4; i++) {
		glVertex2f(block.matrix[i][0], block.matrix[i][1]);
	}
	glEnd();
}

//draw all blocks already on the board
void drawBackground(int background[GRID_X][GRID_Y + NEW_BLOCK_BUFFER]) {

	for (int k = 0; k < GRID_Y; k++) {
		for (int i = 0; i < GRID_X; i++) {
			if (background[i][k] == 1) {
				block block = createBlock(i, k);
				drawBlock(block);
			}
		}
	}
}

//draw the currently falling block
void drawActiveBlock(int activeBlock[4][2]) {

	for (int i = 0; i < 4; i++) {
		block current = createBlock(activeBlock[i][0], activeBlock[i][1]);
		drawBlock(current);
	}

}

//the main draw function tested with mock arrays
/*
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	int background[GRID_X][GRID_Y];
	background[0][1] = 1;
	background[3][4] = 1;
	drawBackground(background);

	int activeBlock[4][2] = { { 5,0 },{ 5,1 },{ 5,2 },{ 6,1 } };

	drawActiveBlock(activeBlock);
	glFlush();
}
*/

void draw() {

	glClear(GL_COLOR_BUFFER_BIT);

	drawBackground(board);

	drawActiveBlock(activeBlockPoints);
	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xMin, xMax, yMin, yMax);

	glClear(GL_COLOR_BUFFER_BIT);
}

/*
void main(int argc, char ** argv) {


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("TETRIS");

	init();
	glutDisplayFunc(draw);
	glutReshapeFunc(reshapeFcn);
	glutMainLoop();
}
*/