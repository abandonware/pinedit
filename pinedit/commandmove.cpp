/***************************************************************************
                          commandmove.cpp  -  description
                             -------------------
    begin                : Fri Apr 12 2002
    copyright            : (C) 2002 by Henrik Enqvist
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

// qt includes
#include <qpainter.h>
// application includes
#include "commandmove.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"

CommandMove::CommandMove(PinEditDoc * doc) : Command(doc) {
}

CommandMove::~CommandMove() {
}

void CommandMove::clearObjects() {
}

void CommandMove::execute(const CommandContext & context) {
	assert(context.shape != NULL);
	p_Context->copy(context);
	
	float dx = context.x2 - context.x1;
	float dy = context.y2 - context.y1;
	float dz = context.z2 - context.z1;
	int index = 0;
	Vertex3D * vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	while (vtx != NULL) {
		m_vVertex.push_back(*vtx);
		m_vIndex.push_back(p_Doc->getSelectedVertex(index));
		vtx->x += dx;
		vtx->y += dy;
		vtx->z += dz;
		index++;
		vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	}

	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
	EM_CERR("move vertices from " << context.x1 <<" "<< context.y1 <<" "<< context.z1 << 
		" to " << context.x2 <<"  "<< context.y2 <<" "<< context.z2);
}

void CommandMove::preview(const CommandContext & context, View2D * view2d) {
	if (context.shape == NULL) return;
	p_Context->copy(context);
	// build matrix stack for temporary translation
	// mtxB is global rotion matrix, mtxC fixes the translation in local rotation
	// mtxC is the final matrix
	Matrix mtxA = EMath::identityMatrix;
	Vertex3D vtxTA = {0,0,0}, vtxRA = {0,0,0};
	vtxTA.x = context.x2 - context.x1;	
	vtxTA.y = context.y2 - context.y1;	
	vtxTA.z = context.z2 - context.z1;	
	EMath::getTransformationMatrix(mtxA, vtxTA, vtxRA);

	// draw selected polygons
	view2d->getPainter()->setPen(Qt::green);
	int index = 0;
	Polygon3D * poly = p_Doc->getSelectedPolygon(index);
	while (poly != NULL) {
		view2d->drawPolygon(context.shape, poly, mtxA);
		index++;
		poly = p_Doc->getSelectedPolygon(index);
	}
	// draw selected vertices
	index = 0;
	Vertex3D * vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	while (vtx != NULL) {
		// the matrix will rotate and reapply the translation
		view2d->drawVertex(context.shape, *vtx, mtxA);
		index++;
		vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	}
	EM_CERR("commandmove::preview");
}

void CommandMove::undo() {
	EM_CERR("CommandMove::undo");
	assert(p_Context->shape != NULL);
	assert(m_vVertex.size() == m_vIndex.size());
	vector<int>::iterator indexiter = m_vIndex.begin();
	vector<int>::iterator indexend = m_vIndex.end();
	vector<Vertex3D>::iterator vtxiter = m_vVertex.begin();
	for (; indexiter != indexend; ++indexiter, ++vtxiter) {
		Vertex3D * vtx = p_Context->shape->getVertex3D(*indexiter);
		assert(vtx != NULL);
		vtx->x = (*vtxiter).x;
		vtx->y = (*vtxiter).y;
		vtx->z = (*vtxiter).z;
	}
	p_Doc->updateAll("polygon");
}

Command * CommandMove::build() {
	EM_CERR("CommandMove::build");
	return new CommandMove(p_Doc);
}
