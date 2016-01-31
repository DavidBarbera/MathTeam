#include "Libraries.h"
#include <iostream>


// orbit_1.cpp : Starter Code for Orbit Demo 

#include <stdlib.h> 
#include <stdio.h> 

#define INIT_VIEW_X    0.0 
#define INIT_VIEW_Y    0.0 
#define INIT_VIEW_Z   -4.5 
#define VIEW_LEFT     -2.0 
#define VIEW_RIGHT     2.0 
#define VIEW_BOTTOM   -2.0 
#define VIEW_TOP       2.0 
#define VIEW_NEAR      1.0 
#define VIEW_FAR     200.0 

int fullscreen = 0;

GLfloat AmbientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
GLfloat DiffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat SpecularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat SpecRef[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat LightPos[] = { -50.0f,50.0f,100.0f,1.0f };
GLubyte Shine = 128;

float sunrev = 0.0;        // the amount of revolution of the sun
float delsunrev = 0.0;  // the amount of change in the revolution (rotation) per frame of animation
float delang = 0.01;   // the amount of change in the rate of rotation per key press

void SetupRend()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);
	glMateriali(GL_FRONT, GL_SHININESS, Shine);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// transforms and drawing commands go here 
	glRotatef(90.0, 1.0, 0.0, 0.0);      // flip scene 90 degrees about the x-axis
	glColor3ub(120, 120, 30);           // yellow 
	glutWireSphere(0.3, 20, 20);        // sun 
	glPopMatrix();

/*	glRotatef(90.0, 1.0, 0.0, 0.0);

	glRotatef(sunrev, 0.0, 0.0, 1.0);    // revolves the sun on its axis 
	glColor3ub(120, 120, 30);           // set color to yellow 
	glutWireSphere(0.3, 20, 20);        // draw the sun 

	glRotatef(planetorb, 0.0, 0.0, 1.0); // orbits the planet around the sun   
	glTranslatef(1.5, 0.0, 0.0);        // sets the radius of the orbit 
	glRotatef(planetrev, 0.0, 0.0, 1.0); // revolves the planet on its axis 
	glColor3ub(30, 120, 30);          // set color to green 
	glutWireSphere(0.1, 20, 20);        // draw the planet
*/

	glutSwapBuffers();
}

void ChangeWindow(GLsizei w, GLsizei h)
{
	GLfloat Ratio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	Ratio = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, Ratio, VIEW_NEAR, VIEW_FAR);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(INIT_VIEW_X, INIT_VIEW_Y, INIT_VIEW_Z);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}

void CheckRot()
{
	// will be used to keep angles between 0.0 and 360.0 degrees 
	if (sunrev>360.0)
		sunrev -= 360.0;
	if (sunrev<0.0)
		sunrev += 360.0;
}

void SpecialKeys(int key, int x, int y)
{
	// will be used to change rotation angles and rates
	if (key == GLUT_KEY_LEFT)
	{
	/*	delplanetrev += 30.0*delang;
		delmoonorb += 5.0*delang;
		delmoonrev += 50.0*delang;
		delplanetorb += 1.0*delang;*/
		delsunrev += delang;
	}

	if (key == GLUT_KEY_RIGHT)
	{
		/*delplanetrev -= 30.0*delang;
		delmoonorb -= 5.0*delang;
		delmoonrev -= 50.0*delang;
		delplanetorb -= 1.0*delang;*/
		delsunrev -= delang;
	}

	if (key == GLUT_KEY_UP)
	{
		//tilt += 1.0;
	}


	if (key == GLUT_KEY_DOWN)
	{
		//tilt -= 1.0;
	}

	CheckRot();
	glutPostRedisplay();
}

void KeyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f':
		if (fullscreen == 1)
		{
			glutReshapeWindow(320, 240);
			glutPositionWindow(5, 30);
		}
		else
			glutFullScreen();
		fullscreen = 1 - fullscreen;
		break;

	case 'F':
		if (fullscreen == 1)
		{
			glutReshapeWindow(320, 240);
			glutPositionWindow(5, 30);
		}
		else
			glutFullScreen();
		fullscreen = 1 - fullscreen;
		break;

	case 'Q':
		exit(1);
		break;

	case 'q':
		exit(1);
		break;
	}
	glutPostRedisplay();
}

void animate(void)
{
	// motion between frames will be controlled here
	// this function is set to run on idle
	sunrev += delsunrev;
	CheckRot();

	glutPostRedisplay();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // double buffered window 
	glutCreateWindow("Orbit Demo");                        // Graphics Window Title 
	glutReshapeWindow(640, 480);                             // Graphics Window Size 
	SetupRend();                                            // lighting and material properties 
	glutReshapeFunc(ChangeWindow);                         // function to maintain aspect ratios 
	glutKeyboardFunc(KeyPress);                            // function to handle key press 
	glutSpecialFunc(SpecialKeys);                          // function to handle special keys 
	glutDisplayFunc(Display);                              // graphics display function 
	glutIdleFunc(animate);                                  // updates object motions 
	glutMainLoop();                                         // enters the GLUT event processing loop 
}