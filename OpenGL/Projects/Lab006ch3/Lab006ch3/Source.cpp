#include "Libraries.h"
#include <iostream>

using namespace std;

// Begin globals.
static int isWire = 0; // Is wireframe?

					   // Vertex co-ordinate vectors for the annulus.
static float vertices1[] =
{
	30.0, 30.0, 0.0,
	10.0, 10.0, 0.0,
	70.0, 30.0, 0.0,
	90.0, 10.0, 0.0,
	70.0, 70.0, 0.0,
	90.0, 90.0, 0.0,
	30.0, 70.0, 0.0,
	10.0, 90.0, 0.0
};

// Vertex color vectors for the annulus.
static float colors1[] =
{
	0.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 0.0,
	1.0, 0.0, 1.0,
	0.0, 1.0, 1.0,
	1.0, 0.0, 0.0
};

// Intertwined array of vertex co-ordinate and color vectors for the triangle.
static float vertices2AndColors2Intertwined[] =
{
	40.0, 40.0, 0.0, 0.0, 1.0, 1.0,
	60.0, 40.0, 0.0, 1.0, 0.0, 0.0,
	60.0, 60.0, 0.0, 0.0, 1.0, 0.0
};

// Triangle strip vertex indices in order.
static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
// End globals.

void draw_square_annulus()
{
	// The vertex and color array pointers point to the data for the annulus.
	glVertexPointer(3, GL_FLOAT, 0, vertices1);
	glColorPointer(3, GL_FLOAT, 0, colors1);

	// Draw annulus.
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, stripIndices);
}

void draw_triangle()
{
	// The vertex and color array pointers point to the intertwined data for the triangle.
	// The value of the stride parameter is as specified because there are six 
	// floating point values in the intertwined array between the start of 
	// successive co-ordinate or color vectors.
	glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), &vertices2AndColors2Intertwined[0]);
	glColorPointer(3, GL_FLOAT, 6 * sizeof(float), &vertices2AndColors2Intertwined[3]);

	// Draw triangle.
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	draw_square_annulus();
	draw_triangle();

	glutSwapBuffers();

}

void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
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
	glutCreateWindow("Drawing with glDrawArrays and glDrawElements");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
