#include "Libraries.h"
#include <iostream>
#include <vector>

// Use the STL extension of C++.
using namespace std;

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 3.0; // Size of point

							  // Point class.
class Point
{
public:
	Point(int x, int y)
	{
		xVal = x; yVal = y;
	}
	void drawPoint(void); // Function to draw a point.
private:
	int xVal, yVal; // x and y co-ordinates of point.
	static float size; // Size of point.
};

float Point::size = pointSize; // Set point size.

							   // Function to draw a point.
void Point::drawPoint(void)
{
	glPointSize(size);
	glBegin(GL_POINTS);
	glVertex3f(xVal, yVal, 0.0);
	glEnd();
}

// Vector of points.
vector<Point> points;

// Iterator to traverse a Point array.
vector<Point>::iterator pointsIterator;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 0.0); //Yellow; the drawing color

	// Loop through the points array drawing each point.
	pointsIterator = points.begin();
	while (pointsIterator != points.end())
	{
		pointsIterator->drawPoint();
		pointsIterator++;
	}
	

	glutSwapBuffers();

}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)

		// Store the clicked point in the points array after correcting
		// from event to OpenGL co-ordinates.
		points.push_back(Point(x, height - y));

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);

	glutPostRedisplay();
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
	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;
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

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	cout << "Interaction:" << endl;
	cout << "Left mouse click to draw a square point, right mouse click to exit." << endl;
}

int main(int argv, char** argc)
{
	printInteraction();
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Using a Mouse with OpenGL and FreeGLUT, check console");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	// Register the mouse callback function. 
	glutMouseFunc(mouseControl);

	init_glew();

	setup();

	glutMainLoop();

}//main
