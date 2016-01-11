#include "Libraries.h"
#include <iostream>

using namespace std;

// Globals.
static unsigned int base; // Display lists base index.
static unsigned int offsets[6] = { 0, 2, 1, 1, 0, 2 }; // Array of display list offsets.

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Execute 6 display lists whose offsets from the base 
	// are in the array offsets.
	glCallLists(6, GL_INT, offsets);

	glutSwapBuffers();

}

// Initialization routine.
static void setup(void)
{
	// Return the first of an available block of three successive  list indexes - 
	//to be used as base value.
	base = glGenLists(3);

	// Specify the base to be used in subsequent display list calls.
	glListBase(base);

	// Create a display list offset 0 from the base value.
	glNewList(base, GL_COMPILE);
	// Red triangle.
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(10.0, 10.0);
	glVertex2f(20.0, 10.0);
	glVertex2f(20.0, 40.0);
	glEnd();
	glTranslatef(15.0, 0.0, 0.0);
	glEndList();

	// Create a display list offset 1 from the base value.
	glNewList(base + 1, GL_COMPILE);
	// Green  rectangle.
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(10.0, 10.0);
	glVertex2f(20.0, 10.0);
	glVertex2f(20.0, 40.0);
	glVertex2f(10.0, 40.0);
	glEnd();
	glTranslatef(15.0, 0.0, 0.0);
	glEndList();

	// Create a display list offset 2 from the base value.
	glNewList(base + 2, GL_COMPILE);
	// Blue pentagon.
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(10.0, 10.0);
	glVertex2f(20.0, 10.0);
	glVertex2f(20.0, 20.0);
	glVertex2f(15.0, 40.0);
	glVertex2f(10.0, 20.0);
	glEnd();
	glTranslatef(15.0, 0.0, 0.0);
	glEndList();

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
