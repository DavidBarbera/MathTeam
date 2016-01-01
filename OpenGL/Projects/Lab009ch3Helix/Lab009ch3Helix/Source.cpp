#include "Libraries.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

// Globals.
static unsigned int aHelix; // List index.

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glColor3f(1.0, 1.0, 1.0);	

	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, -70.0);
	glCallList(aHelix); // Execute display list.
	glPopMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(30.0, 0.0, -70.0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(aHelix); // Execute display list.
	glPopMatrix();

	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(-25.0, 0.0, -70.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glCallList(aHelix); // Execute display list.
	glPopMatrix();

	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -20.0, -70.0);
	glRotatef(90.0, 0.0, 0.0, 1.0);
	glCallList(aHelix); // Execute display list.
	glPopMatrix();

	glColor3f(1.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(-40.0, 40.0, -70.0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(aHelix); // Execute display list.
	glPopMatrix();

	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(30.0, 30.0, -70.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glCallList(aHelix); // Execute display list.
	glPopMatrix();
	

	glutSwapBuffers();

}

void setup()
{
	float t; // Angle parameter.

	aHelix = glGenLists(1); // Return a list index.

							// Begin create a display list.
	glNewList(aHelix, GL_COMPILE);

	// Draw a helix.
	glBegin(GL_LINE_STRIP);
	for (t = -10 * PI; t <= 10 * PI; t += PI / 20.0)
		glVertex3f(20 * cos(t), 20 * sin(t), t);
	glEnd();

	glEndList();
	// End create a display list.
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
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
	glutCreateWindow("Helix, example of list usage");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
