#include "Libraries.h"
#include <iostream>

using namespace std;

// Globals.
static float Xvalue = 0.0, Yvalue = 0.0; // Co-ordinates of the sphere.
static float Angle = 0.0; // Angle to rotate the sphere.

void sphere()
{
	glLoadIdentity();

	// Set the position of the sphere.
	glTranslatef(Xvalue, Yvalue, -5.0);
	glRotatef(Angle, 1.0, 1.0, 1.0);

	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(0.5, 16, 10);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	sphere();

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
	//glOrtho(-5.0, 5.0, -5.0, 5.0, -10.0, 20.0);
	glFrustum(-1, 1, -1, 1, 1.5, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		Xvalue = Yvalue = Angle = 0.0;
		glutPostRedisplay();
		break;
	case 'A':
		Angle += 10.0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_UP) Yvalue += 0.5;
	if (key == GLUT_KEY_DOWN) Yvalue -= 0.5;
	if (key == GLUT_KEY_LEFT) Xvalue -= 0.5;
	if (key == GLUT_KEY_RIGHT) Xvalue += 0.5;
	glutPostRedisplay();
}

void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press the arrow keys to move the sphere." << endl
		<< "Press the space bar to rotate the sphere." << endl
		<< "Press r to reset." << endl;
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
	//Init freeGLUT library
	glutInit(&argv, argc);
	//Set OpenGL to version 4.3 with backward compatibility
	//where legacy commands are implemented
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("The Sphere");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);
	// Register the callback function for non-ASCII key entry.
	glutSpecialFunc(specialKeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
