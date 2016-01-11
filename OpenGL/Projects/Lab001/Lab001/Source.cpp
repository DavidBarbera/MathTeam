#include "Libraries.h"
#include <iostream>

#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

using namespace std;

// Globals.
static int isWire = 0; // Is wireframe?
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24; // Font selection.


// Routine to draw a bitmap character string.
void writeBitmapString(void *font, char *string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void drawDisc(float R, float X, float Y, float Z)
{
	float t;
	int i;

	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X, Y, Z);
	for (i = 0; i <= N; ++i)
	{
		t = 2 * PI * i / N;
		glVertex3f(X + cos(t) * R, Y + sin(t) * R, Z);
	}
	glEnd();
}

void draw_thing()
{
	float angle;
	int i;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers including 
														// the depth buffer.

	glPolygonMode(GL_FRONT, GL_FILL);

	// Upper left circular annulus: the white disc overwrites the red disc.
	glColor3f(1.0, 0.0, 0.0);
	drawDisc(20.0, 25.0, 75.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawDisc(10.0, 25.0, 75.0, 0.0);

	// Upper right circular annulus: the white disc is in front of the red disc blocking it.
	glEnable(GL_DEPTH_TEST); // Enable depth testing. 
	glColor3f(1.0, 0.0, 0.0);
	drawDisc(20.0, 75.0, 75.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	drawDisc(10.0, 75.0, 75.0, 0.5); // Compare this z-value with that of the red disc.
	glDisable(GL_DEPTH_TEST); // Disable depth testing.

							  // Lower circular annulus: with a true hole.
	if (isWire) glPolygonMode(GL_FRONT, GL_LINE); else glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i <= N; ++i)
	{
		angle = 2 * PI * i / N;
		glVertex3f(50 + cos(angle) * 10.0, 30 + sin(angle) * 10.0, 0.0);
		glVertex3f(50 + cos(angle) * 20.0, 30 + sin(angle) * 20.0, 0.0);
	}
	glEnd();

	// Write labels.
	glColor3f(1.0, 1.0, 0.0);
	glRasterPos3f(15.0, 51.0, 0.0);
	writeBitmapString((void*)font, "Overwritten");
	glRasterPos3f(69.0, 51.0, 0.0);
	writeBitmapString((void*)font, "Floating");
	glRasterPos3f(38.0, 6.0, 0.0);
	writeBitmapString((void*)font, "The real deal!");

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	draw_thing();
	
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
	glutCreateWindow("Lab001");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
