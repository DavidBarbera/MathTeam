#include "Libraries.h"
#include <iostream>

using namespace std;

void transformations2()
{
	// Modeling transformations.
	glTranslatef(0.0, 0.0, -80.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
	glTranslatef(10.0, 0.0, 0.0);
	
}

void transformations1()
{
	// Modeling transformations.
	glTranslatef(0.0, 0.0, -80.0);
	glTranslatef(10.0, 0.0, 0.0);
	glRotatef(45.0, 0.0, 0.0, 1.0);
}

void transformations()
{
	// Modeling transformations.
	glTranslatef(0.0, 0.0, -40.0);
	glRotatef(60, 1.0, 0.0, 1.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glColor3f(1.0, 1.0, 0.0); //Yellow; the drawing color
	glLoadIdentity();
	transformations2();
	glutSolidTeapot(5.0); 

	//glColor3f(1.0, 0.0, 0.0); //Yellow; the drawing color
	glLoadIdentity();
	transformations1();
	glutSolidTeapot(5.0);

	

	glutSwapBuffers();

}

void setup_solid()
{
	// Material property vectors.
	float matSpec[] = { 0.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };
	float matAmbAndDif[] = { 0.0, 0.1, 1.0, 1.0 };

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.1, 1.0, 1.0 };
	float lightDifAndSpec[] = { 0.0, 0.1, 1.0, 1.0 };
	float lightPos[] = { 0.0, 7.0, 3.0, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Material properties of the objects.
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matAmbAndDif);

	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// Poperties of the ambient light.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	glEnable(GL_LIGHTING); // Enable lighting calculations.
	glEnable(GL_LIGHT0); // Enable particular light source.
	glEnable(GL_DEPTH_TEST); // Enable depth testing.
}
void setup()
{
	setup_solid();
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
    glFrustum(-5.0, 5.0, -5.0, 5.0, 20, 100.0);

	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();

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
	glutCreateWindow("Window");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
