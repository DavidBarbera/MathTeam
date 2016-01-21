/////////////////////////////////////////////////////////////////////////////
// camera.h
//
// Author: Cameron Chrisman () &
//         Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Camera:          Base camera class, which contains information like position,
//                  target, up, and clipping planes
//
// PerspectiveCam:  Perspective camera class, for implementing perspective
//                  projections
//
// OrthographicCam: Orthographic camera class, for implementing orthographic
//                  projections
/////////////////////////////////////  
// History: 2006-Winter: Written for CSE167 Winter 2006           
/////////////////////////////////////////////////////////////////////////////
#ifndef CSE167_CAMERA_H__
#define CSE167_CAMERA_H__

#include "vector.h"
#include "matrix.h"

/////////////////////////////////////////////////////////////////////////////
// Camera
//
class Camera  
{
////////////////////////////////
// Local Structure
protected:
    struct Plane {
        Vector3 normal;
        float d;
    };

////////////////////////////////
// Constructors/Destructors
public:
    Camera();
    virtual ~Camera() {};

////////////////////////////////
// Local Procedures
public:
    void SetEye(const Point3& eye)               { Eye = eye; }
    void SetUp(const Vector3& up)                { Up = up; }
    void SetTarget(const Point3& t)              { Target = t; }
    void SetNearClip(float nc)                   { NearClip = nc;}
    void SetFarClip(float fc)                    { FarClip = fc;}

    void SetWindowDimensions(unsigned int width,unsigned height) 
        { PixelWidth = width; PixelHeight =  height; }

    Vector3& GetUp()                             { return Up; }
    Point3& GetEye()                             { return Eye; }
    Point3& GetTarget()                         { return Target; }
    float GetNearClip()                          { return NearClip; }
    float GetFarClip()                           { return FarClip; }
	float GetAspect()							 { return (float) PixelWidth/PixelHeight;}

    void GetWindowDimensions(unsigned int &width,unsigned &height) 
        { width = PixelWidth; height = PixelHeight; }


//***************************************************************************
// Begin Assignment  (Implement the following functions in camera.cpp
    void CalcInvLookAt(Matrix &out);
    virtual void CalcProjectionMatrix(Matrix &out)=0;
    virtual void CalcCullingInfo()=0;
    void DrawFrustum();
    char CullBoundingSphere(const Point3 &pos, float radius);
	char TestBoundingSpherePlane(const Point3 &pos, float radius, const Vector3 &normal, float d);
// End Assignment  (Implement the following functions in camera.cpp
//***************************************************************************

////////////////////////////////
// Member Variables
protected:
    // main screen params
    Point3        Eye;
    Point3        Target;    
    Vector3       Up;
     float         NearClip, FarClip;
    unsigned int  PixelWidth,PixelHeight;
    
    // For Culling
    Plane frustumPlanes[6];
	Point3 frustumCorners[8];

};


/////////////////////////////////////////////////////////////////////////////
// PerspectiveCam
//
class PerspectiveCam : public Camera
{
////////////////////////////////
// Constructor/Destructor
public:
    PerspectiveCam(float fov)                          {FOV = fov;}
    virtual ~PerspectiveCam() {};

////////////////////////////////
// Local Procedures
public:
    void SetFOV(float fov) { FOV = fov; }
    float& GetFOV() { return FOV; }
        
//***************************************************************************
// Begin Assignment  (Implement the following functions in camera.cpp

    void CalcProjectionMatrix(Matrix &out);
    void CalcCullingInfo();

// End Assignment  (Implement the following functions in camera.cpp
//***************************************************************************

////////////////////////////////
// Member Variables
private:
    float FOV;
};

/////////////////////////////////////////////////////////////////////////////
// OrthographicCam
//
class OrthographicCam : public Camera
{
////////////////////////////////
// Constructor/Destructor
public:
    OrthographicCam(float h)            { Height = h; }
    virtual ~OrthographicCam() {};

////////////////////////////////
// Local Procedures

//***************************************************************************
// Begin Assignment  (Implement the following functions in camera.cpp

    void CalcProjectionMatrix(Matrix &out);
    void CalcCullingInfo();

// End Assignment  (Implement the following functions in camera.cpp
//***************************************************************************

////////////////////////////////
// Member Variables
private:
    float Height;
};

#endif // CSE167_CAMERA_H__