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
#include "Matrices.h"

#include "teapot.h"             // 3D mesh of teapot
#include "cameraSimple.h"       // 3D mesh of camera

// Globals.
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Euler angles.
Matrix4 matrixData; // Rotation matrix values.
static float t = 0.0; // Interpolation parameter.
static int isAnimate = 0; // Animated?
static int animationPeriod = 100; // Time interval between frames.


								  /** These are the live variables passed into GLUI ***/
								  //int   wireframe = 0;
								  //int   segments = 8;
								  //int   main_window;

int window_width = 1368;
int window_height = 768;

float xy_aspect;
int   last_x, last_y;
float rotationX = 0.0, rotationY = 0.0;

/** These are the live variables passed into GLUI ***/
int   wireframe = 0;
int   active = 0;
int   obj = 0;
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

// Using a std::string as a live variable is safe.
std::string text = "Hello World!";

// Using a char buffer as a live var is also possible, but it is dangerous 
// because GLUI doesn't know how big your buffer is.  
// But still, it works as long as text doesn't happen to overflow.
//char  text[200] = {"Hello World!"};

GLUI_Checkbox   *checkbox;
GLUI_Spinner    *spinner, *spinnerCamera[6], *spinnerModel[6];
GLUI_RadioGroup *radio1;
GLUI_RadioGroup *radio2;
GLUI_EditText   *edittext;

/*----spinners for camera control----*/
int spcameraX(0), spcameraY(0), spcameraZ(10), spcameraPitch(0), spcameraHeading(0), spcameraRoll(0);
/*--- spinners for model control ----*/
int spmodelX(0), spmodelY(0), spmodelZ(0), spmodelPitch(0), spmodelHeading(0), spmodelRoll(0);

/********** User IDs for callbacks ********/
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  251

/********** Miscellaneous global variables **********/
/*
GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat light0_diffuse[] = { .6f, .6f, 1.0f, 1.0f };
GLfloat light0_position[] = { .5f, .5f, 1.0f, 0.0f };

GLfloat light1_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
GLfloat light1_diffuse[] = { .9f, .6f, 0.0f, 1.0f };
GLfloat light1_position[] = { -1.0f, -1.0f, 1.0f, 0.0f };
*/
// constants
const float DEG2RAD = 3.141593f / 180;
const float FOV_Y = 60.0f;              // vertical FOV in degree
const float NEAR_PLANE = 1.0f;
const float FAR_PLANE = 100.0f;
const float CAMERA_ANGLE_X = 45.0f;     // pitch in degree
const float CAMERA_ANGLE_Y = -45.0f;    // heading in degree
const float CAMERA_DISTANCE = 25.0f;    // camera distance

int windowWidth(0);
int windowHeight(0);
bool windowSizeChanged(false);
bool drawModeChanged(false);
int drawMode(0);
int mouseX;
int mouseY;
float cameraPosition[3];
float cameraAngle[3];
float modelPosition[3];
float modelAngle[3];

// these are for 3rd person view
float cameraAngleX(-CAMERA_ANGLE_X);
float cameraAngleY(-CAMERA_ANGLE_Y);
float cameraDistance(CAMERA_DISTANCE);
float bgColor[4];
float modelAngleX(0);
float modelAngleY(0);
float cameraModelAngleX(0);
float cameraModelAngleY(0);


// 4x4 transform matrices
Matrix4 matrixView;
Matrix4 matrixModel;
Matrix4 matrixModelView;
Matrix4 matrixProjection;

//-----------------------------------Quaternions section-------------------------------------------------------

#define PI 3.14159265

// Quaternion class.
class Quaternion
{
public:
	Quaternion() { }
	Quaternion(float wVal, float xVal, float yVal, float zVal)
	{
		w = wVal; x = xVal; y = yVal; z = zVal;
	}
	float getW() { return w; }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }

private:
	float w, x, y, z;
};

static Quaternion identityQuaternion(1.0, 0.0, 0.0, 0.0), q; // Global identity quaternion.

															 // Euler angles class.
class EulerAngles
{
public:
	EulerAngles() { }
	EulerAngles(float alphaVal, float betaVal, float gammaVal)
	{
		alpha = alphaVal; beta = betaVal; gamma = gammaVal;
	}
	float getAlpha() { return alpha; }
	float getBeta() { return beta; }
	float getGamma() { return gamma; }

private:
	float alpha, beta, gamma;
};

static EulerAngles e; // Global Eular angle value.

					  // Rotation matrix class.
class RotationMatrix
{
public:
	RotationMatrix() { }
	RotationMatrix(float matrixDataVal[16])
	{
		for (int i = 0; i < 16; i++) matrixData[i] = matrixDataVal[i];
	}
	float getMatrixData(int i) { return matrixData[i]; }

private:
	float matrixData[16];
};

// Routine to multiply two quaternions.
Quaternion multiplyQuaternions(Quaternion q1, Quaternion q2)
{
	float w1, x1, y1, z1, w2, x2, y2, z2, w3, x3, y3, z3;

	w1 = q1.getW(); x1 = q1.getX(); y1 = q1.getY(); z1 = q1.getZ();
	w2 = q2.getW(); x2 = q2.getX(); y2 = q2.getY(); z2 = q2.getZ();

	w3 = w1*w2 - x1*x2 - y1*y2 - z1*z2;
	x3 = w1*x2 + x1*w2 + y1*z2 - z1*y2;
	y3 = w1*y2 + y1*w2 + z1*x2 - x1*z2;
	z3 = w1*z2 + z1*w2 + x1*y2 - y1*x2;

	return *new Quaternion(w3, x3, y3, z3);
}

// Routine to convert the Euler angle specifying a rotation to a quaternion. 
Quaternion eulerAnglesToQuaternion(EulerAngles e)
{
	float alpha, beta, gamma;
	Quaternion *q1, *q2, *q3;

	alpha = e.getAlpha(); beta = e.getBeta(); gamma = e.getGamma();

	q1 = new Quaternion(cos((PI / 180.0) * (alpha / 2.0)), sin((PI / 180.0) * (alpha / 2.0)), 0.0, 0.0);
	q2 = new Quaternion(cos((PI / 180.0) * (beta / 2.0)), 0.0, sin((PI / 180.0) * (beta / 2.0)), 0.0);
	q3 = new Quaternion(cos((PI / 180.0) * (gamma / 2.0)), 0.0, 0.0, sin((PI / 180.0) * (gamma / 2.0)));

	return multiplyQuaternions(*q1, multiplyQuaternions(*q2, *q3));
}

// Routine to convert a quaternion specifying a rotation to a 4x4 rotation matrix in column-major order.
Matrix4 quaternionToRotationMatrix(Quaternion q)
{
	float w, x, y, z;
	float m[16];

	w = q.getW(); x = q.getX(); y = q.getY(); z = q.getZ();

	m[0] = w*w + x*x - y*y - z*z;
	m[1] = 2.0*x*y + 2.0*w*z;
	m[2] = 2.0*x*z - 2.0*y*w;
	m[3] = 0.0;
	m[4] = 2.0*x*y - 2.0*w*z;
	m[5] = w*w - x*x + y*y - z*z;
	m[6] = 2.0*y*z + 2.0*w*x;
	m[7] = 0.0;
	m[8] = 2.0*x*z + 2.0*w*y;
	m[9] = 2.0*y*z - 2.0*w*x;
	m[10] = w*w - x*x - y*y + z*z;
	m[11] = 0.0;
	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = 0.0;
	m[15] = 1.0;

	return m;
}

// Read global Euler angle values to global EulerAngles object e.
void readEulerAngles(EulerAngles *e)
{
	*e = *new EulerAngles(Xangle, Yangle, Zangle);
}

// Write RotationMatrix object r values to global matrixData.
void writeMatrixData(Matrix4 r)
{
	//for (int i = 0; i < 16; i++)
	matrixData = r;
}

// Spherical linear interpolation between unit quaternions q1 and q2 with interpolation parameter t.
Quaternion slerp(Quaternion q1, Quaternion q2, float t)
{
	float w1, x1, y1, z1, w2, x2, y2, z2, w3, x3, y3, z3;
	Quaternion q2New;
	float theta, mult1, mult2;

	w1 = q1.getW(); x1 = q1.getX(); y1 = q1.getY(); z1 = q1.getZ();
	w2 = q2.getW(); x2 = q2.getX(); y2 = q2.getY(); z2 = q2.getZ();

	// Reverse the sign of q2 if q1.q2 < 0.
	if (w1*w2 + x1*x2 + y1*y2 + z1*z2 < 0)
	{
		w2 = -w2; x2 = -x2; y2 = -y2; z2 = -z2;
	}

	theta = acos(w1*w2 + x1*x2 + y1*y2 + z1*z2);

	if (theta > 0.000001)
	{
		mult1 = sin((1 - t)*theta) / sin(theta);
		mult2 = sin(t*theta) / sin(theta);
	}

	// To avoid division by 0 and by very small numbers the approximation of sin(angle)
	// by angle is used when theta is small (0.000001 is chosen arbitrarily).
	else
	{
		mult1 = 1 - t;
		mult2 = t;
	}

	w3 = mult1*w1 + mult2*w2;
	x3 = mult1*x1 + mult2*x2;
	y3 = mult1*y1 + mult2*y2;
	z3 = mult1*z1 + mult2*z2;

	return *new Quaternion(w3, x3, y3, z3);
}

//---------------------------------------------------------------------------------------------------------------
/*glm::mat4 matrixView = glm::mat4(1.0f);
glm::mat4 matrixModel = glm::mat4(1.0f);;
glm::mat4 matrixModelView = glm::mat4(1.0f);
glm::mat4 matrixProjection = glm::mat4(1.0f);*/


/*
void initScene()
{
cameraPosition[0] = cameraPosition[1] = 0;
cameraPosition[2] = -10;
cameraAngle[0] = cameraAngle[1] = cameraAngle[2] = 0;
modelPosition[0] = modelPosition[1] = modelPosition[2] = 0;
modelAngle[0] = modelAngle[1] = modelAngle[2] = 0;
bgColor[0] = bgColor[1] = bgColor[2] = bgColor[3] = 0;

cameraAngleX = cameraAngleY = 0;

matrixView = glm::mat4(1.0f);
matrixModel = glm::mat4(1.0f);
matrixModelView = glm::mat4(1.0f);
matrixProjection = glm::mat4(1.0f);
}
*/




///////////////////////////////////////////////////////////////////////////////
// initialize lights
///////////////////////////////////////////////////////////////////////////////
void initLights()
{
	// set up light colors (ambient, diffuse, specular)
	GLfloat lightKa[] = { .0f, .0f, .0f, 1.0f };      // ambient light
	GLfloat lightKd[] = { .9f, .9f, .9f, 1.0f };      // diffuse light
	GLfloat lightKs[] = { 1, 1, 1, 1 };               // specular light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

	// position the light in eye space
	float lightPos[4] = { 0, 1, 1, 0 };               // directional light
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);                            // MUST enable each light source after configuration
}

///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL states and scene
///////////////////////////////////////////////////////////////////////////////
void init()
{

	// Initialize global matrixData.
	for (int i = 0; i < 16; i++) matrixData[i] = 0.0;
	matrixData[0] = matrixData[5] = matrixData[10] = matrixData[15] = 1.0;

	glShadeModel(GL_SMOOTH);                        // shading method: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);          // 4-byte pixel alignment

													// enable/disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_SCISSOR_TEST);

	// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);   // background color
	glClearStencil(0);                              // clear stencil buffer
	glClearDepth(1.0f);                             // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);

	//initScene();
	initLights();
}







///////////////////////////////////////////////////////////////////////////////
// set camera position and lookat direction
///////////////////////////////////////////////////////////////////////////////
void setCamera(float posX, float posY, float posZ, float targetX, float targetY, float targetZ)
{
	float forward[4];
	float up[4];
	float left[4];
	float position[4];
	float invLength;

	// determine forward vector (direction reversed because it is camera)
	forward[0] = posX - targetX;    // x
	forward[1] = posY - targetY;    // y
	forward[2] = posZ - targetZ;    // z
	forward[3] = 0.0f;              // w
									// normalize it without w-component
	invLength = 1.0f / sqrtf(forward[0] * forward[0] + forward[1] * forward[1] + forward[2] * forward[2]);
	forward[0] *= invLength;
	forward[1] *= invLength;
	forward[2] *= invLength;

	// assume up direction is straight up
	up[0] = 0.0f;   // x
	up[1] = 1.0f;   // y
	up[2] = 0.0f;   // z
	up[3] = 0.0f;   // w

					// compute left vector with cross product
	left[0] = up[1] * forward[2] - up[2] * forward[1];  // x
	left[1] = up[2] * forward[0] - up[0] * forward[2];  // y
	left[2] = up[0] * forward[1] - up[1] * forward[0];  // z
	left[3] = 1.0f;                                 // w

													// re-compute orthogonal up vector
	up[0] = forward[1] * left[2] - forward[2] * left[1];    // x
	up[1] = forward[2] * left[0] - forward[0] * left[2];    // y
	up[2] = forward[0] * left[1] - forward[1] * left[0];    // z
	up[3] = 0.0f;                                       // w

														// camera position
	position[0] = -posX;
	position[1] = -posY;
	position[2] = -posZ;
	position[3] = 1.0f;

	// copy axis vectors to matrix
	matrixView.identity();
	matrixView.setColumn(0, left);
	matrixView.setColumn(1, up);
	matrixView.setColumn(2, forward);
	matrixView.setColumn(3, position);
}


///////////////////////////////////////////////////////////////////////////////
// set rendering window size
///////////////////////////////////////////////////////////////////////////////
void setWindowSize(int width, int height)
{
	// assign the width/height of viewport
	windowWidth = width;
	windowHeight = height;
	windowSizeChanged = true;
}

///////////////////////////////////////////////////////////////////////////////
// set a perspective frustum with 6 params similar to glFrustum()
// (left, right, bottom, top, near, far)
// Note: this is for row-major notation. OpenGL needs transpose it
///////////////////////////////////////////////////////////////////////////////
void setFrustum(float l, float r, float b, float t, float n, float f)
{
	/*	matrixProjection = glm::mat4(1.0f);
	matrixProjection[0][0] = 2 * n / (r - l);
	matrixProjection[0][2] = (r + l) / (r - l);
	matrixProjection[1][1] = 2 * n / (t - b);
	matrixProjection[1][2] = (t + b) / (t - b);
	matrixProjection[2][2] = -(f + n) / (f - n);
	matrixProjection[2][3] = -(2 * f * n) / (f - n);
	matrixProjection[3][2] = -1;
	matrixProjection[3][3] = 0;*/
	matrixProjection.identity();
	matrixProjection[0] = 2 * n / (r - l);
	matrixProjection[2] = (r + l) / (r - l);
	matrixProjection[5] = 2 * n / (t - b);
	matrixProjection[6] = (t + b) / (t - b);
	matrixProjection[10] = -(f + n) / (f - n);
	matrixProjection[11] = -(2 * f * n) / (f - n);
	matrixProjection[14] = -1;
	matrixProjection[15] = 0;
}

///////////////////////////////////////////////////////////////////////////////
// set a orthographic frustum with 6 params similar to glOrtho()
// (left, right, bottom, top, near, far)
// Note: this is for row-major notation. OpenGL needs transpose it
///////////////////////////////////////////////////////////////////////////////
void setOrthoFrustum(float l, float r, float b, float t, float n, float f)
{
	/*matrixProjection = glm::mat4(1.0f);
	matrixProjection[0][0] = 2 / (r - l);
	matrixProjection[0][3] = -(r + l) / (r - l);
	matrixProjection[1][1] = 2 / (t - b);
	matrixProjection[1][3] = -(t + b) / (t - b);
	matrixProjection[2][2] = -2 / (f - n);
	matrixProjection[2][3] = -(f + n) / (f - n);*/
	matrixProjection.identity();
	matrixProjection[0] = 2 / (r - l);
	matrixProjection[3] = -(r + l) / (r - l);
	matrixProjection[5] = 2 / (t - b);
	matrixProjection[7] = -(t + b) / (t - b);
	matrixProjection[10] = -2 / (f - n);
	matrixProjection[11] = -(f + n) / (f - n);
}

///////////////////////////////////////////////////////////////////////////////
// set a symmetric perspective frustum with 4 params similar to gluPerspective
// (vertical field of view, aspect ratio, near, far)
///////////////////////////////////////////////////////////////////////////////
void setFrustum(float fovY, float aspectRatio, float front, float back)
{
	float tangent = tanf(fovY / 2 * DEG2RAD);   // tangent of half fovY
	float height = front * tangent;           // half height of near plane
	float width = height * aspectRatio;       // half width of near plane

											  // params: left, right, bottom, top, near, far
	setFrustum(-width, width, -height, height, front, back);
}

///////////////////////////////////////////////////////////////////////////////
// configure projection and viewport
///////////////////////////////////////////////////////////////////////////////
void setViewport(int x, int y, int w, int h)
{
	// set viewport to be the entire window
	glViewport((GLsizei)x, (GLsizei)y, (GLsizei)w, (GLsizei)h);
	//	glScissor((GLsizei)x, (GLsizei)y, (GLsizei)w, (GLsizei)h);


	// set perspective viewing frustum
	setFrustum(FOV_Y, (float)(w) / h, NEAR_PLANE, FAR_PLANE); // FOV, AspectRatio, NearClip, FarClip

															  // copy projection matrix to OpenGL
	glMatrixMode(GL_PROJECTION);
	/*glLoadMatrixf(glm::value_ptr(matrixProjection));*/
	glLoadMatrixf(matrixProjection.getTranspose());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



///////////////////////////////////////////////////////////////////////////////
// configure projection and viewport of sub window
///////////////////////////////////////////////////////////////////////////////
void setViewportSub(int x, int y, int width, int height, float nearPlane, float farPlane)
{
	// set viewport
	glViewport(x, y, width, height);
	glScissor(x, y, width, height);

	// set perspective viewing frustum
	setFrustum(FOV_Y, (float)(width) / height, nearPlane, farPlane); // FOV, AspectRatio, NearClip, FarClip

																	 //glEnable(GL_SCISSOR_TEST);

																	 // copy projection matrix to OpenGL
	glMatrixMode(GL_PROJECTION);
	/*	glLoadMatrixf(glm::value_ptr(matrixProjection));*/
	glLoadMatrixf(matrixProjection.getTranspose());
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

///////////////////////////////////////////////////////////////////////////////
// draw a grid on the xz plane
///////////////////////////////////////////////////////////////////////////////
void drawGrid(float size, float step)
{
	// disable lighting
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);

	glColor3f(0.3f, 0.3f, 0.3f);
	for (float i = step; i <= size; i += step)
	{
		glVertex3f(-size, 0, i);   // lines parallel to X-axis
		glVertex3f(size, 0, i);
		glVertex3f(-size, 0, -i);   // lines parallel to X-axis
		glVertex3f(size, 0, -i);

		glVertex3f(i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(i, 0, size);
		glVertex3f(-i, 0, -size);   // lines parallel to Z-axis
		glVertex3f(-i, 0, size);
	}

	// x-axis
	glColor3f(0.5f, 0, 0);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);

	// z-axis
	glColor3f(0, 0, 0.5f);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);

	glEnd();

	// enable lighting back
	glEnable(GL_LIGHTING);
}



///////////////////////////////////////////////////////////////////////////////
// draw the local axis of an object
///////////////////////////////////////////////////////////////////////////////
void drawAxis(float size)
{
	glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
	glDisable(GL_LIGHTING);
	glPushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
								//      the light position when you draw GL_LINES
								//      and GL_POINTS. remember the matrix.

								// draw axis
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();
	glLineWidth(1);

	// draw arrows(actually big square dots)
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	glVertex3f(size, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, size, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, size);
	glEnd();
	glPointSize(1);

	// restore default settings
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
}



///////////////////////////////////////////////////////////////////////////////
// draw frustum
///////////////////////////////////////////////////////////////////////////////
void drawFrustum(float fovY, float aspectRatio, float nearPlane, float farPlane)
{
	float tangent = tanf(fovY / 2 * DEG2RAD);
	float nearHeight = nearPlane * tangent;
	float nearWidth = nearHeight * aspectRatio;
	float farHeight = farPlane * tangent;
	float farWidth = farHeight * aspectRatio;

	// compute 8 vertices of the frustum
	float vertices[8][3];
	// near top right
	vertices[0][0] = nearWidth;     vertices[0][1] = nearHeight;    vertices[0][2] = -nearPlane;
	// near top left
	vertices[1][0] = -nearWidth;    vertices[1][1] = nearHeight;    vertices[1][2] = -nearPlane;
	// near bottom left
	vertices[2][0] = -nearWidth;    vertices[2][1] = -nearHeight;   vertices[2][2] = -nearPlane;
	// near bottom right
	vertices[3][0] = nearWidth;     vertices[3][1] = -nearHeight;   vertices[3][2] = -nearPlane;
	// far top right
	vertices[4][0] = farWidth;      vertices[4][1] = farHeight;     vertices[4][2] = -farPlane;
	// far top left
	vertices[5][0] = -farWidth;     vertices[5][1] = farHeight;     vertices[5][2] = -farPlane;
	// far bottom left
	vertices[6][0] = -farWidth;     vertices[6][1] = -farHeight;    vertices[6][2] = -farPlane;
	// far bottom right
	vertices[7][0] = farWidth;      vertices[7][1] = -farHeight;    vertices[7][2] = -farPlane;

	float colorLine1[4] = { 0.7f, 0.7f, 0.7f, 0.7f };
	float colorLine2[4] = { 0.2f, 0.2f, 0.2f, 0.7f };
	float colorPlane[4] = { 0.5f, 0.5f, 0.5f, 0.5f };

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// draw the edges around frustum
	glBegin(GL_LINES);
	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[4]);

	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[5]);

	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[6]);

	glColor4fv(colorLine2);
	glVertex3f(0, 0, 0);
	glColor4fv(colorLine1);
	glVertex3fv(vertices[7]);
	glEnd();

	glColor4fv(colorLine1);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[7]);
	glEnd();

	glColor4fv(colorLine1);
	glBegin(GL_LINE_LOOP);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[3]);
	glEnd();

	// draw near and far plane
	glColor4fv(colorPlane);
	glBegin(GL_QUADS);
	glVertex3fv(vertices[0]);
	glVertex3fv(vertices[1]);
	glVertex3fv(vertices[2]);
	glVertex3fv(vertices[3]);
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[7]);
	glEnd();

	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
}
/*
//Quaternion qmodel, qcameraModel;
EulerAngles emodel, ecameraModel;

Quaternion qmodel = new Quaternion;
Quaternion qcamerModel = new Quaternion;


emodel(modelAngle[0],modelAngle[1],modelAngle[2]);
ecameraModel(cameraAngle[0], cameraAngle[1], cameraAngle[2]);
qmodel = eulerAnglesToQuaternion(emodel);
qcameraModel = eulerAnglesToQuaternion(qcameraModel);
*/

///////////////////////////////////////////////////////////////////////////////
// update matrix
///////////////////////////////////////////////////////////////////////////////
void updateViewMatrix()
{
	// transform the camera (viewing matrix) from world space to eye space
	// Notice all values are negated, because we move the whole scene with the
	// inverse of camera transform    matrixView.identity();
	/*matrixView = glm::mat4(1.0f);
	matrixView = glm::translate(matrixView, glm::vec3(-cameraPosition[0], -cameraPosition[1], -cameraPosition[2]));
	matrixView = glm::rotate(matrixView, -cameraAngle[0], glm::vec3(1, 0, 0));   // pitch
	matrixView = glm::rotate(matrixView, -cameraAngle[1], glm::vec3(0, 1, 0));   // heading
	matrixView = glm::rotate(matrixView, -cameraAngle[2], glm::vec3(0, 0, 1));   // roll*/

	matrixView.identity();
	matrixView.translate(-cameraPosition[0], -cameraPosition[1], -cameraPosition[2]);
	matrixView.rotateX(-cameraAngle[0]);    // pitch
	matrixView.rotateY(-cameraAngle[1]);    // heading
	matrixView.rotateZ(-cameraAngle[2]);    // roll

	matrixModelView = matrixView * matrixModel;
}

void updateModelMatrix()
{
	// transform objects from object space to world space
	/*matrixModel = glm::mat4(1.0f);
	matrixModel = glm::rotate(matrixModel, modelAngle[2], glm::vec3(0, 0, 1));
	matrixModel = glm::rotate(matrixModel, modelAngle[1], glm::vec3(0, 1, 0));
	matrixModel = glm::rotate(matrixModel, modelAngle[0], glm::vec3(1, 0, 0));
	matrixModel = glm::translate(matrixModel, glm::vec3(modelPosition[0], modelPosition[1], modelPosition[2]));*/
	matrixModel.identity();
	matrixModel.rotateZ(modelAngle[2]);
	matrixModel.rotateY(modelAngle[1]);
	matrixModel.rotateX(modelAngle[0]);
	matrixModel.translate(modelPosition[0], modelPosition[1], modelPosition[2]);

	matrixModelView = matrixView * matrixModel;
}

///////////////////////////////////////////////////////////////////////////////
// set the camera position and rotation
///////////////////////////////////////////////////////////////////////////////
void setViewMatrix(float x, float y, float z, float pitch, float heading, float roll)
{
	cameraPosition[0] = x;
	cameraPosition[1] = y;
	cameraPosition[2] = z;
	cameraAngle[0] = pitch;
	cameraAngle[1] = heading;
	cameraAngle[2] = roll;

	updateViewMatrix();
}



///////////////////////////////////////////////////////////////////////////////
// set the object position and rotation
///////////////////////////////////////////////////////////////////////////////
void setModelMatrix(float x, float y, float z, float rx, float ry, float rz)
{
	modelPosition[0] = x;
	modelPosition[1] = y;
	modelPosition[2] = z;
	modelAngle[0] = rx;
	modelAngle[1] = ry;
	modelAngle[2] = rz;

	updateModelMatrix();
}



void setMousePosition(int x, int y) { mouseX = x; mouseY = y; };

void setCameraX(float x) { cameraPosition[0] = x; updateViewMatrix(); }
void setCameraY(float y) { cameraPosition[1] = y; updateViewMatrix(); }
void setCameraZ(float z) { cameraPosition[2] = z; updateViewMatrix(); }
void setCameraAngleX(float p) { cameraAngle[0] = p; updateViewMatrix(); }
void setCameraAngleY(float h) { cameraAngle[1] = h; updateViewMatrix(); }
void setCameraAngleZ(float r) { cameraAngle[2] = r; updateViewMatrix(); }
float getCameraX() { return cameraPosition[0]; }
float getCameraY() { return cameraPosition[1]; }
float getCameraZ() { return cameraPosition[2]; }
float getCameraAngleX() { return cameraAngle[0]; }
float getCameraAngleY() { return cameraAngle[1]; }
float getCameraAngleZ() { return cameraAngle[2]; }

void setModelX(float x) { modelPosition[0] = x; updateModelMatrix(); }
void setModelY(float y) { modelPosition[1] = y; updateModelMatrix(); }
void setModelZ(float z) { modelPosition[2] = z; updateModelMatrix(); }
void setModelAngleX(float a) { modelAngle[0] = a; updateModelMatrix(); }
void setModelAngleY(float a) { modelAngle[1] = a; updateModelMatrix(); }
void setModelAngleZ(float a) { modelAngle[2] = a; updateModelMatrix(); }
float getModelX() { return modelPosition[0]; }
float getModelY() { return modelPosition[1]; }
float getModelZ() { return modelPosition[2]; }
float getModelAngleX() { return modelAngle[0]; }
float getModelAngleY() { return modelAngle[1]; }
float getModelAngleZ() { return modelAngle[2]; }

// return 16 elements of  target matrix
/*const float* getViewMatrixElements() { return glm::value_ptr(matrixView); }
const float* getModelMatrixElements() { return glm::value_ptr(matrixModel); }
const float* getModelViewMatrixElements() { return glm::value_ptr(matrixModelView); }
const float* getProjectionMatrixElements() { return glm::value_ptr(matrixProjection); }*/
const float* getViewMatrixElements() { return matrixView.get(); }
const float* getModelMatrixElements() { return matrixModel.get(); }
const float* getModelViewMatrixElements() { return matrixModelView.get(); }
const float* getProjectionMatrixElements() { return matrixProjection.get(); }




///////////////////////////////////////////////////////////////////////////////
// rotate the camera for subWin2 (3rd person view)
///////////////////////////////////////////////////////////////////////////////
void rotateCamera(int x, int y)
{
	cameraAngleX += (x - mouseX);
	cameraAngleY += (y - mouseY);
	mouseX = x;
	mouseY = y;
}

void rotateModel(int x, int y) {
	modelAngleX += (x - mouseX);
	modelAngleY += (y - mouseY);
	setModelAngleX(modelAngleX);
	setModelAngleX(modelAngleY);

	mouseX = x;
	mouseY = y;
}

void rotateCameraModel(int x, int y)
{
	cameraModelAngleX += (x - mouseX);
	cameraModelAngleY += (y - mouseY);
	mouseX = x;
	mouseY = y;
}

///////////////////////////////////////////////////////////////////////////////
// zoom the camera for subWin2 (3rd person view)
///////////////////////////////////////////////////////////////////////////////
void zoomCamera(int y)
{
	cameraDistance -= (y - mouseY) * 0.1f;
	mouseY = y;
}
void zoomCameraDelta(int delta)
{
	cameraDistance -= delta;
}


///////////////////////////////////////////////////////////////////////////////
// change drawing mode
///////////////////////////////////////////////////////////////////////////////
void setDrawMode(int mode)
{
	if (drawMode != mode)
	{
		drawModeChanged = true;
		drawMode = mode;
	}
}

/*
glm::mat4 transpose(glm::mat4 Matrix)
{
glm::mat4 Inv;
for (int i = 0; i < 4; i++) {
for (int j = 0; j < 4; j++) {
Inv[i][j] = Matrix[j][i];
//printf("%f,%f", Inv[i][j], Matrix[j][i]);
}
}
return Inv;

}*/

///////////////////////////////////////////////////////////////////////////////
// draw upper window (view from the camera)
///////////////////////////////////////////////////////////////////////////////
void drawSub1()
{
	int halfHeight = windowHeight / 2;

	// clear buffer
	setViewportSub(0, halfHeight, windowWidth, halfHeight, 1, 10);
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// set upper viewport, make it square
	if (windowWidth > halfHeight)
		setViewportSub((windowWidth - halfHeight) / 2, halfHeight, halfHeight, halfHeight, 1, 10);
	else
		setViewportSub(0, halfHeight + (halfHeight - windowWidth) / 2, windowWidth, windowWidth, 1, 10);

	// clear buffer
	glClearColor(0.2f, 0.2f, 0.2f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();

	// set view matrix ========================================================
	// copy the matrix to OpenGL GL_MODELVIEW matrix
	// Note that OpenGL uses column-major matrix, so transpose the matrix first
	// See updateViewMatrix() how matrixView is constructed. The equivalent
	// OpenGL calls are;
	//    glLoadIdentity();
	//    glRotatef(-cameraAngle[2], 0, 0, 1); // roll
	//    glRotatef(-cameraAngle[1], 0, 1, 0); // heading
	//    glRotatef(-cameraAngle[0], 1, 0, 0); // pitch
	//    glTranslatef(-cameraPosition[0], -cameraPosition[1], -cameraPosition[2]);
	glLoadMatrixf(matrixView.getTranspose());

	// always draw the grid at the origin (before any modeling transform)
	drawGrid(10, 1);

	// transform objects ======================================================
	// From now, all transform will be for modeling matrix only.
	// (from object space to world space)
	// See updateModelMatrix() how matrixModel is constructed. The equivalent
	// OpenGL calls are;		
	//    glLoadIdentity();
	//    glTranslatef(modelPosition[0], modelPosition[1], modelPosition[2]);
	//    glRotatef(modelAngle[0], 1, 0, 0);
	//    glRotatef(modelAngle[1], 0, 1, 0);
	//    glRotatef(modelAngle[2], 0, 0, 1);

	// compute GL_MODELVIEW matrix by multiplying matrixView and matrixModel
	// before drawing the object:
	// ModelView_M = View_M * Model_M
	// This modelview matrix transforms the objects from object space to eye space.
	// copy modelview matrix to OpenGL after transpose
	glLoadMatrixf(matrixModelView.getTranspose());
	//live
	//	glRotatef(modelAngleY, 1, 0, 0); // pitch
	//	glRotatef(modelAngleX, 0, 1, 0);


	// draw a teapot after ModelView transform
	// v' = Mmv * v
	drawAxis(4);
	drawTeapot();

	glPopMatrix();
}



///////////////////////////////////////////////////////////////////////////////
// draw bottom window (3rd person view)
// This function uses only OpenGL matrix and transform calls
///////////////////////////////////////////////////////////////////////////////
void drawSub2()
{
	// set bottom viewport
	setViewportSub(0, 0, windowWidth, windowHeight / 2, NEAR_PLANE, FAR_PLANE);

	// clear buffer
	glClearColor(bgColor[0], bgColor[1], bgColor[2], bgColor[3]);   // background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glPushMatrix();

	// First, transform the camera (viewing matrix) from world space to eye space
	glTranslatef(0, 0, -cameraDistance);
	//live
	glRotatef(cameraAngleY, 1, 0, 0); // pitch
	glRotatef(cameraAngleX, 0, 1, 0); // heading

									  // draw grid
	drawGrid(10, 1);

	// draw a teapot
	glPushMatrix();
	glTranslatef(modelPosition[0], modelPosition[1], modelPosition[2]);
	glRotatef(modelAngle[0], 1, 0, 0);
	glRotatef(modelAngle[1], 0, 1, 0);
	glRotatef(modelAngle[2], 0, 0, 1);
	//live
	//	glRotatef(modelAngleY, 1, 0, 0); // pitch
	//	glRotatef(modelAngleX, 0, 1, 0);

	drawAxis(4);
	drawTeapot();
	glPopMatrix();

	// draw the camera
	glPushMatrix();
	glTranslatef(cameraPosition[0], cameraPosition[1], cameraPosition[2]);
	glRotatef(cameraAngle[0], 1, 0, 0);
	glRotatef(cameraAngle[1], 0, 1, 0);
	glRotatef(cameraAngle[2], 0, 0, 1);
	//live
	//	glRotatef(cameraModelAngleY, 1, 0, 0); // pitch
	//	glRotatef(cameraModelAngleX, 0, 1, 0);
	//----------------------------------------------------------

	glPushMatrix();
	glTranslatef(-cameraPosition[0], -cameraPosition[1], -cameraPosition[2]);
	glMultMatrixf(matrixData.get());
	// Draw animated red L.
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.5, 10.0);
	glEnd();
	glLineWidth(1.0);
	glTranslatef(cameraPosition[0], cameraPosition[1], cameraPosition[2]);

	//----------------------------------------------------------
	drawCamera();
	drawFrustum(FOV_Y, 1, 1, 10);
	glPopMatrix();

	glPushMatrix();
	// Change Euler angles.
	//Xangle = cameraAngle[0];
	//Yangle = cameraAngle[1];
	//Zangle = cameraAngle[2];
	glTranslatef(-cameraPosition[0], -cameraPosition[1], -cameraPosition[2]);

	glRotatef(Xangle, 1.0, 0.0, 0.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Zangle, 0.0, 0.0, 1.0);

	// Draw user-orientable blue L.
	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.0, 10.0);
	glVertex3f(0.0, 0.5, 10.0);
	glEnd();
	glLineWidth(1.0);

	glPopMatrix();


	glPopMatrix();

	glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////////
// draw 2D/3D scene
///////////////////////////////////////////////////////////////////////////////
void draw()
{

	drawSub2();
	drawSub1();
	// post frame
	if (windowSizeChanged)
	{
		setViewport(0, 0, windowWidth, windowHeight);
		windowSizeChanged = false;
	}

	if (drawModeChanged)
	{
		if (drawMode == 0)           // fill mode
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
		}
		else if (drawMode == 1)      // wireframe mode
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
		}
		else if (drawMode == 2)      // point mode
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
		}
		drawModeChanged = false;
	}
}

/**************************************** control_cb() *******************/
/* GLUI control callback                                                 */

void control_cb(int control)
{
	/********************************************************************
	Here we'll print the user id of the control that generated the
	callback, and we'll also explicitly get the values of each control.
	Note that we really didn't have to explicitly get the values, since
	they are already all contained within the live variables:
	'wireframe',  'segments',  'obj',  and 'text'
	********************************************************************/
	printf("callback: %d\n", control);
	printf("             checkbox: %d\n", checkbox->get_int_val());
	printf("              spinner: %d\n", spinner->get_int_val());
	printf("          radio1 group: %d\n", radio1->get_int_val());
	printf("          radio2 group: %d\n", radio2->get_int_val());
	printf("                 text: %s\n", edittext->get_text());
	printf("          spinners group: %d\n", spcameraX);




	switch (control) {
	case 4: setDrawMode(radio1->get_int_val());
		drawModeChanged = true;
		break;
	case 6: setCameraX(spcameraX);
		break;
	case 7:setCameraY(spcameraY);
		break;
	case 8:setCameraZ(spcameraZ);
		break;
	case 9:setCameraAngleX((float)spcameraPitch);
		break;
	case 10:setCameraAngleY((float)spcameraHeading);
		break;
	case 11:setCameraAngleZ((float)spcameraRoll);
		break;
	case 12:setModelX(spmodelX);
		break;
	case 13:setModelY(spmodelY);
		break;
	case 14:setModelZ(spmodelZ);
		break;
	case 15:setModelAngleX(spmodelPitch);
		break;
	case 16:setModelAngleY(spmodelHeading);
		break;
	case 17:setModelAngleZ(spmodelRoll);
		break;
	}

	/*setCameraX(spinnerCamera[0]);
	setCameraY(float y);
	setCameraZ(float z);
	setCameraAngleX(float p);
	setCameraAngleY(float h);
	setCameraAngleZ(float r);*/

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

void quaternionToEuler(Quaternion q, EulerAngles* e)
{
	float w, x, y, z, alpha, beta, gamma;

	w = q.getW();
	x = q.getX();
	y = q.getY();
	z = q.getZ();

	alpha = atan2(2 * (w*x + y*z), 1 - 2 * (x*x + y*y));
	beta = asin(2 * (w*y - z*x));
	gamma = atan2(2 * (w*z + x*y), 1 - 2 * (y*y + z*z));

	*e = *new EulerAngles(Xangle, Yangle, Zangle);

}

void animate(int value)
{
	Quaternion qInterpolated;
	Matrix4 r;

	if (isAnimate)
	{
		if (t < 1.0) t += 0.04;
		qInterpolated = slerp(identityQuaternion, q, t);
		r = quaternionToRotationMatrix(qInterpolated);
		writeMatrixData(r);


		glutPostRedisplay();
		glutTimerFunc(animationPeriod, animate, 1);
	}
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
	case 'x':
		Xangle += 5.0;
		if (Xangle > 180.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle <= -180.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 180.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle <= -180.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 180.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle <= -180.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	case 13:
		readEulerAngles(&e);
		q = eulerAnglesToQuaternion(e);
		isAnimate = 1;
		animate(1);
		glutPostRedisplay();
		break;
	case ' ':
		Zangle = Yangle = Xangle = 0.0;
		isAnimate = 0;
		t = 0.0;
		//for (int i = 0; i < 16; i++) matrixData[i] = 0.0;
		//matrixData[0] = matrixData[5] = matrixData[10] = matrixData[15] = 1.0;
		matrixData.identity();
		glutPostRedisplay();
		break;
	default:
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
	/*	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	*/
	setWindowSize(w, h);

	glutPostRedisplay();
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay(void)
{
	draw();
	glutSwapBuffers();
}

void myGlutMotion(int x, int y)
{
	rotationX += (float)(y - last_y);
	rotationY += (float)(x - last_x);

	last_x = x;
	last_y = y;

	switch (active) {
	case 0: rotateModel(x, y);
		break;
	case 1: rotateCamera(x, y);
		break;
	case 2: rotateCameraModel(x, y);
		break;
	}



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
	setViewMatrix(0, 0, 10, 0, 0, 0);
	setModelMatrix(0, 0, 0, 0, 0, 0);

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
	GLUI *glui = GLUI_Master.create_glui("GLUI", 0, 400, 50); /* name, flags,
															  x, and y */
	new GLUI_StaticText(glui, "Dialog Form");
	new GLUI_Separator(glui);
	//------------
	checkbox = new GLUI_Checkbox(glui, "Wireframe", &wireframe, 1, control_cb);
	//-------------
	spinner = new GLUI_Spinner(glui, "Segments:", &segments, 2, control_cb);
	spinner->set_int_limits(3, 60);
	edittext = new GLUI_EditText(glui, "Text:", text, 3, control_cb);
	//--------------
	GLUI_Panel *obj_panel1 = new GLUI_Panel(glui, "Draw Mode");
	radio1 = new GLUI_RadioGroup(obj_panel1, &drawMode, 4, control_cb);
	new GLUI_RadioButton(radio1, "Fill");
	new GLUI_RadioButton(radio1, "Wireframe");
	new GLUI_RadioButton(radio1, "Points");
	//--------
	GLUI_Panel *obj_panel2 = new GLUI_Panel(glui, "Active");
	radio2 = new GLUI_RadioGroup(obj_panel2, &active, 5, control_cb);
	new GLUI_RadioButton(radio2, "Model");
	new GLUI_RadioButton(radio2, "World");
	new GLUI_RadioButton(radio2, "Camera");
	//-------
	spinnerCamera[0] = new GLUI_Spinner(glui, "Camera X", &spcameraX, 6, control_cb);
	spinnerCamera[0]->set_int_limits(-10, 10);
	spinnerCamera[1] = new GLUI_Spinner(glui, "Camera Y", &spcameraY, 7, control_cb);
	spinnerCamera[1]->set_int_limits(-10, 10);
	spinnerCamera[2] = new GLUI_Spinner(glui, "Camera Z", &spcameraZ, 8, control_cb);
	spinnerCamera[2]->set_int_limits(-10, 10);
	spinnerCamera[3] = new GLUI_Spinner(glui, "Camera Pitch", &spcameraPitch, 9, control_cb);
	spinnerCamera[3]->set_int_limits(-360, 360);
	spinnerCamera[4] = new GLUI_Spinner(glui, "Camera Heading", &spcameraHeading, 10, control_cb);
	spinnerCamera[4]->set_int_limits(-360, 360);
	spinnerCamera[5] = new GLUI_Spinner(glui, "Camera Roll", &spcameraRoll, 11, control_cb);
	spinnerCamera[5]->set_int_limits(-360, 360);

	//-------
	spinnerModel[0] = new GLUI_Spinner(glui, "Model X", &spmodelX, 12, control_cb);
	spinnerModel[0]->set_int_limits(-10, 10);
	spinnerModel[1] = new GLUI_Spinner(glui, "Model Y", &spmodelY, 13, control_cb);
	spinnerModel[1]->set_int_limits(-10, 10);
	spinnerModel[2] = new GLUI_Spinner(glui, "Model Z", &spmodelZ, 14, control_cb);
	spinnerModel[2]->set_int_limits(-10, 10);
	spinnerModel[3] = new GLUI_Spinner(glui, "Model Pitch", &spmodelPitch, 15, control_cb);
	spinnerModel[3]->set_int_limits(-360, 360);
	spinnerModel[4] = new GLUI_Spinner(glui, "Model Heading", &spmodelHeading, 16, control_cb);
	spinnerModel[4]->set_int_limits(-360, 360);
	spinnerModel[5] = new GLUI_Spinner(glui, "Model Roll", &spmodelRoll, 17, control_cb);
	spinnerModel[5]->set_int_limits(-360, 360);

	//------

	new GLUI_Button(glui, "Quit", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(main_window);

	/* We register the idle callback with GLUI, *not* with GLUT */
	GLUI_Master.set_glutIdleFunc(myGlutIdle);
	//GLUI_Master.set_glutIdleFunc(NULL);

}



int main(int argc, char* argv[])
{

	glutWindowSystem(argc, argv);

	//SetupLights();
	init();

	GluiWindowSystem();

	glutMainLoop();

	return EXIT_SUCCESS;
}



