/***************************************************************************
                          glengine.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Henrik Enqvist IB
    email                : henqvist@excite.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// general includes
#include <GL/gl.h>
#include <cassert>
// qt includes
#include <qevent.h>
// application includes
#include "glengine.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Engine.h"

/** The a class for providing the emilia engine with an OpenGL driver. 
 * The emilia engine is in pineditdoc.cpp */
GLEngine::GLEngine(QGLFormat & format, QWidget *parent, const char *name, PinEditDoc * doc) 
: QGLWidget(format, parent, name) {
	assert(doc != NULL);
	p_Doc = doc;
	p_Doc->registerUpdateable(this, "polygon");
	m_RotX = 0;
	m_RotY = 0;
	m_RotZ = 0;
	cerr << "glengine::glengine" << endl;
}

GLEngine::~GLEngine(){
}

void GLEngine::initializeGL() {
	glClearColor(0.0, 0.1, 0.3, 0.0);
	glClearDepth(1.0);
 	
 	glEnable(GL_CULL_FACE);
 	glCullFace(GL_BACK);
 	glFrontFace(GL_CW);
	
 	glEnable(GL_DEPTH_TEST);
 	glDepthFunc(GL_LESS);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 200);
	glMatrixMode(GL_MODELVIEW);
}

void GLEngine::resizeGL(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 200);
	glMatrixMode(GL_MODELVIEW);
}

void GLEngine::paintGL() {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glColor3f(1, 1, 1);
	glLoadIdentity();
  gluLookAt(0,0,0, 0,0,-1, 0,1,0);

  p_Doc->getEngine()->tick();
  p_Doc->getEngine()->render();

  // cerr << "paint" << endl;
}

void GLEngine::mouseMoveEvent(QMouseEvent * event) {
	int x = event->x();
	int y = event->y();
	//cerr << "mouse moved" << x - m_MouseX <<" "<< y - m_MouseY << endl;
	switch(m_ButtonState) {
	case LeftButton:
		m_RotY += (float)(x-m_MouseX)/200;
		m_RotX += (float)(y-m_MouseY)/200;
		p_Doc->getCameraRot()->setRotation(m_RotX, m_RotY, m_RotZ);
		break;
	case RightButton:
		p_Doc->getCameraTrans()->addTranslation(0, 0, (float)(m_MouseY-y)/10);
		break;
	case MidButton:
		p_Doc->getCameraTrans()->addTranslation((float)(m_MouseX-x)/10, (float)(y-m_MouseY)/10, 0);
		break;
	}
	m_MouseX = x;
	m_MouseY = y;
	
	this->updateGL();
}

void GLEngine::mousePressEvent(QMouseEvent * event) {
	m_ButtonState = event->button();
	m_MouseX = event->x();
	m_MouseY = event->y();
}

void GLEngine::doUpdate() {
	this->updateGL();
}
