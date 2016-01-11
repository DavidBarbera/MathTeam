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
	Point() {};
	void setCoords(int x, int y)
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

// Currently clicked point.
Point currentPoint;

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

	currentPoint.drawPoint();
	

	glutSwapBuffers();

}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y)
{
	// Store the clicked point in the currentPoint variable when left button is pressed.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		currentPoint = Point(x, height - y);

	// Store the currentPoint in the points vector when left button is released.
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		points.push_back(currentPoint);

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(0);

	glutPostRedisplay();
}

// Mouse motion callback routine.
void mouseMotion(int x, int y)
{
	// Update the location of the current point as the mouse moves with button pressed.
	currentPoint.setCoords(x, height - y);

	glutPostRedisplay();
}

void mouseWheel(int wheel, int direction, int x, int y)
{
(direction > 0) ? pointSize++ : pointSize--;
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
	cout << "Left mouse click to draw a square point, keep left button pressed to drag point," << endl
		<< "right mouse click to exit." << endl;
}

int main(int argv, char** argc)
{
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(700, 700);
	glutCreateWindow("Mouse control and motion, check console");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	// Register the mouse callback function.
	glutMouseFunc(mouseControl);

	// Register the mouse motion callback function.
	glutMotionFunc(mouseMotion);

	// Register the mouse wheel callback function.
	glutMouseWheelFunc(mouseWheel);

	init_glew();

	setup();

	glutMainLoop();

}//main
