/***************************************************************************
                          glengine.h  -  description
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

#ifndef GLENGINE_H
#define GLENGINE_H

// qt includes
#include <qgl.h>
// application includes
#include "pineditdoc.h"

class QMouseEvent;
class PinEditDoc;

/** The GLEngine class provides the OpenGL implementation for the emilia engine. 
 ** @author Henrik Enqvist IB */
class GLEngine : public QGLWidget, public Updateable  {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	GLEngine(QGLFormat & format, QWidget * parent, const char * name, PinEditDoc * doc);
	~GLEngine();

 protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	void mouseMoveEvent(QMouseEvent * event);
	void mousePressEvent(QMouseEvent * event);
	void doUpdate();
		
 private:
	PinEditDoc * p_Doc;
	int m_MouseX;
	int m_MouseY;
	float m_RotX;
	float m_RotY;
	float m_RotZ;
	ButtonState m_ButtonState;
};

#endif
