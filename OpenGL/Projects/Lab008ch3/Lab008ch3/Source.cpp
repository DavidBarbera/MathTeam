#include "Libraries.h"
#include <iostream>

#define VERTICES 0
#define INDICES 1
#define ANNULUS 0
#define TRIANGLE 1

using namespace std;

// Begin globals.
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

// Vertex co-ordinate vectors for the triangle.
static float vertices2[] =
{
	40.0, 40.0, 0.0,
	60.0, 40.0, 0.0,
	60.0, 60.0, 0.0
};

// Vertex color vectors for the triangle.
static float colors2[] =
{
	0.0, 1.0, 1.0,
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0
};

// Triangle strip vertex indices in order.
static unsigned int stripIndices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };

static unsigned int buffer[2]; // Array of buffer ids.

static unsigned int vao[2]; // Array of VAO ids.
// End globals.

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	   // Draw annulus.
	glBindVertexArray(vao[ANNULUS]);
	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, 0);

	// Draw triangle.
	glBindVertexArray(vao[TRIANGLE]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	

	glutSwapBuffers();

}

void setup()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);


	glGenVertexArrays(2, vao); // Generate VAO ids.

							   // BEGIN bind VAO id vao[ANNULUS] to the set of vertex array calls following.
	glBindVertexArray(vao[ANNULUS]);

	glGenBuffers(2, buffer); // Generate buffer ids.

							 // Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1) + sizeof(colors1), NULL, GL_STATIC_DRAW);

	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices1), vertices1);

	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices1), sizeof(colors1), colors1);

	// Bind and fill indices buffer.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(stripIndices), stripIndices, GL_STATIC_DRAW);

	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(vertices1)));
	// END bind VAO id vao[ANNULUS].

	// BEGIN bind VAO id vao[TRIANGLE] to the set of vertex array calls following.
	glBindVertexArray(vao[TRIANGLE]);

	glGenBuffers(1, buffer); // Generate buffer ids.

							 // Enable two vertex arrays: co-ordinates and color.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Bind vertex buffer and reserve space.
	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2) + sizeof(colors2), NULL, GL_STATIC_DRAW);

	// Copy vertex coordinates data into first half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices2), vertices2);

	// Copy vertex color data into second half of vertex buffer.
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices2), sizeof(colors2), colors2);

	// Specify vertex and color pointers to the start of the respective data.
	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(3, GL_FLOAT, 0, (GLvoid*)(sizeof(vertices2)));
	// END bind VAO id vao[TRIANGLE].

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
	glutCreateWindow("Window");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(KeyInput);

	init_glew();

	setup();

	glutMainLoop();

}//main
