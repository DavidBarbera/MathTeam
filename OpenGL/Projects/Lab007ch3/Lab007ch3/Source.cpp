#include "Libraries.h"
#include <iostream>

#define VERTICES 0
#define INDICES 1

using namespace std;

// Begin globals.
// Vertex co-ordinate vectors.
static float vertices[] =
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

// Vertex color vectors.
static float colors[] =
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

// Triangle strip vertex indices in order.
static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };

static unsigned int buffer[2]; // Array of buffer ids.
							   // End globals.

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Get a pointer to the vertex buffer.
	float* bufferData = (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	// Randomly change the color values.
	for (int i = 0; i < sizeof(colors) / sizeof(float); i++)
		bufferData[sizeof(vertices) / sizeof(float) + i] = (float)rand() / (float)RAND_MAX;

	// Release the vertex buffer.
	glUnmapBuffer(GL_ARRAY_BUFFER);

	// Draw square annulus.
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);
	

	glutSwapBuffers();

}

// Timer function.
void animate(int someValue)
{
	glutPostRedisplay();
	glutTimerFunc(500, animate, 1);
}

void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

//-------------------------------------  VBO -----------------------------
	// Generate buffer ids.
	glGenBuffers(2, buffer);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);// binding buffer Id to a Vertex attributes buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);

	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);//buffering vertices

	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors); //buffering colors

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]); // binding buffer Id to a Vertex array indices buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);//buffering indices
//-------------------------------------  VBO -----------------------------

	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(vertices)));

	glutTimerFunc(5, animate, 1);
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
	glutCreateWindow("Vertex Buffer Object usage example");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
