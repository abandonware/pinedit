/***************************************************************************
                          glengine.cpp  -  description
                             -------------------
    begin                : Thu Nov 29 2001
    copyright            : (C) 2001 by Henrik Enqvist
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
#include <SDL_opengl.h>
#include <cassert>
// qt includes
#include <qevent.h>
//Added by qt3to4:
#include <QMouseEvent>
// application includes
#include "glengine.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Engine.h"
#include "Config.h"

/** The a class for providing the emilia engine with an OpenGL driver. 
 * The emilia engine is in pineditdoc.cpp */
GLEngine::GLEngine(QGLFormat & format, QWidget *parent, const char *name, PinEditDoc * doc) 
  : QGLWidget(format, parent, name) {
  assert(doc != NULL);
  p_Doc = doc;
  p_Doc->registerUpdateable(this, "polygon");
  m_qRot.x = 0.0f;
  m_qRot.y = 0.0f;
  m_qRot.z = 0.0f;
  m_qRot.w = 1.0f;
  EM_CERR("glengine::glengine");
}

GLEngine::~GLEngine(){
}

void GLEngine::initializeGL() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
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
  
  // EM_CERR("paint");
}

void GLEngine::mouseMoveEvent(QMouseEvent * event) {
  int x = event->x();
  int y = event->y();
  Vertex3D vtxS = {1,1,1};
  //EM_CERR("mouse moved" << x - m_MouseX <<" "<< y - m_MouseY);
  switch(m_ButtonState) {
  case Qt::LeftButton:
    Quaternion qRot, qTmp;
    Vertex3D vtxU, vtxV, vtxT;
    vtxT.x = 0.0f;
    vtxT.y = 0.0f;
    vtxT.z = 0.0f;
    vtxU.x = 0.0f;
    vtxU.y = 0.0f;
    vtxU.z = 1.0f;
    vtxV.x = (x - m_MouseX)/100.0f;
    vtxV.y = (m_MouseY - y)/100.0f;
    vtxV.z = 1.0f;
    
    /*
    vtxU.x = (float)(Config::getInstance()->getWidthDiv2() - x) / 100.0f;
    vtxU.y = (float)(y - Config::getInstance()->getHeightDiv2()) / 100.0f;
    vtxU.z = 1.0f - EM_ABS(vtxU.x) - EM_ABS(vtxU.y);
    if (vtxU.z < 0.0f) vtxU.z = 0.0f;
    vtxV.x = (float)(Config::getInstance()->getWidthDiv2() - m_MouseX) / 100.0f;
    vtxV.y = (float)(m_MouseY - Config::getInstance()->getHeightDiv2()) / 100.0f;
    vtxV.z = 1.0f - EM_ABS(vtxV.x) - EM_ABS(vtxV.y);
    if (vtxV.z < 0.0f) vtxV.z = 0.0f;
    */
    EMath::rotationArc(vtxU, vtxV, qRot);

    EMath::quaternionMulti(qRot, m_qRot, qTmp);
    m_qRot = qTmp;

    EMath::getTransformationMatrix(p_Doc->getCameraRot()->m_mtxSrc, vtxT, m_qRot, vtxS);

    //p_Doc->getCameraRot()->setRotation(vtxRot.x, vtxRot.y, vtxRot.z);
    break;
  case Qt::MidButton: {
    Vertex3D vtxA, vtxB;
    vtxA.x = (float)(m_MouseX-x)/10;
    vtxA.y = 0;
    vtxA.z = (float)(m_MouseY-y)/10;
    EMath::applyMatrixRot(p_Doc->getCameraRot()->m_mtxSrc, vtxA, vtxB);
    p_Doc->getCameraTrans()->addTranslation(vtxB.x, vtxB.y, vtxB.z);
  } break;
  case Qt::RightButton: {
    Vertex3D vtxA, vtxB;
    vtxA.x = (float)(m_MouseX-x)/10;
    vtxA.y = -(float)(m_MouseY-y)/10;
    vtxA.z = 0.0f;
    EMath::applyMatrixRot(p_Doc->getCameraRot()->m_mtxSrc, vtxA, vtxB);
    p_Doc->getCameraTrans()->addTranslation(vtxB.x, vtxB.y, vtxB.z);
  } break;
  default: break;
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
