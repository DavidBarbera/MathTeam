/////////////////////////////////////////////////////////////////////////////
// scenegraph.h
//
// Authors: Cameron Chrisman (cchrisman@cs.ucsd.edu)
//          Alex Kozlowski (kman@graphics.ucsd.edu)
//
///////////////////////////////////// 
// Classes declared: 
//
// Renderer:       A base class for rendering scenegraphs and models
//
// OpenGLRenderer: A class for rendering triangle models and scenegraphs using
//                 OpenGL commands
// 
///////////////////////////////////// 
// History: 2006-Winter: Written by for CSE167 Winter 2006           
/////////////////////////////////////////////////////////////////////////////
#ifndef __CSE167_RENDERER_H
#define __CSE167_RENDERER_H

#include "vector.h"
#include "scenegraph.h"

/////////////////////////////////////////////////////////////////////////////
// Renderer

class Renderer
{
    public:
        virtual void Render(Scene* scene) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// OpenGLRenderer
class OpenGLRenderer : public Renderer
{
////////////////////////////////
// Constructor/Destructor
    public:
        OpenGLRenderer();

////////////////////////////////
// Lcoal Procedures
    public:
        void Render(Scene *pScene);
        static void DrawModel(Geometry *pGeometry);
    private:
        void DrawNode(Node* n);
////////////////////////////////
// Member Variables
    private:
        void DrawLights(LightList *lights);
};

#endif
