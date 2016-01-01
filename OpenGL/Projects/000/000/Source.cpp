#include "Libraries.h"
#include <iostream>
/*
#include <stdio.h>
#include <string.h>
#include <vector>

#include <windows.h>
#include <mmsystem.h>
*/

void main(int argv, char** argc) {

	glutInit(&argv, argc);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1380, 780);
	glutCreateWindow("Hey there, check the console window for info about your supported OpenGL version and extensions. Press 'Enter' to leave");

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error initializing GLEW: %s\n",
			glewGetErrorString(err));
	}

	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion =
		glGetString(GL_SHADING_LANGUAGE_VERSION);
	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("GL Vendor : %s\n", vendor);
	printf("GL Renderer : %s\n", renderer);
	printf("GL Version (string) : %s\n", version);
	printf("GL Version (integer) : %d.%d\n", major, minor);
	printf("GLSL Version : %s\n", glslVersion);

	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
	for (int i = 0; i < nExtensions; i++)
		printf("%i : %s\n", i, glGetStringi(GL_EXTENSIONS, i));


	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;			//std::cout << "GL_EXTENSIONS: " << glGetString(GL_EXTENSIONS) << std::endl;
	std::cout << "GL_RENDERER: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL_VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GLU_VERSION: " << gluGetString(GLU_VERSION) << std::endl;			//std::cout << "GLU_EXTENSIONS: " << gluGetString(GLU_EXTENSIONS) << std::endl;
	std::cout << "GLUT_API_VERSION: " << GLUT_API_VERSION << std::endl;


	getchar();

}