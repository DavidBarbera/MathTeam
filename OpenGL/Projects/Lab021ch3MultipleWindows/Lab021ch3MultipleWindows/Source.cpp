#include "Libraries.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

// Globals.
static int id1, id2; // Window identifiers.

void display1()
{
	// Choose window.
	glutSetWindow(id1);

	glClear(GL_COLOR_BUFFER_BIT);

	// A red square.
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(40.0, 10.0, 0.0);
	glVertex3f(40.0, 40.0, 0.0);
	glVertex3f(10.0, 40.0, 0.0);
	glEnd();
	glutSwapBuffers();

}

void display2()
{
	// Choose window.
	glutSetWindow(id2);

	glClear(GL_COLOR_BUFFER_BIT);

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
	glutSwapBuffers();

}
void setup1()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
void setup2()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
void resize1(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Non-square aspect ratio squashes the square.
	glOrtho(0.0, 50.0, 0.0, 100.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void resize2(int w, int h)
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

//---- Window 1 ---------------------------------------
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	id1 = glutCreateWindow("Window 1");
	setup1();
	glutDisplayFunc(display1);
	glutReshapeFunc(resize1);
	glutKeyboardFunc(KeyInput);

//---- Window 2 ---------------------------------------
	glutInitWindowPosition(500, 0);
	glutInitWindowSize(500, 500);
	id2 = glutCreateWindow("Window 2");
	setup2();
	glutDisplayFunc(display2);
	glutReshapeFunc(resize2);
	glutKeyboardFunc(KeyInput);


	init_glew();

	
	setup2();


	glutMainLoop();

}//main
