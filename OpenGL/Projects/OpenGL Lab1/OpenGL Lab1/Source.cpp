#include "Libraries.h"
#include <iostream>

using namespace std;

// Globals.
static float square_color[3] = { 1.0, 0.0, 0.0 }; // Color of the square.

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3fv(square_color);
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();

	glutSwapBuffers();

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

// The top menu callback function.
void top_menu(int id)
{
	if (id == 1) exit(0);
}

// The sub-menu callback function.
void color_menu(int id)
{
	if (id == 2)
	{
		square_color[0] = 1.0; square_color[1] = 0.0; square_color[2] = 0.0;
	}
	if (id == 3)
	{
		square_color[0] = 0.0; square_color[1] = 0.0; square_color[2] = 1.0;
	}
	glutPostRedisplay();
}

// Routine to make the menu.
void makeMenu(void)
{
	// The sub-menu is created first (because it should be visible when the top
	// menu is created): its callback function is registered and menu entries added.
	int sub_menu;
	sub_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Blue", 3);

	// The top menu is created: its callback function is registered and menu entries,
	// including a submenu, added.
	glutCreateMenu(top_menu);
	glutAddSubMenu("Color", sub_menu);
	glutAddMenuEntry("Quit", 1);

	// The menu is attached to a mouse button.
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Make menu.
	makeMenu();
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
	cout << "Press the right mouse button to see options." << endl;
}

int main(int argv, char** argc)
{
	printInteraction();
	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
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
