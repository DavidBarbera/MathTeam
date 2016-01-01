#include "Libraries.h"
#include <iostream>


using namespace std;

// Globals.
static int isWire = 0; // Is wireframe// Vertex co-ordinate vectors.
static float vertices[8][3] =
{
	{ 30.0, 30.0, 0.0 },
	{ 10.0, 10.0, 0.0 },
	{ 70.0, 30.0, 0.0 },
	{ 90.0, 10.0, 0.0 },
	{ 70.0, 70.0, 0.0 },
	{ 90.0, 90.0, 0.0 },
	{ 30.0, 70.0, 0.0 },
	{ 10.0, 90.0, 0.0 }
};

// Vertex color vectors.
static float colors[8][3] =
{
	{ 0.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 1.0, 0.0 },
	{ 1.0, 0.0, 1.0 },
	{ 0.0, 1.0, 1.0 },
	{ 1.0, 0.0, 0.0 }
};

// Triangle strip vertex indices in order.
static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
// End globals.


void draw_thingy()
{
	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(30.0, 30.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(70.0, 30.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(90.0, 10.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(70.0, 70.0, 0.0);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(90.0, 90.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glVertex3f(30.0, 70.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(10.0, 90.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(30.0, 30.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glEnd();
}

void thing2()
{
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 10; ++i)
	{
		glColor3fv(colors[i % 8]);
		glVertex3fv(vertices[i % 8]);
	}
	glEnd();
}

void thing3()
{
	// Draw square annulus.
	glBegin(GL_TRIANGLE_STRIP);
	// The i th vertex in vertices[] and i th color in colors[] are called together by glArrayElement(i).
	for (int i = 0; i < 10; ++i) glArrayElement(i % 8);
	glEnd();
}

void thing4()
{
	// Draw square annulus. glDrawElements() "pulls up" data for 10 vertices in one command -
	// more efficient than calling glArrayElement() 10 times.
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, stripIndices);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	thing4();

	glutSwapBuffers();

}

void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Specify locations for the co-ordinates and color arrays.
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
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
		if (isWire == 0) isWire = 1;
		else isWire = 0;
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
	cout << "Press the space bar to toggle between wireframe and filled." << endl;
}


int main(int argv, char** argc)
{
	printInteraction();
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Press Space Bar to change display mode");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
