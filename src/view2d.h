/***************************************************************************
                          view2d.h  -  description
                             -------------------
    begin                : Wed Apr 10 2002
    copyright            : (C) 2002 by Henrik Enqvist IB
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

#ifndef VIEW2D_H
#define VIEW2D_H

// qt includes
#include <qwidget.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPaintEvent>
// application includes
#include "pineditdoc.h"

class PinEditDoc;
class QPaintEvent;
class QPen;
class QPainter;
class CommandContext;
class Polygon3D;
class Group;

/** @author Henrik Enqvist IB */
class View2D : public QWidget, public Updateable {
	Q_OBJECT        // must include this if you use Qt signals/slots
 public:
	View2D(int type, PinEditDoc * doc, QWidget * parent, const char * name, Qt::WFlags f) ;
	~View2D();
	void resizeEvent(QResizeEvent * e);
	void mousePressEvent(QMouseEvent * e);
	void mouseMoveEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void setMode(int mode) { m_iMode = mode; };
	void setZoom(int zoom) { m_fZoom = zoom; };
	void showGrid(bool grid) { m_bGrid = grid; };
	void paintEvent(QPaintEvent * e);
	void doUpdate();
	inline int screenx(float x) { return (int)(x*m_fZoom + m_iXOffset); };
	inline int screeny(float y) { return (int)(y*m_fZoom + m_iYOffset); };
	inline float localx(int x) { return (float)(x - m_iXOffset) / m_fZoom; };
	inline float localy(int y) { return (float)(y - m_iYOffset) / m_fZoom; };
    void drawGroup(QPainter &painter, Group * g, const Matrix & mtx);
    void drawPolygon(QPainter &painter, Shape3D * shape, Polygon3D * poly, const Matrix & mtx);
    void drawVertex(QPainter &painter, Shape3D * shape, const Vertex3D & vtx, const Matrix & mtx);
 protected:
    void drawShapeMode(QPainter &painter);
    void drawGroupMode(QPainter &painter);
    void drawGrid(QPainter &painter);
	int m_iMode;
	bool m_bGrid;
	CommandContext * p_Context;
	PinEditDoc * p_Doc;
	float m_fZoom;
	int m_iXOffset;
	int m_iYOffset;
	int m_iX1, m_iX2;
	int m_iY1, m_iY2;
	int m_iMouse;
	int m_iType;
};

#endif
