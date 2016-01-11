#include "Libraries.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

// Globals.
static int width, height; // OpenGL window size.

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 0.0); //Yellow; the drawing color
							  // Define first viewport.
	glViewport(0, 0, width / 2.0, height);

// Begin contents of first viewport.-------------------
	// A red square.
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(40.0, 10.0, 0.0);
	glVertex3f(40.0, 40.0, 0.0);
	glVertex3f(10.0, 40.0, 0.0);
	glEnd();
	// End contents of first viewport.

// Define second viewport.------------------------------
	glViewport(width / 2.0, 0, width / 2.0, height);

	// Begin contents of second viewport.
	// A blue circle.
	glColor3f(0.0, 0.0, 1.0);
	float angle;
	int i;
	glBegin(GL_LINE_LOOP);
	for (i = 0; i < 30; ++i)
	{
		angle = 2 * PI * i / 30;
		glVertex2f(50.0 + cos(angle) * 40.0, 50.0 + sin(angle) * 40.0);
	}
	glEnd();

	// A vertical bluish line at the left to separate the viewports.
	glColor3f(0.2, 0.2, 0.5);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex3f(0.1, 0.0, 0.0);
	glVertex3f(0.1, 100.0, 0.0);
	glEnd();
	glLineWidth(1.0);
	// End contents of second viewport.
	

	glutSwapBuffers();

}

void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;
}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void init_glew()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error initializing GLEW: %s\n",
			glewGetErrorString(err));
	}
}

int main(int argv, char** argc)
{
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Window");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
