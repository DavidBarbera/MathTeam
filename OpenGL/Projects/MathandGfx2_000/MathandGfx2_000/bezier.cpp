#include "bezier.h"

/////////////////////////////////////////////////////////////////////////////
// Name:           BezierCurve constructor
// Arguments:      Four points for a single cubic Bezier curve
// Returns:        none
/////////////////////////////////////////////////////////////////////////////    
BezierCurve::BezierCurve(Point3 p0,Point3 p1,Point3 p2,Point3 p3)
{
	InitPoints(p0,p1,p2,p3);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           InitPoints
// Arguments:      Four points for a single cubic Bezier curve
// Returns:        none
// Side Effects:   Possibly does some preprocessing for the curve.  For example,
//                 here we could compute the 4 cubic coefficients and store them
//                 in some local array.  Or, we could compute the matrix form
//                 of this equation and store it locally.  You are free to modify
//                 bezier.h accordingly.
/////////////////////////////////////////////////////////////////////////////    
void BezierCurve::InitPoints(Point3 p0,Point3 p1,Point3 p2,Point3 p3)
{

	Points[0] = p0;
	Points[1] = p1;
	Points[2] = p2;
	Points[3] = p3;

}



/////////////////////////////////////////////////////////////////////////////
// Name:           Evaluate
// Arguments:      A t value, the position and tangents to store the result
// Returns:        none
// Side Effects:   For the given value of t, compute the resulting point on 
//                 the Bezier curve and its tangent.  Store the point in 'pos'
//                 and the tangent vector in 'tan.'
/////////////////////////////////////////////////////////////////////////////    
void BezierCurve::Evaluate(float t,Point3 &pos,Vector3 &tan)
{
	pos.Lerp(t,Points[0], Points[3]);
	tan = Points[3] - Points[0];

}

/////////////////////////////////////////////////////////////////////////////
// Name:           BezierPatch constructor
// Arguments:      Array of 16 points representing the control points of the 
//                 bezier patch.  ures and vres define the degree of tesselation
//                 in the patch.
// Returns:        none
// Side Effects:   Computes the entire patch and stores it as a single indexed
//                 model.  Should work if ures and vres are not equal.
/////////////////////////////////////////////////////////////////////////////    
BezierPatch::BezierPatch(Point3* pArray, int ures, int vres)
{
	Init(4,1,0,2);
	pVertices[0] = pArray[0];
	pVertices[1] = pArray[3];
	pVertices[2] = pArray[15];
	pVertices[3] = pArray[12];

	pNormals[0].Cross(pVertices[1] - pVertices[0], pVertices[3] - pVertices[0]);
	pTris[0].SetVertices(0,1,2);
	pTris[1].SetVertices(0,2,3);
	pTris[0].SetNormals(0,0,0);
	pTris[1].SetNormals(0,0,0);

}