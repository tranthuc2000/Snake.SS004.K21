#include <stdlib.h>
#include "glut.h"
#include <time.h>
#include <string>
#define COT 40
#define DONG 40
#define FPS 10	
#define UP 1
#define DOWN -1
#define RIGHT 2
#define LEFT -2
#define MAX 100
void start();
int snake = 3;
int score=0;
bool GameOver = false;
bool CreatFood = true;
int FoodX, FoodY;
void display_callback();
void init();
void reshape_callback(int,int);
void time_callback(int);
void keyboard_callback(int, int, int);
int DFPosX[100] = { 20,20,20 }, DFPosY[100] = { 20,19,18 };
int DFDirection = RIGHT;
void DrawSnake();
void DrawFood();
void ramdom(int&, int&);
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Snake");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, time_callback, 0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
	return 0;
}
void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	DrawSnake();
	if (GameOver == true)
	{
		exit(0);
	}
	DrawFood();
	glutSwapBuffers();
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}
void reshape_callback(int weight, int height)
{
	glViewport(0, 0, (GLsizei)weight, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	glOrtho(0.0,COT, 0.0, DONG, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void time_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, time_callback, 0);
}
void keyboard_callback(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (DFDirection != DOWN)
			DFDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		if (DFDirection != UP)
			DFDirection = DOWN;
		break;
	case GLUT_KEY_LEFT:
		if (DFDirection != RIGHT)
			DFDirection = LEFT;
		break;
	case GLUT_KEY_RIGHT:
		if (DFDirection != LEFT)
			DFDirection = RIGHT;
		break;

	}
}
void DrawSnake()
{
	for (int i = snake - 1; i > 0; i--)
	{
		DFPosX[i] = DFPosX[i - 1];
		DFPosY[i] = DFPosY[i - 1];
	}
	if (DFDirection == RIGHT)
		DFPosX[0]++;
	if (DFDirection == LEFT)
		DFPosX[0]--;
	if (DFDirection == UP)
		DFPosY[0]++;
	if (DFDirection == DOWN)
		DFPosY[0]--;
	for (int i = 0; i < snake; i++)
	{
		if (i == 0)
			glColor3f(1.0, 0.0, 1.0);
		else
			glColor3f(0.0, 1.0, 1.0);
		glRectd(DFPosX[i], DFPosY[i], DFPosX[i] + 1, DFPosY[i] + 1);
		if (i!=0 && DFPosX[0] == DFPosX[i] && DFPosY[0] == DFPosY[i])
			GameOver = true;
	}
	if (DFPosX[0] == 0 || DFPosY[0] == 0 || DFPosX[0] == 40 - 1 || DFPosY[0] == 40 - 1)
	{
		GameOver = true;
	}
	if(FoodX==DFPosX[0]&& FoodY==DFPosY[0])
	{
		score++;
		snake++;
		if (snake > MAX)
			snake = MAX;
		CreatFood = true;
	}
}
void DrawFood()
{
	glColor3f(1.0, 0.0, 1.0);
	if (CreatFood)
		ramdom(FoodX, FoodY);
	CreatFood = false;
	glRectd(FoodX, FoodY, FoodX + 1, FoodY + 1);
}
void ramdom(int& x, int& y)
{
	srand(time(NULL));
	x = 1 + rand() % (38 - 1);
	y = 1 + rand() % (38 - 1);
}