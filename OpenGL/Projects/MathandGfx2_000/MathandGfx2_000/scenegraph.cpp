/////////////////////////////////////////////////////////////////////////////
// scenegraph.cpp     
///////////////////////////////////// 

#include "scenegraph.h"

//***************************************************************************
//************************** Begin Assignment *******************************

/////////////////////////////////////////////////////////////////////////////
// Name:           AddChild
// Arguments:      A child node to add
// Returns:        none
// Side Effects:   Adds the node to the current list of children.  Sets the
//                 child's parent node appropriately
/////////////////////////////////////////////////////////////////////////////
void TransformNode::AddChild(Node *pNode)
{

}


/////////////////////////////////////////////////////////////////////////////
// Name:           UpdateLocalTransform
// Arguments:      none
// Returns:        none
// Side Effects:   Updates the local transformation matrix, setting it to a
//                 rotation matrix about the unit axis 'axis' by angle 'angle'
/////////////////////////////////////////////////////////////////////////////
void RotationNode::UpdateLocalTransform()
{

}


/////////////////////////////////////////////////////////////////////////////
// Name:           UpdateLocalTransform
// Arguments:      none
// Returns:        none
// Side Effects:   Updates the local transformation matrix, setting it to a 
//                 translation matrix based on 'd'
/////////////////////////////////////////////////////////////////////////////
void TranslationNode::UpdateLocalTransform()
{
	
}


/////////////////////////////////////////////////////////////////////////////
// Name:           UpdateLocalTransform
// Arguments:      none
// Returns:        none
// Side Effects:   Updates the local transformation matrix, setting it to a 
//                 scale matrix based on 's'
/////////////////////////////////////////////////////////////////////////////
void ScaleNode::UpdateLocalTransform()
{

}

//************************** End Assignment *********************************
//***************************************************************************
