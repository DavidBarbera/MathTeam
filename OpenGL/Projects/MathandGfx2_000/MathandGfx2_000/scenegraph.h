/////////////////////////////////////////////////////////////////////////////
// scenegraph.h
//
// Authors: Cameron Chrisman (cchrisman@cs.ucsd.edu)
//          Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Stack:         A templated stack class
//
// Node:          Base node that defines node interface
//
// Scene:         A class enclosing elements in our scene
// 
///////////////////////////////////// 
// History: 2006-Winter: Written by for CSE167 Winter 2006 
/////////////////////////////////////////////////////////////////////////////

#ifndef CSE167_SCENEGRAPH_H_
#define CSE167_SCENEGRAPH_H_

#include "vector.h"
#include "matrix.h"
#include "geometry.h"
#include "light.h"


////////////////////////////////
// Forward Declarations
//
template <class T> class Stack;
class Node;
typedef Stack<Node*> NodeList;
typedef Stack<Light> LightList;

//**************************************************************************//
// Templated Stack class
//
template <class T> class Stack
{
////////////////////////////////
// Constructors/Destructors
    public:
        Stack();
        ~Stack();
////////////////////////////////
// Local Procedures
    public:
        void Push(T );
        void Pop();
        void Clear();
        T Get(int i);
        T* GetPointer(int i);
        unsigned int Size();
////////////////////////////////
// Member variables
    private:
        unsigned int m_nElem,m_ArraySize;
        T* data;
};


//**************************************************************************//
// Node
//
class Node
{
////////////////////////////////
// Constructor/Destructor
public:
	Node() {m_pParentNode = 0;}
////////////////////////////////
// Local Procedures
public:
    void SetParent(Node* parent)            { m_pParentNode = parent; }
    Node* GetParent()                       { return m_pParentNode; };

    
	virtual void AddChild(Node *pChildNode) {};
    virtual NodeList* GetChildren()         { return 0; }
    virtual Geometry* GetGeometry()         { return 0; };
    virtual Matrix GetLocalTransform()      { return Matrix::IDENTITY; }
    virtual Matrix GetWorldTransform()      { return Matrix::IDENTITY; }

////////////////////////////////
// Member variables

private:    
    Node     *m_pParentNode;
};


//**************************************************************************//
// TransformNode
//
class TransformNode : public Node 
{

////////////////////////////////
// Local Procedures
public:
    void AddChild(Node *pChildNode);
    NodeList* GetChildren()              { return &m_lChildren; }
    Matrix GetLocalTransform()           { return m_LocalTransform; }

////////////////////////////////
// Member variables

protected:    
    Matrix   m_LocalTransform;
    NodeList m_lChildren;
};



//**************************************************************************//
// RotationNode
//
class RotationNode : public TransformNode 
{
////////////////////////////////
// Constructor/Destructor
public:
	RotationNode() {axis = Vector3(0,1,0); angle = 0;};

////////////////////////////////
// Local Procedures
public:
	// sets axis (performs normalization)
	void SetAxis(Vector3 v)            { axis = v;  axis.Normalize(); UpdateLocalTransform(); }  
	// Sets angle in radians
	void SetAngle(float radians)       { angle = radians; UpdateLocalTransform(); }

private:
	// Updates the local transformation matrix 
	void UpdateLocalTransform();

////////////////////////////////
// Member variables
private:
	Vector3 axis;
	float angle;
};



//**************************************************************************//
// TranslationNode
//
class TranslationNode : public TransformNode {
////////////////////////////////
// Local Procedures
public:
    void SetTranslation(Vector3 v)         { d = v; UpdateLocalTransform(); }
private:
	void UpdateLocalTransform();
////////////////////////////////
// Member variables
private:
    Vector3 d;
};


//**************************************************************************//
// ScaleNode
//
class ScaleNode : public TransformNode {
////////////////////////////////
// Local Procedures
public:
    void SetScale(Vector3 v)         { s = v; UpdateLocalTransform(); }
private:
	void UpdateLocalTransform();
////////////////////////////////
// Member variables
private:
    Vector3 s;
};


//**************************************************************************//
// ShapeNode
//
class ShapeNode : public Node
{
////////////////////////////////
// Constructor/Destructor
public:
	ShapeNode(Geometry *pGeom=0)            { m_pGeom = pGeom;}
////////////////////////////////
// Local Procedures
   public:
        Geometry* GetGeometry()             { return m_pGeom; };
		void SetGeometry(Geometry *pGeom)   { m_pGeom = pGeom;}

////////////////////////////////
// Member variables
    private:    
		Geometry *m_pGeom;
};





/////////////////////////////////////////////////////////////////////////////
// Scene
//
class Scene
{
////////////////////////////////
// Constructor/Destructor
    public:
        Scene() {m_RootNode = 0;};
////////////////////////////////
// Local Procedures
    public:
        Node* GetRootNode()            { return m_RootNode; }
		void SetRootNode(Node *pNode)  { m_RootNode = pNode;}
        LightList* GetLights()         { return &m_lLights; }

////////////////////////////////
// Member variables
    protected:
        Node      *m_RootNode;
        LightList m_lLights;
};




//**************************************************************************//
// Begin Stack Template Definitions
//


// You shouldn't need to modify any of this code, or know the details of how it works
// other than its syntax

template <class T> Stack<T>::Stack()
{
    m_nElem=0;
    m_ArraySize = 0;
    data = 0;
}

template <class T> Stack<T>::~Stack() { if(data) delete[] data; }

template <class T> void Stack<T>::Push(T item)
{
    // this function is currently slow, but can be easily made faster with lazy allocation
    T* newData = new T[m_nElem+1];

    for(unsigned int i=0;i<m_nElem;++i)
        newData[i] = data[i];
    
    if(data)
        delete[] data;

    data = newData;

    data[m_nElem] = item;
    m_nElem++;
}

template <class T> void Stack<T>::Pop() { --m_nElem; }
template <class T> void Stack<T>::Clear() { delete[] data; m_nElem = m_ArraySize = 0;}
template <class T> T Stack<T>::Get(int i) { return data[i]; }
template <class T> T* Stack<T>::GetPointer(int i) { return &(data[i]); }
template <class T> unsigned int Stack<T>::Size() { return m_nElem; }

// End Stack Template Definitions
//**************************************************************************//

#endif
