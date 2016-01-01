#include "Libraries.h"
#include <iostream>

#define PI 3.14159265

using namespace std;

void helix()
{
	float t;
	float R = 20.0;
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (t = -10 * PI; t <= 10 * PI; t += PI / 20.0)
		glVertex3f(R * cos(t), R * sin(t), t - 60.0);
	// glVertex3f(R * cos(t), t, R * sin(t) - 60.0);
	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	helix();
	
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
	//glOrtho(-50.0, 50.0, -50.0, 50.0, 0.0, 100.0);
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5 , 100.0);
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

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); //(GLUT_DOUBLE | GLUT_RGBA);
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
