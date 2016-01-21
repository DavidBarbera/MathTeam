////////////////////////////////////////////////////////////////////////////////
// geometry.cpp
///////////////////////////////////// 

#include "geometry.h"
#include "core.h"
#include "float.h"

/////////////////////////////////////////////////////////////////////////////
// Name:           Geometry Constructor
// Arguments:      none
// Returns:        none
// Side Effects:   Initializes all member variables to 0
/////////////////////////////////////////////////////////////////////////////
Geometry::Geometry(){ 
	pVertices    =0;
    pNormals     =0;
    pColors      =0;
    pTris        =0;
    numVertices  =0;
    numNormals   =0;
    numColors    =0;
    numTriangles =0;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Geometry Constructor
// Arguments:      number of vertices, normals, colors, and triangles
// Returns:        none
// Side Effects:   Initializes all member variables to their appropriate sizes
/////////////////////////////////////////////////////////////////////////////
Geometry::Geometry(int numVerts, int numNorms, int numCols, int numTris) 
{
    Init (numVerts, numNorms, numCols, numTris);
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Geometry Destructor
// Arguments:      number of vertices, normals, colors, and triangles
// Returns:        none
// Side Effects:   Initializes all member variables to their appropriate sizes
//                 Also deletes any pre-existing arrays
/////////////////////////////////////////////////////////////////////////////
Geometry::~Geometry()
{
    // Delete triangles if we allocated some
    // Note that deleting a pointer to 0 (NULL) has no adverse effects, so 
    // that's how we get away with this instead of doing
    // if(pVertices) delete[] pVertices;

    delete [] pVertices;
    delete [] pNormals;
    delete [] pColors;
    delete [] pTris;
}

/////////////////////////////////////////////////////////////////////////////
// Name:           Init
// Arguments:      number of vertices, normals, colors, and triangles
// Returns:        none
// Side Effects:   Initializes all member variables to their appropriate sizes
//                 Also deletes existing arrays
/////////////////////////////////////////////////////////////////////////////
void Geometry::Init (int numVerts, int numNorms, int numCols, int numTris)
{
    if(numVerts == 0 || numTris == 0) 
        return; // We should probably throw some kind of error here 

    delete [] pVertices;
    delete [] pNormals;
    delete [] pColors;
    delete [] pTris;
    
    numTriangles = numTris;
    numVertices = numVerts;
    numNormals = numNorms;
    numColors = numCols;
    
    pVertices = new Point3[numVertices];
    if(numNormals != 0) pNormals = new Vector3[numNormals];
    if(numColors != 0) pColors = new Color3[numColors];
    pTris = new Triangle[numTriangles];
}


//***************************************************************************
// BEGIN ASSIGNMENT 4
// You do not need to implement this for Assignment 3

/////////////////////////////////////////////////////////////////////////////
// Name:           CalcBoundingSphere
// Arguments:      none
// Returns:        none
// Side Effects:   Calculates the center and radius of the bounding sphere
//                 and stores the results in boundingCenter and boundingRadius               
/////////////////////////////////////////////////////////////////////////////
void Geometry::CalcBoundingSphere( Point3 &boundingCenter, float &boundingRadius)
{

}


// END ASSIGNMENT 4
//***************************************************************************
