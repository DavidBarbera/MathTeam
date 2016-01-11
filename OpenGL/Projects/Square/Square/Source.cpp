#include "Libraries.h"
#include <iostream>

#define PI 3.14159265358979324

using namespace std;

// Globals.
//circle
static float R = 40.0; // Radius of circle.
static float X = 50.0; // X-coordinate of center of circle.
static float Y = 50.0; // Y-coordinate of center of circle.
static int num_vertices = 25; // Number of vertices on circle.
//Parabola
static int M = 3; // Number of vertices on one half of the parabola.



void square1()
{
	glColor3f(1.0, 1.0, 0.0); //Yellow; the drawing color
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.5);
	glVertex3f(80.0, 20.0, -0.5);
	glVertex3f(80.0, 80.0, 0.1);
	glVertex3f(20.0, 80.0, 0.2);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(120.0, 120.0, 0.0);
	glVertex3f(180.0, 120.0, 0.0);
	glVertex3f(180.0, 180.0, 0.0);
	glVertex3f(120.0, 180.0, 0.0);
	glEnd();
}

void square2()
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(40.0, 40.0, 0.0);
	glVertex3f(60.0, 40.0, 0.0);
	glVertex3f(60.0, 60.0, 0.0);
	glVertex3f(40.0, 60.0, 0.0);
	glEnd();

}

void square3()
{
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(80.0, 80.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();

}

void square4()
{
	glColor3f(1.0, 1.0, 0.0);
	glPointSize(5.0);
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();
}

void triangle()
{
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 10.2);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glEnd();
}

void lines()
{
	glLineWidth(5.0);
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glEnd();
}

void triangles()
{
	//Set Polygon Modes
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(10.0, 90.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(35.0, 75.0, 0.0);
	glVertex3f(30.0, 20.0, 0.0);
	glVertex3f(90.0, 90.0, 0.0);
	glVertex3f(80.0, 40.0, 0.0);
	glEnd();
}

void triangles2()
{
	//Set Polygon Modes
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(15.0, 90.0, 0.0);
	glVertex3f(55.0, 75.0, 0.0);
	glVertex3f(80.0, 30.0, 0.0);
	glVertex3f(90.0, 10.0, 0.0);
	glEnd();
}

void circle()
{
	float t = 0;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num_vertices; i++)
	{
		glColor3f((float)rand() / (float)RAND_MAX,
			(float)rand() / (float)RAND_MAX,
			(float)rand() / (float)RAND_MAX );
		glVertex3f(X + R*cos(t), Y + R*sin(t), 0.0);
		t += 2 * PI / num_vertices;
	}
	glEnd();
}

void parabola()
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 0.0);

	// The 2M+1 vertices on the parabola are equally spaced in x-coordinates.
	// The parabola is translated and scaled to center it in the window.
	glBegin(GL_LINE_STRIP);
	for (i = -M; i <= M; ++i)
	{
		glVertex3f(50.0 + 50.0 * (float)i / M, 100.0 * (float)(i*i) / (M*M), 0.0);
	}
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	parabola();

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
	case '+':
		num_vertices = num_vertices + 5;
		M++;
		glutPostRedisplay();
		break;
	case '-':
		num_vertices = num_vertices - 5;
		M--;
		glutPostRedisplay();
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
	glutCreateWindow("Square");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
