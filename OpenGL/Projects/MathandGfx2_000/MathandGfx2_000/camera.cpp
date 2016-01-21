#include "Camera.h"


/////////////////////////////////////////////////////////////////////////////
// Name:           Camera Constructor
// Arguments:      none
// Returns:        none
// Side Effects:   
/////////////////////////////////////////////////////////////////////////////
Camera::Camera()
{
    Eye.Set(0,0,1);
    Target.Set(0,0,0);    
    Up.Set(0,1,0);
    NearClip = 1;
    FarClip = 12;
    PixelWidth = PixelHeight = 1;
 
}


//***************************************************************************
// BeginAssignment 


/////////////////////////////////////////////////////////////////////////////
// Name:           CalcInvLookAt
// Arguments:      Matrix to store the inverse camera transform (inverse lookat)
// Returns:        none
// Side Effects:   Sets 'out' to the inverse lookat transformation determined by 
//                 local Eye, Target, and Up variables
/////////////////////////////////////////////////////////////////////////////
void Camera::CalcInvLookAt(Matrix& out){

    out.Identity();

}

/////////////////////////////////////////////////////////////////////////////
// Name:           DrawFrustum
// Arguments:      none
// Returns:        none
// Side Effects:   Draws the frustum as given by the eight frustumCorners
//                 point values.  This is dependant upon the order the
//                 points were created in the CalcCullingInfo functions below
//                 You may assume CalcCullingInfo has already been called.
/////////////////////////////////////////////////////////////////////////////
void Camera::DrawFrustum() {

}

/////////////////////////////////////////////////////////////////////////////
// Name:           CalcProjectionMatrix
// Arguments:      Matrix to store the projection transformation in
// Returns:        none
// Side Effects:   Sets 'out' to the perspective projeciton matrix determined 
//                 local FOV, window dimensions, Near and Far clipping planes
/////////////////////////////////////////////////////////////////////////////
void PerspectiveCam::CalcProjectionMatrix(Matrix &out)
{
	out.Identity();
}

/////////////////////////////////////////////////////////////////////////////
// Name:           CalcProjectionMatrix
// Arguments:      Matrix to store the projection transformation in
// Returns:        none
// Side Effects:   Sets 'out' to the perspective projeciton matrix determined 
//                 local Height, window dimensions, Near and Far clipping planes
//                 To simplify computation, we assume the left and right frustum
//                 planes are equidistant from the origin.  The same is true for
//                 the top and bottom planes.
//                 Height (top - bottom) is known.  Width is computed as 
//                 the product of the height and the aspect ratio of the window
//                 sizes.
/////////////////////////////////////////////////////////////////////////////
void OrthographicCam::CalcProjectionMatrix(Matrix &out)
{
	out.Identity();
}

/////////////////////////////////////////////////////////////////////////////
// Name:           CullBoundingSphere
// Arguments:      The position and radius of the bounding sphere to be culled
//                 The array of six plane 'D' components and six plane Normal
//                 vectors calculated in CalcCullingInfo.
//                 You may assume CalcCullingInfo has already been called.
// Returns:         1 if the bounding sphere lies completely outside the frustum
//                  0 if the bounding sphere intersects the frustum
//                 -1 if the bounding sphere lies completely inside the frustum
/////////////////////////////////////////////////////////////////////////////
char Camera::CullBoundingSphere(const Point3 &pos, float radius)
{
	return 1;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           TestBoundingSpherePlane
// Arguments:      The position and radius of the bounding sphere to be culled
//                 The normal and 'd' component for a single plane 
// Returns:         1 if the bounding sphere lies completely in front of the plane
//                  0 if the bounding sphere intersects the plane
//                 -1 if the bounding sphere lies completely behind the plane
/////////////////////////////////////////////////////////////////////////////
char Camera::TestBoundingSpherePlane(const Point3 &pos, float radius, const Vector3 &normal, float d)
{
	return 1;

}


/////////////////////////////////////////////////////////////////////////////
// Name:           CalcCullingInfo
// Arguments:      none
// Returns:        none
// Side Effects:   Stores the plane information (normal and d component) for
//                 each of the six frustum planes in the local frustumPlanes 
//                 array.
/////////////////////////////////////////////////////////////////////////////
void PerspectiveCam::CalcCullingInfo() 
{

}


/////////////////////////////////////////////////////////////////////////////
// Name:           CalcCullingInfo
// Arguments:      none
// Returns:        none
// Side Effects:   Stores the plane information (normal and d component) for
//                 each of the six frustum planes in the local frustumPlanes 
//                 array. Also fills frustumCorners with the eight corners
//                 of the frustum
/////////////////////////////////////////////////////////////////////////////
void OrthographicCam::CalcCullingInfo() 
{
 

}

// End Assignment 
//***************************************************************************
