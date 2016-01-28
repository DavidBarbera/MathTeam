#include "Libraries.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

// Globals.
static int isWire = 0; // Is wireframe?


void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// We set the color (before the begin of the whole square)
	//glColor3f(0.0, 0.0, 0.0);

	if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_TRIANGLE_STRIP);
		// First annulus
		glVertex3f(30.0, 30.0, 0.0);
		glVertex3f(10.0, 10.0, 0.0);

		glVertex3f(90.0, 30.0, 0.0);
		glVertex3f(100.0, 10.0, 0.0);	

		glVertex3f(90.0, 70.0, 0.0);
		glVertex3f(100.0, 90.0, 0.0);

		glVertex3f(30.0, 70.0, 0.0);
		glVertex3f(10.0, 90.0, 0.0);

		glVertex3f(30.0, 30.0, 0.0);
		glVertex3f(10.0, 10.0, 0.0);

		glVertex3f(110.0, 30.0, 0.0);
		glVertex3f(100.0, 10.0, 0.0);

		glVertex3f(170.0, 30.0, 0.0);
		glVertex3f(190.0, 10.0, 0.0);

		glVertex3f(170.0, 70.0, 0.0);
		glVertex3f(190.0, 90.0, 0.0);

		glVertex3f(110.0, 70.0, 0.0);
		glVertex3f(100.0, 90.0, 0.0);

		glVertex3f(110.0, 30.0, 0.0);
		glVertex3f(100.0, 10.0, 0.0);

		// Second annulus
		

		

		
	glEnd();

	/*glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3d(40.0, 40.0, 0.0);
		glVertex3d(60.0, 40.0, 0.0);
		glVertex3d(60.0, 60.0, 0.0);
		glVertex3d(40.0, 60.0, 0.0);
	glEnd();*/
	

	glutSwapBuffers();

}

void setup()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200.0, 0, 100.0, -1.0, 1.0);
	//glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	// gluPerspective(90.0, 1.0, 5.0, 100.0);
	// gluPerspective(90.0, (float)w/(float)h, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);

}

void KeyInput(unsigned char key, int x, int y)
{

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

void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press P/p to increase/decrease the number of longitudinal slices." << endl
		<< "Press Q/q to increase/decrease the number of latitudinal slices." << endl
		<< "Press x, X, y, Y, z, Z to turn the hemisphere." << endl;
}

int main(int argv, char** argc)
{
	printInteraction();
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 500);
	glutCreateWindow("Hemisphere, check console for instructions");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
