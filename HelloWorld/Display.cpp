///* to display game on screen*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>


int const numBlocksX = 10;
int const numBlocksY = 20;
GLfloat const blockSize = 30;

GLsizei winWidth = numBlocksX * blockSize, winHeight = numBlocksY * blockSize;
GLfloat xMin = 0.0, xMax = 300.0, yMin = 0.0, yMax = 600.0;

//the corners of the drawn polygon and the centre of it relative to the window, not the other blocks
class block {
public:
	GLfloat centreX, centreY;
	GLfloat matrix[4][3];
};


void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(xMin, xMax, yMin, yMax);
}


block createBlock(int x, int y) {
	block block;

	block.centreX = (blockSize / 2.0) + (x * blockSize);
	block.centreY = (blockSize / 2.0) + (y * blockSize);

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
void drawBackground(int background[numBlocksX][numBlocksY]) {
	
	for (int k = 0; k < numBlocksY; k++) {
		for (int i = 0; i < numBlocksX; i++) {
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
void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	int background[numBlocksX][numBlocksY];
	background[0][1] = 1;
	background[3][4] = 1;
	drawBackground(background);

	int activeBlock[4][2] = { { 5,0 },{ 5,1 },{ 5,2 },{ 6,1 } };

	drawActiveBlock(activeBlock);
	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xMin, xMax, yMin, yMax);

	glClear(GL_COLOR_BUFFER_BIT);
}


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