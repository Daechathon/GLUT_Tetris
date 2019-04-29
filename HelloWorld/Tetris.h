#pragma once
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>

#define GRID_X 10
#define GRID_Y 20 
#define BLOCK_SIZE 30
#define NEW_BLOCK_BUFFER 4 //TODO change to probably 4 later

void addPoints(int pointsToAdd);
int checkLineClears();
void clearLine(int row);
void incrementCounters();
void moveBlockDown();
int blockPlace();
void createNewBlock();
void addBlockToBoard();
void removeBlockFromBoard();
void rotateBlock();
void moveBlock(bool isMoveRight);
void hardDrop();

//______________________________________

class block;

void reshapeFcn(GLint newWidth, GLint newHeight);
void draw(void);
void draw(int activeBlock[4][2], int background[GRID_X][GRID_Y]);
void drawActiveBlock(int activeBlock[4][2]);
void drawBackground(int background[GRID_X][GRID_Y]);
void drawBlock(block block);
block createBlock(int x, int y);
void init(void);