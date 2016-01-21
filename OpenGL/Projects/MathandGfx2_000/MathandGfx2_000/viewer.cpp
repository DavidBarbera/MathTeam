#include "viewer.h"
#include "core.h"

#define CAM_SPEED_STEP 0.001
#define CAM_SPEED_MAX 0.01
#define CAM_SPEED_MIN 0

Viewer::Viewer(char* title,int width,int height):perspCam(60.0),orthoCam(10.0)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( width, height );
	glutCreateWindow( title );

	bgColor.Set(0.7,0.7,0.7);
	
	camera = &perspCam;
	camera->SetNearClip(0.01);
	camera->SetFarClip(1000);

	initialize();
	reshape(width,height);
}

// THESE ARE THE FUNCTIONS YOU WILL MOST COMMONLY OVERRIDE!
void Viewer::initialize()
{
    // Setup the background color
    glClearColor(0.5,0.7,0.9,1);
    // Enable depth testing
    glEnable ( GL_DEPTH_TEST );
    // Enable back face culling
    glEnable ( GL_CULL_FACE );
    // So our normals are not adversely affected by nonuniform scales
    glEnable (GL_NORMALIZE);
    // Allow glColorf to specify the ambient and diffuse components of our materials
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    // Enable lighting
    Light::EnableLighting ();


	// Initialize Camera
	lookTarget.Set(0,0,0);
	viewTheta = M_PI; viewPhi = M_PI/4; viewDistance = 20;
	updateCamera();

	// Here we initialize our models
	pTeapot = new ObjFile("teapot.obj", Matrix::IDENTITY);
	pTeapotShape = new ShapeNode(pTeapot);
	pTeapotShape->SetColor(Color3(0,0.6,0.9));

	iObjectSelect = OBJ_CURVE;
	myScene.SetRootNode(0);

	// Add Lights
	LightList* lights = myScene.GetLights();    
  	Light l;
   	l.SetPosition(Point3(-2,5,10));
	lights->Push(l);
	Light l2;
   	l2.SetPosition(Point3(-2,10,-1));
	lights->Push(l2);

	// Initialize Camera Paths
	cameraPaths[0].InitPoints(Point3(-20,20,-5), Point3(-20,20,20), Point3(20,20,20), Point3(20,20,-5));
	cameraPaths[1].InitPoints(Point3(20,20,-5), Point3(20,20,-20), Point3(-20,20,-20), Point3(-20,20,-5));
	bUseCameraPath = false;
	tCameraPath=0.0;
	cameraSpeed = 0.0001;

	// Initialize Visible Bezier Curve
	controlPoints[0] = Point3(-1,5,0);
	controlPoints[1] = Point3(-1,7,0);
	controlPoints[2] = Point3(.25,3,0);
	controlPoints[3] = Point3(1,5,0);
	BezierCurve curve(controlPoints[0],controlPoints[1],controlPoints[2],controlPoints[3]);
	preCalcBezierCurve(curve);

	int h = -1;
	for(int j=0; j < 4; j++) {
		for(int k = 0; k < 4; k++) {
			controlPatch[j*4+k].Set(2*(j-1.5),h+2,2*(k-1.5));
			h *= -1;
		}
	}

	pPatch = new BezierPatch(controlPatch, 10, 15);
	pPatchShape = new ShapeNode(pPatch);
	pPatchShape->SetColor(Color3(.2,.4,.7));

}

void Viewer::draw()
{
	if(bUseCameraPath)
		updateCameraPath();
	drawCamera();

	if(iObjectSelect == OBJ_CURVE) {
		Light::DisableLighting();
		drawBezierCurve();
	}

	// Draw the floor
	Light::DisableLighting();
	drawFloor(10,10,20);

	// Draw the teapot
	glRenderer.Render(&myScene);

	glutSwapBuffers();
	glutPostRedisplay();
}

void Viewer::idle() { }

void Viewer::keyboardInput(unsigned char key,int x,int y)
{
	switch(key)
	{
		        // Increase the simulation step size
        case '+':        
            cameraSpeed += CAM_SPEED_STEP;
            if(cameraSpeed > CAM_SPEED_MAX)
                cameraSpeed = CAM_SPEED_MAX;
            break;
        // Decrease the simulation step size
        case '-':        
            cameraSpeed -= CAM_SPEED_STEP;
            if(cameraSpeed < CAM_SPEED_MIN)
                cameraSpeed = CAM_SPEED_MIN;
            break;   

		case 's':
			if(iObjectSelect == OBJ_CURVE) {
				iObjectSelect = OBJ_TEAPOT;
				myScene.SetRootNode(pTeapotShape);
			} else if(iObjectSelect == OBJ_TEAPOT) {
				iObjectSelect = OBJ_PATCH;
				myScene.SetRootNode(pPatchShape);
			} else {
				iObjectSelect = OBJ_CURVE;
				myScene.SetRootNode(0);
			}
			break;
		case 'c':
			bUseCameraPath = !bUseCameraPath;
			if(bUseCameraPath)
				printf("Camera Path: On\n");
			else {
				printf("Camera Path: Off\n");
				updateCamera();
			}
			break;
		case 'q':
		case 27 :         // "27" is theEscape key
			exit(1);
			break;
	}
}

// YOU WILL PROBABLY NOT NEED TO OVERRIDE ANY FUNCTIONS BELOW THIS LINE
// BUT FEEL FREE TO IF YOU WANT!  
/////////////////////////////////////////////////////////////////////////////////

void Viewer::mouseButton(int buttonType,int buttonState,int x,int y)
{
	this->buttonState = buttonState; 
	this->buttonType = buttonType; 
	if(buttonState == GLUT_DOWN)
	{
		mousePosition.Set(x,y,0);
	}
}

void Viewer::mouseMotion(int x,int y)
{
//	fprintf(stderr,"calling mouse motion theta: %f  phi: %f dist: %f!\n",viewTheta,viewPhi,viewDistance);
	if(bUseCameraPath)
		return;

	Vector3 mouseNew,mouseDelta,u,v,w;
	float rotateSpeed = 1./100;
	float zoomSpeed,translateSpeed;

	w = camera->GetTarget() - camera->GetEye();
	w.Normalize();
	v = camera->GetUp();
	v.Normalize();
	u.Cross(v,w);
	u.Normalize();

	mouseNew.Set(x,y,0);
	mouseDelta = mouseNew-mousePosition;
	mousePosition = mouseNew;

	switch(buttonType) 
	{
		case GLUT_LEFT_BUTTON:
			viewTheta -= mouseDelta.x*rotateSpeed;
			viewPhi += mouseDelta.y*rotateSpeed;
			if(viewPhi > M_PI*0.5)
				viewPhi = M_PI*0.5;
			if(viewPhi < -M_PI*0.5)
				viewPhi = -M_PI*0.5;
			break;
		case GLUT_MIDDLE_BUTTON:
			translateSpeed = viewDistance*rotateSpeed*(1./5);
			lookTarget += (mouseDelta.x*u + mouseDelta.y*v)*translateSpeed;
			break;
		case GLUT_RIGHT_BUTTON:
			zoomSpeed = viewDistance*rotateSpeed*(1./5);
			viewDistance -= mouseDelta.y*zoomSpeed;
			break;
	} 
	updateCamera();
}

void Viewer::reshape(int w,int h)
{
	windowSize.x = w; windowSize.y = h;
	glClearColor(bgColor.x, bgColor.y, bgColor.z, 1);
	glViewport(0,0,(int)windowSize.x,(int)windowSize.y);
	camera->SetWindowDimensions((int)windowSize.x,(int)windowSize.y);
}

void Viewer::drawCamera()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix projection, lookat;

	 // Setup our projection Matrix4x4
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
//	camera->CalcProjectionMatrix(projection);
//	glMultMatrixf(projection);
//	Equivalent OpenGL command:
	gluPerspective(((PerspectiveCam*)camera)->GetFOV(),windowSize.x/windowSize.y,camera->GetNearClip(),camera->GetFarClip());

//	camera->CalcLookAt(lookat);
//	glMultMatrixf(lookat);
//	Equivalent OpenGL command:
	Point3 eye = camera->GetEye();
	Point3 target = camera->GetTarget();
	Vector3 up = camera->GetUp();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye.x, eye.y, eye.z, target.x, target.y, target.z, up.x, up.y, up.z);
}


void Viewer::updateCamera() {
	Matrix rotx,roty,rot,lookat,projection;
	Vector3 up;
	Point3 cameraPos;

	// We set up a single rotation Matrix4x4 for our polar rotations of Theta and Phi
    roty.MakeRotateY(viewTheta);
    rotx.MakeRotateX(viewPhi);
	rot = roty*rotx;

	// We fix the up vectors and initial positions of the camera
	// and then transform them by our Matrix4x4
	cameraPos.Set(0,0,-viewDistance);
	up.Set(0,1,0);
	
	rot.Transform(cameraPos,cameraPos);
	rot.Transform(up,up);

	// Then we shift the entire frame of reference of the camera
	// so that we are rotating about our look target
	cameraPos += lookTarget.ToVector3();

	camera->SetEye(cameraPos);
	camera->SetTarget(lookTarget);
}

void Viewer::updateCameraPath() {
	tCameraPath += cameraSpeed;
	tCameraPath = (tCameraPath >= 2.0) ? tCameraPath - 2.0 : tCameraPath;
//	tCameraPath = fmod(tCameraPath, 2.0);
	float tEval = tCameraPath;
	int iPath = 0;
	if(tEval > 1.0) {
		iPath = 1;
		tEval -= 1.0;
	}
	Point3 eye; Vector3 dummy;
	cameraPaths[iPath].Evaluate(tEval, eye, dummy);
	camera->SetEye(eye);
	camera->SetTarget(Point3(0,0,0));

}

void Viewer::preCalcBezierCurve(BezierCurve &curve) {
	float t=0;
	float tdelta = 1./19.;
	for(int i = 0; i < 20; i++) { 
		curve.Evaluate(t, curvePoints[i], curveTangents[i]);
		t += tdelta;
	}
}

void Viewer::drawBezierCurve() {

	int i;

	glColor3f(1,1,0);
	glBegin(GL_LINE_STRIP);
	for(i = 0; i < 4; i++) 
		glVertex3fv(controlPoints[i]);
	glEnd();

	glColor3f(1,1,0);
	glPointSize(3);
	glBegin(GL_POINTS);
	for(i = 0; i < 4; i++) 
		glVertex3fv(controlPoints[i]);
	glEnd();


 	glColor3f(0,0,1);
	glBegin(GL_LINE_STRIP);
	for(i = 0; i < 20; i++) 
		glVertex3fv(curvePoints[i]);
	glEnd();

}

void Viewer::drawFloor(unsigned int nx,unsigned int ny,float radius)
{
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINES);
	for(unsigned int i=0;i<=nx;++i)
	{
		if(i==nx/2){ glColor3f(0,0,0); }
		glVertex3f((2*radius*i)/nx-radius,0,-radius);
		glVertex3f((2*radius*i)/nx-radius,0,radius);
		if(i==nx/2){ glColor3f(0.5,0.5,0.5); }

	}

	for(unsigned int j=0;j<=ny;++j)
	{
		if(j==ny/2){ glColor3f(0,0,0); }
		glVertex3f(-radius,0,(2*radius*j)/ny-radius);
		glVertex3f(radius,0,(2*radius*j)/ny-radius);
		if(j==ny/2){ glColor3f(0.5,0.5,0.5); }

	}

	glEnd();
}
