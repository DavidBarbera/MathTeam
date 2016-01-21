#include "viewer.h"
#include "core.h"

// Global Variables, use as few as possible :)
Viewer *mainWindow;

// Function Declarations
// Glut requires that we use global/static functions so we declare a few below
void glutKeyboardCallback( unsigned char key, int x, int y ) 
{ mainWindow->keyboardInput(key,x,y); }

void glutMouseButtonCallback(int buttonType, int buttonState, int x, int y )
{ mainWindow->mouseButton(buttonType,buttonState,x,y); }

void glutMouseMotionCallback(int x, int y )
{ mainWindow->mouseMotion(x,y); }

void glutDisplayCallback(void)
{ mainWindow->draw(); }

void glutIdleCallback(void)
{ mainWindow->idle(); }

void glutReshapeCallback(int w, int h)
{ mainWindow->reshape(w,h); }

int main(int argc,char** argv)
{
	glutInit(&argc,argv);

	mainWindow = new Viewer("Basic Viewer",512,512);
	
	glutKeyboardFunc( glutKeyboardCallback );
	glutMouseFunc( glutMouseButtonCallback );
	glutMotionFunc( glutMouseMotionCallback );

	glutIdleFunc( glutIdleCallback );
	glutReshapeFunc( glutReshapeCallback );
	glutDisplayFunc( glutDisplayCallback);

	glutMainLoop();
	delete mainWindow;
	return 0;
}
