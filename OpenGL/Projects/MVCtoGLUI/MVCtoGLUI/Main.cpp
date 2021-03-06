/****************************************************************************

A simple GLUT program using the GLUI User Interface Library

This program sets up a checkbox and a spinner, both with live variables.
No callbacks are used.

-----------------------------------------------------------------------

9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/
#pragma once

#include <string.h>
#include "Libraries.h"

//#include "h"
//#include "things.h"
#include "Global.h"
#include "Scene.h"
//#include "teapot.h"             // 3D mesh of teapot
//#include "cameraSimple.h"       // 3D mesh of camera

Scene scene;

int window_width = 1368;
int window_height = 768;

float xy_aspect;
int   last_x, last_y;
float rotationX = 0.0, rotationY = 0.0;

/** These are the live variables passed into GLUI ***/

int   wireframe = 0;
int   obj_type = 1;
int   segments = 8;
int   segments2 = 8;
int   light0_enabled = 1;
int   light1_enabled = 0;
float light0_intensity = 1.0;
float light1_intensity = 1.0;
int   main_window;
float scale = 1.0;
int   show_sphere = 1;
int   show_torus = 1;


/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui;
GLUI_Checkbox   *checkbox;
GLUI_Spinner    *spinner, *light0_spinner, *light1_spinner;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;

/********** User IDs for callbacks ********/
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  251

/********** Miscellaneous global variables **********/

GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat light0_diffuse[] = { .6f, .6f, 1.0f, 1.0f };
GLfloat light0_position[] = { .5f, .5f, 1.0f, 0.0f };

GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat light1_diffuse[] = { .9f, .6f, 0.0f, 1.0f };
GLfloat light1_position[] = { -1.0f, -1.0f, 1.0f, 0.0f };


/**************************************** control_cb() *******************/
/* GLUI control callback                                                 */

void control_cb(int control)
{
	if (control == LIGHT0_ENABLED_ID) {
		if (light0_enabled) {
			glEnable(GL_LIGHT0);
			light0_spinner->enable();
		}
		else {
			glDisable(GL_LIGHT0);
			light0_spinner->disable();
		}
	}
	else if (control == LIGHT1_ENABLED_ID) {
		if (light1_enabled) {
			glEnable(GL_LIGHT1);
			light1_spinner->enable();
		}
		else {
			glDisable(GL_LIGHT1);
			light1_spinner->disable();
		}
	}
	else if (control == LIGHT0_INTENSITY_ID) {
		float v[] = { light0_diffuse[0],  light0_diffuse[1],
			light0_diffuse[2],  light0_diffuse[3] };

		v[0] *= light0_intensity;
		v[1] *= light0_intensity;
		v[2] *= light0_intensity;

		glLightfv(GL_LIGHT0, GL_DIFFUSE, v);
	}
	else if (control == LIGHT1_INTENSITY_ID) {
		float v[] = { light1_diffuse[0],  light1_diffuse[1],
			light1_diffuse[2],  light1_diffuse[3] };

		v[0] *= light1_intensity;
		v[1] *= light1_intensity;
		v[2] *= light1_intensity;

		glLightfv(GL_LIGHT1, GL_DIFFUSE, v);
	}
	
}

/***************************************** myGlutIdle() ***********/

void myGlutIdle(void)
{
	// According to the GLUT specification, the current window is
	//undefined during an idle callback.  So we need to explicitly change
	//it if necessary 
	if (glutGetWindow() != main_window)
		glutSetWindow(main_window);

	glutPostRedisplay();
}


/**************************************** myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
	switch (Key)
	{
	case 27:
	case 'q':
		exit(0);
		break;
	};

	glutPostRedisplay();
}


/***************************************** myGlutMenu() ***********/
void myGlutMenu(int value)
{
	myGlutKeyboard(value, 0, 0);
}
/**************************************** myGlutReshape() *************/

void myGlutReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	scene.setWindowSize(w, h);

	glutPostRedisplay();
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay(void)
{
	scene.draw();
	glutSwapBuffers();
}

void myGlutMotion(int x, int y)
{
	rotationX += (float)(y - last_y);
	rotationY += (float)(x - last_x);

	last_x = x;
	last_y = y;

	scene.rotateCamera(x, y);
	//scene.rotateModel(x, y);

	
 	glutPostRedisplay();
}

void myGlutMouse(int button, int button_state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
		last_x = x;
		last_y = y;
	}
	if (button == GLUT_RIGHT_BUTTON && button_state == GLUT_DOWN) {
		last_x = x;
		last_y = y;
	}
}

void glutWindowSystem(int argc, char* argv[]) {
	/****************************************/
	/*   Initialize GLUT and create window  */
	/****************************************/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(window_width, window_height);
	//setWindowSize(window_width, window_height);
	scene.setViewMatrix(0, 0, 10, 0, 0, 0);
	scene.setModelMatrix(0, 0, 0, 0, 0, 0);

	main_window = glutCreateWindow("MVC to GLUI");
	glutDisplayFunc(myGlutDisplay);
	glutReshapeFunc(myGlutReshape);
	glutKeyboardFunc(myGlutKeyboard);
	glutMotionFunc(myGlutMotion);
	glutMouseFunc(myGlutMouse);

}

void SetupLights()
{
	/****************************************/
	/*       Set up OpenGL lights           */
	/****************************************/

	GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
	GLfloat light0_diffuse[] = { .6f, .6f, 1.0f, 1.0f };
	GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	/****************************************/
	/*          Enable z-buferring          */
	/****************************************/

	glEnable(GL_DEPTH_TEST);
}
/**************************************** main() ********************/

void GluiWindowSystem()
{
	/****************************************/
	/*         Here's the GLUI code         */
	/****************************************/

	printf("GLUI version: %3.2f\n", GLUI_Master.get_version());

	glui = GLUI_Master.create_glui("GLUI", 0, 400, 50); /* name, flags,
														x, and y */

														/*** Add invisible panel to hold rest of controls ***/
	GLUI_Panel *panel1 = new GLUI_Panel(glui, "", GLUI_PANEL_NONE);

	obj_panel = new GLUI_Panel(panel1, "Objects");

	/***** Control for object params *****/

	checkbox =
		new GLUI_Checkbox(obj_panel, "Wireframe", &wireframe, 1, control_cb);
	spinner = new GLUI_Spinner(obj_panel, "Segments:", &segments);
	spinner->set_int_limits(3, 60);
	spinner->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Spinner *scale_spinner =
		new GLUI_Spinner(obj_panel, "Scale:", &scale);
	scale_spinner->set_float_limits(.2f, 4.0);
	scale_spinner->set_alignment(GLUI_ALIGN_RIGHT);

	GLUI_Panel *panel2 = new GLUI_Panel(obj_panel, "", GLUI_PANEL_NONE);
	new GLUI_Checkbox(panel2, "Sphere", &show_sphere);
	new GLUI_Column(panel2);
	new GLUI_Checkbox(panel2, "Torus", &show_torus);


	/*** Start a new column in this panel ***/
	new GLUI_Column(panel1, false); /* 'false' means don't draw bar */


									/******** Add some controls for lights ********/

	GLUI_Panel *light0 = new GLUI_Panel(panel1, "Light 1");
	GLUI_Panel *light1 = new GLUI_Panel(panel1, "Light 2");

	new GLUI_Checkbox(light0, "Enabled", &light0_enabled,
		LIGHT0_ENABLED_ID, control_cb);
	light0_spinner =
		new GLUI_Spinner(light0, "Intensity:",
			&light0_intensity, LIGHT0_INTENSITY_ID,
			control_cb);
	light0_spinner->set_float_limits(0.0, 1.0);

	new GLUI_Checkbox(light1, "Enabled", &light1_enabled,
		LIGHT1_ENABLED_ID, control_cb);
	light1_spinner =
		new GLUI_Spinner(light1, "Intensity:",
			&light1_intensity, LIGHT1_INTENSITY_ID,
			control_cb);
	light1_spinner->set_float_limits(0.0, 1.0);
	light1_spinner->disable();   /* Disable this light initially */


								 /****** A 'quit' button *****/

	new GLUI_Button(glui, "Quit", 0, (GLUI_Update_CB)exit);


	/**** Link windows to GLUI ******/

	glui->set_main_gfx_window(main_window);

}



int main(int argc, char* argv[])
{
	 
	glutWindowSystem(argc, argv);

	//SetupLights();
	scene.init();

	GluiWindowSystem();
	
	glutMainLoop();

	return EXIT_SUCCESS;
}



