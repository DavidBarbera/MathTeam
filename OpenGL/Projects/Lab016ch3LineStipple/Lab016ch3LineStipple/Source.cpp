#include "Libraries.h"
#include <iostream>

using namespace std;

// Globals.
static int stippleID = 0; // Stipple ID.
static long font = (long)GLUT_BITMAP_8_BY_13; // Font selection.

											  // Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);

	glEnable(GL_LINE_STIPPLE); // Enable line stippling.

							   // Speficy the stipple pattern and write a label.
	glRasterPos3f(30.0, 40.0, 0.0);
	switch (stippleID)
	{
	case 0:
		glDisable(GL_LINE_STIPPLE);
		writeBitmapString((void*)font, "No stipple");
		break;
	case 1:
		glLineStipple(1, 0x5555);
		writeBitmapString((void*)font, "glLineStipple(1, 0x5555)");
		break;
	case 2:
		glLineStipple(1, 0x0101);
		writeBitmapString((void*)font, "glLineStipple(1, 0x0101)");
		break;
	case 3:
		glLineStipple(1, 0x00FF);
		writeBitmapString((void*)font, "glLineStipple(1, 0x00FF)");
		break;
	case 4:
		glLineStipple(5, 0x5555);
		writeBitmapString((void*)font, "glLineStipple(5, 0x5555)");
		break;
	default:
		break;
	}

	// Draw one straight line segment.
	glBegin(GL_LINES);
	glVertex3f(25.0, 50.0, 0.0);
	glVertex3f(75.0, 50.0, 0.0);
	glEnd();

	glDisable(GL_LINE_STIPPLE); // Disable line stippling.
	

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

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		if (stippleID < 4) stippleID++;
		else stippleID = 0;
		glutPostRedisplay();
		break;
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

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Press the space bar to cycle between stipples." << endl;
}

int main(int argv, char** argc)
{
	printInteraction();
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Line Stipple types in FreeGLUT, check console");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
