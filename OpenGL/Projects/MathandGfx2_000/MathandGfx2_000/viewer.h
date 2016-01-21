#ifndef __CSE167_VIEWER_H
#define __CSE167_VIEWER_H

#include "camera.h"
#include "vector.h"
#include "objfile.h"
#include "bezier.h"
#include "renderer.h"
#include "scenegraph.h"

class Viewer
{
	public:
		Viewer(char* title,int width,int height);
	public:
		virtual void initialize();
		virtual void keyboardInput(unsigned char key,int x,int y);
		virtual void mouseButton(int buttonType,int buttonState,int x,int y); 
		virtual void mouseMotion(int x,int y);
		virtual void draw();
		virtual void idle();
		virtual void reshape(int w,int h);

	protected:
		Camera* camera;
		
		void drawFloor(unsigned int nx,unsigned int ny,float radius);
		void drawCamera();
		void updateCamera();

		// Testing Functions for this project
		void updateCameraPath();
		void preCalcBezierCurve(BezierCurve &curve);
		void drawBezierCurve();
	private:
		float viewTheta,viewPhi,viewDistance;
		Vector3 mousePosition,bgColor,windowSize;
		Point3 lookTarget;
		int buttonType,buttonState;
		PerspectiveCam perspCam;
		OrthographicCam orthoCam;
		OpenGLRenderer glRenderer;

	// Local variables you will most likely modify
	private:

		// Objects
		ObjFile *pTeapot;
		BezierPatch *pPatch;
		ShapeNode *pTeapotShape;
		ShapeNode *pPatchShape;
		Scene myScene;
		int iObjectSelect;
		enum{ OBJ_CURVE, OBJ_TEAPOT, OBJ_PATCH};

		// Camera Paths
		BezierCurve cameraPaths[2];
		bool bUseCameraPath;
		float tCameraPath;
		float cameraSpeed;

		// For testing Bezier Curves
		Point3 controlPoints[4];
		Point3 curvePoints[20];
		Vector3 curveTangents[20];

		// For testing Bezier Patches
		Point3 controlPatch[16];

};


#endif
