/***************************************************************************
                          view2d.cpp  -  description
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

// general includes
#include <iostream>
#include <assert.h>
// qt includes
#include <qpainter.h>
#include <qpen.h>
#include <qmsgbox.h>
#include <qstatusbar.h>
// application includes
#include "view2d.h"
#include "pinedit.h"
#include "pineditdoc.h"
#include "command.h"
#include "pineditview.h"
// emilia includes
#include "Private.h"
#include "Engine.h"
#include "Group.h"
#include "Shape3D.h"
#include "Polygon.h"
#include "EMath.h"

View2D::View2D(int type, PinEditDoc * doc, QWidget * parent, const char * name, WFlags f) 
: QWidget(parent, name, f ) {
	assert(doc != NULL);
	p_Doc = doc;
	p_Doc->registerUpdateable(this, "polygon");

	m_iMode = EM_SHAPE_MODE;
	m_bGrid = true;
	m_fZoom = 10;
	m_iXOffset = 150;
	m_iYOffset = 120;
	m_iMouse = 0;
	m_iType = type;
	m_iX1 = m_iY1 = m_iX2 = m_iY2 = 0;
	p_Context = new CommandContext();
	p_QPainter = new QPainter(this);
	this->setBackgroundMode(PaletteBase);
}

View2D::~View2D(){
}

void View2D::mousePressEvent(QMouseEvent* e) {
	m_iX2 = m_iX1 = e->x();
	m_iY2 = m_iY1 = e->y();
	if (e->button() ==  QMouseEvent::LeftButton) {
		m_iMouse = 1;
	} else if (e->button() == QMouseEvent::RightButton) {
		m_iMouse = 2;
	} else if (e->button() == QMouseEvent::MidButton) {
		m_iMouse = 0;
		m_iXOffset = 150;
		m_iYOffset = 120;
	}
}

void View2D::mouseReleaseEvent(QMouseEvent * e) {
	m_iMouse = 0;
	m_iX2 = e->x();
	m_iY2 = e->y();
	if (e->button() ==  QMouseEvent::LeftButton) {
		CommandContext context;
		context.clear();
		Command * command = p_Doc->buildCommand();
		if (command != NULL) {
			switch (m_iType) {
			case XY: 
				context.x1 = this->localx(m_iX1);	context.x2 = this->localx(m_iX2);
				context.y1 = -this->localy(m_iY1); context.y2 = -this->localy(m_iY2);
				context.z1 = 0;             context.z2 = 0; 
				break;
			case XZ: 
				context.x1 = this->localx(m_iX1);	context.x2 = this->localx(m_iX2);
				context.y1 = 0;             context.y2 = 0;
				context.z1 = this->localy(m_iY1); context.z2 = this->localy(m_iY2); 
				break;
			case ZY: 
				context.x1 = 0;             context.x2 = 0;
				context.y1 = -this->localy(m_iY1); context.y2 = -this->localy(m_iY2);
				context.z1 = this->localx(m_iX1); context.z2 = this->localx(m_iX2); 
				break;
			}
			context.shape = p_Doc->getCurrentShape();
			context.group = p_Doc->getCurrentGroup();
			context.type = m_iType;
			if (context.group != NULL && context.shape != NULL) {
				command->execute(context);
			} else {
				QMessageBox::information( this, "Command", "No Shape selected.");
			}
		}
	} else if (e->button() == QMouseEvent::RightButton) {
	} else if (e->button() == QMouseEvent::MidButton) {
	}
	m_iX1 = m_iX2;
	m_iY1 = m_iY2;
	this->repaint();
}

void View2D::mouseMoveEvent(QMouseEvent* e) {
	if (m_iMouse == 1) {
	}
	if (m_iMouse == 2) {
		m_iXOffset += (e->x() - m_iX2);
		m_iYOffset += (e->y() - m_iY2);
	}
	m_iX2 = e->x();
	m_iY2 = e->y();
	this->repaint();
	PinEditApp::p_CurrentApp->statusBar()->message(QString().setNum(this->localx(m_iX2)) + " " + 
																								 QString().setNum(this->localy(m_iY2)));
}

void View2D::drawPolygon(Shape3D * shape, Polygon * poly, const Matrix & mtx) {
	//cerr << "View2D::drawPolygon" << endl;
	assert(shape != NULL);
	assert(poly != NULL);
	assert(shape->getPolygonIndex(poly) >= 0);
	// find first vertex
	int polyindex = 0;
	int vtxindex = poly->getIndex(polyindex);
	Vertex3D * vtx0 = shape->getVertex3D(vtxindex);
	// loop throgh the rest
	if (vtx0 != NULL) {
		polyindex++;
		vtxindex = poly->getIndex(polyindex);
		Vertex3D vtx1 = *vtx0;
		Vertex3D vtx2 = *vtx0; 
		Vertex3D vtxTrans1;
		Vertex3D vtxTrans2;
		while (vtxindex != -1) {
			vtx1 = vtx2;
			vtx2 = *(shape->getVertex3D(vtxindex));
			EMath::applyMatrix(mtx, vtx1, vtxTrans1);
			EMath::applyMatrix(mtx, vtx2, vtxTrans2);
			switch (m_iType) {
			case XY: p_QPainter->drawLine(this->screenx(vtxTrans1.x), this->screeny(-vtxTrans1.y), 
																		this->screenx(vtxTrans2.x), this->screeny(-vtxTrans2.y)); 
				break;
			case XZ: p_QPainter->drawLine(this->screenx(vtxTrans1.x), this->screeny(vtxTrans1.z), 
																		this->screenx(vtxTrans2.x), this->screeny(vtxTrans2.z)); 
				break;
			case ZY: p_QPainter->drawLine(this->screenx(vtxTrans1.z), this->screeny(-vtxTrans1.y), 
																		this->screenx(vtxTrans2.z), this->screeny(-vtxTrans2.y));
				break;
			}
			polyindex++;
			vtxindex = poly->getIndex(polyindex);
		}
		// the line from the last to the first
		vtx1 = *vtx0;
		EMath::applyMatrix(mtx, vtx1, vtxTrans1);
		EMath::applyMatrix(mtx, vtx2, vtxTrans2);
		switch (m_iType) {
		case XY: p_QPainter->drawLine(this->screenx(vtxTrans2.x), this->screeny(-vtxTrans2.y), 
																	this->screenx(vtxTrans1.x), this->screeny(-vtxTrans1.y)); 
			break;
		case XZ: p_QPainter->drawLine(this->screenx(vtxTrans2.x), this->screeny(vtxTrans2.z), 
																	this->screenx(vtxTrans1.x), this->screeny(vtxTrans1.z)); 
			break;
		case ZY: p_QPainter->drawLine(this->screenx(vtxTrans2.z), this->screeny(-vtxTrans2.y), 
																	this->screenx(vtxTrans1.z), this->screeny(-vtxTrans1.y)); 
			break;
		}
	}
}

void View2D::drawVertex(Shape3D * shape, const Vertex3D & vtx, const Matrix & mtx) {
	//cerr << "View2D::drawPolygon" << endl;
	assert(shape != NULL);
	Vertex3D vtxA;
	EMath::applyMatrix(mtx, vtx, vtxA);
	switch (m_iType) {
	case XY: p_QPainter->drawRect(this->screenx(vtxA.x)-1, this->screeny(-vtxA.y)-1, 3, 3); break;
	case XZ: p_QPainter->drawRect(this->screenx(vtxA.x)-1, this->screeny(vtxA.z)-1,	3, 3); break;
	case ZY: p_QPainter->drawRect(this->screenx(vtxA.z)-1, this->screeny(-vtxA.y)-1, 3, 3); break;
	}
}

void View2D::drawShapeMode() {
	// cerr << "View2D::drawShapeMode" << endl;
	// draw other shapes in group with lightgray
	if (p_Doc->getCurrentGroup() == NULL) return;

	int sh = 0;
	Shape3D * shape = p_Doc->getCurrentGroup()->getShape3D(sh);
	while (shape != NULL) {
		p_QPainter->setPen(Qt::lightGray);
		int index = 0;
		Vertex3D * vtx = shape->getVertex3D(index);
		while (vtx != NULL) {
			//cerr << vtx->x <<" "<< vtx->y <<" "<< vtx->z << endl;
			switch (m_iType) {
			case XY: p_QPainter->drawRect(this->screenx(vtx->x)-1, this->screeny(-vtx->y)-1, 3, 3); break;
			case XZ: p_QPainter->drawRect(this->screenx(vtx->x)-1, this->screeny(vtx->z)-1, 3, 3); break;
			case ZY: p_QPainter->drawRect(this->screenx(vtx->z)-1, this->screeny(-vtx->y)-1, 3, 3); break;
			}
			index++;
			vtx = shape->getVertex3D(index);
		}
		index = 0;
		Polygon * poly = shape->getPolygon(index);
		while (poly != NULL) {
			this->drawPolygon(shape, poly, EMath::identityMatrix);
			index++;
			poly = shape->getPolygon(index);
		}
		++sh;
		shape = p_Doc->getCurrentGroup()->getShape3D(sh);
	}
	// current shape
	shape = p_Doc->getCurrentShape();
	if (shape == NULL) {
		return;
	}
	{	// normal vertices
		p_QPainter->setPen(Qt::black);
		int index = 0;
		Vertex3D * vtx = shape->getVertex3D(index);
		while (vtx != NULL) {
			//cerr << vtx->x <<" "<< vtx->y <<" "<< vtx->z << endl;
			switch (m_iType) {
			case XY: p_QPainter->drawRect(this->screenx(vtx->x)-1, this->screeny(-vtx->y)-1, 3, 3); break;
			case XZ: p_QPainter->drawRect(this->screenx(vtx->x)-1, this->screeny(vtx->z)-1, 3, 3); break;
			case ZY: p_QPainter->drawRect(this->screenx(vtx->z)-1, this->screeny(-vtx->y)-1, 3, 3); break;
			}
			index++;
			vtx = shape->getVertex3D(index);
		}
	}	

	{ // selected vertices
		p_QPainter->setPen(Qt::red);
		int index = 0;
		Vertex3D * vtx = shape->getVertex3D(p_Doc->getSelectedVertex(index));
		while (vtx != NULL) {
			//cerr << vtx->x <<" "<< vtx->y <<" "<< vtx->z << endl;
			switch (m_iType) {
			case XY: p_QPainter->drawRect(this->screenx(vtx->x)-1, this->screeny(-vtx->y)-1, 3, 3); break;
			case XZ: p_QPainter->drawRect(this->screenx(vtx->x)-1, this->screeny(vtx->z)-1, 3, 3); break;
			case ZY: p_QPainter->drawRect(this->screenx(vtx->z)-1, this->screeny(-vtx->y)-1, 3, 3); break;
			}
			index++;
			vtx = shape->getVertex3D(p_Doc->getSelectedVertex(index));
		}
		vtx = shape->getVertex3D(p_Doc->getSelectedVertexExtra());
		if (vtx != NULL) {
			switch (m_iType) {
			case XY: p_QPainter->drawRect(this->screenx(vtx->x)-2, this->screeny(-vtx->y)-1, 5, 5); break;
			case XZ: p_QPainter->drawRect(this->screenx(vtx->x)-2, this->screeny(vtx->z)-1, 5, 5); break;
			case ZY: p_QPainter->drawRect(this->screenx(vtx->z)-2, this->screeny(-vtx->y)-1, 5, 5); break;
			}
		}
	}

	{ // normal polygons
		p_QPainter->setPen(Qt::black);
		int index = 0;
		Polygon * poly = shape->getPolygon(index);
		while (poly != NULL) {
			this->drawPolygon(shape, poly, EMath::identityMatrix);
			index++;
			poly = shape->getPolygon(index);
		}
	}

	{ // selected polygons
		p_QPainter->setPen(Qt::red);
		int index = 0;
		Polygon * poly = p_Doc->getSelectedPolygon(index);
		while (poly != NULL) {
			this->drawPolygon(shape, poly, EMath::identityMatrix);
			index++;
			poly = p_Doc->getSelectedPolygon(index);
		}
	}

	CommandContext context;
	context.clear();
	Command * command = p_Doc->buildCommand();
	if (command != NULL) {
		switch (m_iType) {
		case XY: 
			context.x1 = this->localx(m_iX1);	context.x2 = this->localx(m_iX2);
			context.y1 = -this->localy(m_iY1); context.y2 = -this->localy(m_iY2);
			context.z1 = 0;             context.z2 = 0; 
			break;
		case XZ: 
			context.x1 = this->localx(m_iX1);	context.x2 = this->localx(m_iX2);
			context.y1 = 0;             context.y2 = 0;
			context.z1 = this->localy(m_iY1); context.z2 = this->localy(m_iY2); 
			break;
		case ZY: 
			context.x1 = 0;             context.x2 = 0;
			context.y1 = -this->localy(m_iY1); context.y2 = -this->localy(m_iY2);
			context.z1 = this->localx(m_iX1); context.z2 = this->localx(m_iX2); 
			break;
		}
		context.sx1 = m_iX1;
		context.sy1 = m_iY1;
		context.sx2 = m_iX2;
		context.sy2 = m_iY2;
		context.shape = p_Doc->getCurrentShape();
		context.group = p_Doc->getCurrentGroup();
		context.type = m_iType;
		command->preview(context, this);
	}
}

void View2D::drawGroupMode() {
	//cerr << "View2D::drawGroupMode" << endl;
	Matrix mtx = EMath::identityMatrix;
	// draw all groups
	this->drawGroup(p_Doc->getEngine(), mtx);
}

/* input: group to draw, matrix stack before applying this group */
void View2D::drawGroup(Group * g, const Matrix & mtxP) {
	//cerr << "View3D::drawGroup" << endl;
	Matrix mtxT;
	EMath::matrixMulti(g->m_mtxSrc, mtxP, mtxT);
	// draw a cross to notate the centre of the group
	if (g == p_Doc->getCurrentGroup()) {
		p_QPainter->setPen(Qt::red);
	} else {
		p_QPainter->setPen(Qt::black);
	}
	switch (m_iType) {
	case XY: 
		p_QPainter->drawLine(this->screenx(mtxT.t[0])-2, this->screeny(-mtxT.t[1]), 
												 this->screenx(mtxT.t[0])+2, this->screeny(-mtxT.t[1]));
		p_QPainter->drawLine(this->screenx(mtxT.t[0]), this->screeny(-mtxT.t[1])-2, 
												 this->screenx(mtxT.t[0]), this->screeny(-mtxT.t[1])+2); break;
	case XZ: 
		p_QPainter->drawLine(this->screenx(mtxT.t[0])-2, this->screeny(mtxT.t[2]),
												 this->screenx(mtxT.t[0])+2, this->screeny(mtxT.t[2]));
		p_QPainter->drawLine(this->screenx(mtxT.t[0]), this->screeny(mtxT.t[2])-2,
												 this->screenx(mtxT.t[0]), this->screeny(mtxT.t[2])+2); break;
	case ZY: 
		p_QPainter->drawLine(this->screenx(mtxT.t[2])-2, this->screeny(-mtxT.t[1]),
												 this->screenx(mtxT.t[2])+2, this->screeny(-mtxT.t[1]));
		p_QPainter->drawLine(this->screenx(mtxT.t[2]), this->screeny(-mtxT.t[1])-2,
												 this->screenx(mtxT.t[2]), this->screeny(-mtxT.t[1])+2); break;
	}

	// draw all polygons
	int shindex = 0;
	Shape3D * shape = g->getShape3D(shindex);
	while (shape != NULL) {
		int polyindex = 0;
		Polygon * poly = shape->getPolygon(polyindex);
		while (poly != NULL) {
			this->drawPolygon(shape, poly, mtxT);
			polyindex++;
			poly = shape->getPolygon(polyindex);
		}
		shindex++;
		shape = g->getShape3D(shindex);
	}

	CommandContext context;
	context.clear();
	Command * command = p_Doc->buildCommand();
	if (command != NULL) {
		switch (m_iType) {
		case XY: 
			context.x1 = this->localx(m_iX1);	context.x2 = this->localx(m_iX2);
			context.y1 = -this->localy(m_iY1); context.y2 = -this->localy(m_iY2);
			context.z1 = 0;             context.z2 = 0; 
			break;
		case XZ: 
			context.x1 = this->localx(m_iX1);	context.x2 = this->localx(m_iX2);
			context.y1 = 0;             context.y2 = 0;
			context.z1 = this->localy(m_iY1); context.z2 = this->localy(m_iY2); 
			break;
		case ZY: 
			context.x1 = 0;             context.x2 = 0;
			context.y1 = -this->localy(m_iY1); context.y2 = -this->localy(m_iY2);
			context.z1 = this->localx(m_iX1); context.z2 = this->localx(m_iX2); 
			break;
		}
		context.sx1 = m_iX1;
		context.sy1 = m_iY1;
		context.sx2 = m_iX2;
		context.sy2 = m_iY2;
		context.shape = p_Doc->getCurrentShape();
		context.group = p_Doc->getCurrentGroup();
		context.type = m_iType;
		command->preview(context, this);
	}
	// TODO recurse the temporary movement to child groups
	int index = 0;
	Group * group = g->getGroup(index);
	while (group != NULL) {
		this->drawGroup(group, mtxT);
		index++;
		group = g->getGroup(index);
	}
}

void View2D::drawGrid() {
	//cerr << "View2D::drawGrid" << endl;
	p_QPainter->setPen(Qt::lightGray);
	float step = m_fZoom;
	float xoffset = (m_iXOffset-150)%(int)m_fZoom;
	float yoffset = (m_iYOffset-120)%(int)m_fZoom;
	for (float x=150; x<300; x+=step) {
		p_QPainter->drawLine((int)(x+xoffset), 0, (int)(x+xoffset), 240);
	}
	for (float x=150-step; x>0; x-=step) {
		p_QPainter->drawLine((int)(x+xoffset), 0, (int)(x+xoffset), 240);
	}
	for (float y=120; y<240; y+=step) {
		p_QPainter->drawLine(0, (int)(y+yoffset), 300, (int)(y+yoffset));
	}
	for (float y=120-step; y>0; y-=step) {
		p_QPainter->drawLine(0, (int)(y+yoffset), 300, (int)(y+yoffset));
	}

	p_QPainter->setPen(Qt::darkGray);
	p_QPainter->drawLine(this->screenx(-100), this->screeny(0), this->screenx(100), this->screeny(0));
	p_QPainter->drawLine(this->screenx(0), this->screeny(-100), this->screenx(0), this->screeny(100));
}

// this is the function who draws stuff to the screen
void View2D::paintEvent(QPaintEvent * e) {
	//
	if (m_bGrid) {
		this->drawGrid();
	}
	if (m_iMode == EM_SHAPE_MODE) {
		this->drawShapeMode();
	} else if (m_iMode == EM_GROUP_MODE) {
		this->drawGroupMode();
	}

	//cerr << "view2d::paintevent" << endl;
}

void View2D::doUpdate() {
	this->repaint();
}
