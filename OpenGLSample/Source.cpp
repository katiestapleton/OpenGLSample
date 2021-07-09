#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>

using namespace std;

const float DEG2RAD = 3.14159 / 180;

void processInput(GLFWwindow* window);

enum BRICKTYPE { REFLECTIVE, DESTRUCTABLE };
enum ONOFF { ON, OFF };

class Brick
{
public:
	float red, green, blue;
	float x, y, width;
	BRICKTYPE brick_type;
	ONOFF onoff;

	Brick(BRICKTYPE bt, float xx, float yy, float ww, float r, float g, float b)
	{
		brick_type = bt; x = xx; y = yy, width = ww; red = r, green = g, blue = b;
		onoff = ON;
	};

	void drawBrick()
	{
		if (onoff == ON)
		{
			double halfside = width / 2;

			glColor3d(red, green, blue);
			glBegin(GL_POLYGON);

			glVertex2d(x + halfside, y + halfside);
			glVertex2d(x + halfside, y - halfside);
			glVertex2d(x - halfside, y - halfside);
			glVertex2d(x - halfside, y + halfside);

			glEnd();
		}
	}
};


class Circle
{
public:
	float red, green, blue;
	float radius;
	float x;
	float y;
	float speed = 0.03;
	int direction; // 1=up 2=right 3=down 4=left 5 = up right   6 = up left  7 = down right  8= down left
	ONOFF onoff;


	Circle(double xx, double yy, double rr, int dir, float rad, float r, float g, float b)
	{
		x = xx;
		y = yy;
		radius = rr;
		red = r;
		green = g;
		blue = b;
		radius = rad;
		direction = dir;
		onoff = ON;
	}

	// random color generator for collisions
	// converts into decimal
	int GetRandomColor()
	{
		float color = (rand() % 256) / 256;
		float absColor = abs(color)+0.1;
		return absColor;
	}
	
	void CheckCollision(Brick* brk, Circle* cir)
	{
		if (brk->brick_type == REFLECTIVE)
		{
			// uses random color generator function to retrieve color
			float redNew = GetRandomColor();
			float greenNew = GetRandomColor();
			float blueNew = GetRandomColor();

			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{
				direction = GetRandomDirection();
				x = x + 0.03;
				y = y + 0.04;

				// assigned new color to brick color upon collision
				brk->red = redNew;
				brk->green = greenNew;
				brk->blue = blueNew;

				// changes color of ball to match new brick color upon collision
				cir->red = redNew;
				cir->green = greenNew;
				cir->blue = blueNew;
			}

		}
		else if (brk->brick_type == DESTRUCTABLE)
		{

			if ((x > brk->x - brk->width && x <= brk->x + brk->width) && (y > brk->y - brk->width && y <= brk->y + brk->width))
			{
				brk->onoff = OFF;
			}

			//destructable brick: collision makes ball disappear
			cir->onoff = OFF;
		}
	}

	int GetRandomDirection()
	{
		return (rand() % 8) + 1;
	}
	

	
	void MoveOneStep()
	{
		if (direction == 1 || direction == 5 || direction == 6)  // up
		{
			if (y > -1 + radius)
			{
				y -= speed;
			}
			else
			{
				//direction = GetRandomDirection();
                // applied basic physics to bounce back of ball
				direction = 3;
			}
		}

		if (direction == 2 || direction == 5 || direction == 7)  // right
		{
			if (x < 1 - radius)
			{
				x += speed;

			}
			else
			{
				//direction = GetRandomDirection();

				// applied basic physics to bounce back of ball
				direction = 4;
			}
		}

		if (direction == 3 || direction == 7 || direction == 8)  // down
		{
			if (y < 1 - radius) {
				y += speed;

			}
			else
			{
				//direction = GetRandomDirection();

				// applied basic physics to bounce back of ball
				direction = 1;
			}
		}

		if (direction == 4 || direction == 6 || direction == 8)  // left
		{
			if (x > -1 + radius) {
				x -= speed;
			}
			else
			{
				//direction = GetRandomDirection();

				// applied basic physics to bounce back of ball
				direction = 2;
			}
		}

	}

	void DrawCircle()
	{
		// circle must be "on" to be drawn
		if (onoff == ON)
		{
			glColor3f(red, green, blue);
			glBegin(GL_POLYGON);
			for (int i = 0; i < 360; i++) {
				float degInRad = i * DEG2RAD;
				glVertex2f((cos(degInRad) * radius) + x, (sin(degInRad) * radius) + y);
			}

			glEnd();
		}
	}
};


vector<Circle> world;


int main(void) {
	srand(time(NULL));

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(480, 480, "Random World of Circles", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	Brick brick(REFLECTIVE,     0.19, -0.64, 0.17, 0.53, 0.29, 0.87);
	Brick brick1(REFLECTIVE,    0.00, 0.00, 0.00,  1.0, 0.97, 0.30);
	Brick brick2(DESTRUCTABLE, -0.51, 0.50, 0.19,  1.0, 0.82, 0.23);
	Brick brick3(DESTRUCTABLE,  0.75, 0.27, 0.23, 0.0, 0.43, 1.0);
	// center box. do not change coordinates for brick 4
	Brick brick4(REFLECTIVE,    0, 0, 0.2, 1, 0.5, 0.5);
	Brick brick5(DESTRUCTABLE, -0.15, 0.63, 0.22,  0.94, 0.32, 0.17);
	Brick brick6(DESTRUCTABLE,  -0.67, -0.72, 0.12,  0.42, 0.61, 0.67);
	Brick brick7(DESTRUCTABLE, -0.52, -0.14, 0.33,  0.17, 0.16, 0.73);
	Brick brick8(REFLECTIVE,   0.64, -0.22, 0.27,  0.48, 0.37, 0.0);
	Brick brick9(REFLECTIVE,   0.42, 0.72, 0.21,  0.00, 0.8, 0.8);


	while (!glfwWindowShouldClose(window)) {
		//Setup View
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);


		//Movement
		for (int i = 0; i < world.size(); i++)
		{
			world[i].DrawCircle();

			// returns circle from given location in vector. used to check collisions
			Circle circle = world.at(i);

			world[i].CheckCollision(&brick, &circle);
			world[i].CheckCollision(&brick2, &circle);
			world[i].CheckCollision(&brick3, &circle);
			world[i].CheckCollision(&brick4, &circle);
			world[i].MoveOneStep();
		}

		brick.drawBrick();
		brick1.drawBrick();
		brick2.drawBrick();
		brick3.drawBrick();
		brick4.drawBrick();
		brick5.drawBrick();
		brick6.drawBrick();
		brick7.drawBrick();
		brick8.drawBrick();
		brick9.drawBrick();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		double r, g, b;
		r = rand() / 10000;
		g = rand() / 10000;
		b = rand() / 10000;
		Circle B(0, 0, 02, 2, 0.05, r, g, b);
		world.push_back(B);
	}
}