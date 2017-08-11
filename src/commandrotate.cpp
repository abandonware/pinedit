/***************************************************************************
                          commandrotate.cpp  -  description
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
#include "commandrotate.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"

CommandRotate::CommandRotate(PinEditDoc * doc) : Command(doc) {
}

CommandRotate::~CommandRotate() {
}

void CommandRotate::execute(const CommandContext & context) {
	assert(context.shape != NULL);
	EM_CERR("CommandRotate::execute");
	p_Context->copy(context);

	Matrix mtxA = EMath::identityMatrix;
	Vertex3D vtxTA = {0,0,0}, vtxRA = {0,0,0}, vtxSA = {1,1,1};
	switch (context.type) {
	case XY: vtxRA.z = (context.x2-context.x1)/PE_ROTATION_FACTOR; break;
	case XZ: vtxRA.y = (context.x2-context.x1)/PE_ROTATION_FACTOR; break;
	case ZY: vtxRA.x = (context.z2-context.z1)/PE_ROTATION_FACTOR; break;
	}
	EMath::getTransformationMatrix(mtxA, vtxTA, vtxRA, vtxSA);

	int index = 0;
	Vertex3D * vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	Vertex3D vtxTmp;
	while (vtx != NULL) {
		m_vVertex.push_back(*vtx);
		m_vIndex.push_back(p_Doc->getSelectedVertex(index));
		EMath::applyMatrixRot(mtxA, *vtx, vtxTmp);
		*vtx = vtxTmp;
		index++;
		vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	}

	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
}

void CommandRotate::preview(const CommandContext & context, View2D * view2d, QPainter &painter) {
	EM_CERR("CommandRotate::preview");
    if (context.shape == NULL) return;
	// build matrix stack for temporary translation
	// mtxB is global rotion matrix, mtxC fixes the translation in local rotation
	// mtxC is the final matrix
	Matrix mtxA = EMath::identityMatrix;
	Vertex3D vtxTA = {0,0,0}, vtxRA = {0,0,0}, vtxSA = {1,1,1};
	
	switch (context.type) {
	case XY: vtxRA.z = (context.x2-context.x1)/PE_ROTATION_FACTOR; break;
	case XZ: vtxRA.y = (context.x2-context.x1)/PE_ROTATION_FACTOR; break;
	case ZY: vtxRA.x = (context.z2-context.z1)/PE_ROTATION_FACTOR; break;
	}
	EMath::getTransformationMatrix(mtxA, vtxTA, vtxRA, vtxSA);

	// draw selected polygons
    painter.setPen(Qt::green);
	int index = 0;
	Polygon3D * poly = p_Doc->getSelectedPolygon(index);
	while (poly != NULL) {
        view2d->drawPolygon(painter, context.shape, poly, mtxA);
		index++;
		poly = p_Doc->getSelectedPolygon(index);
	}
	// draw selected vertices
	index = 0;
	Vertex3D * vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
	while (vtx != NULL) {
		// the matrix will rotate and reapply the translation
        view2d->drawVertex(painter, context.shape, *vtx, mtxA);
		index++;
		vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index));
    }
}

void CommandRotate::undo() {
	EM_CERR("CommandRotate::undo");
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

Command * CommandRotate::build() {
	EM_CERR("CommandRotate::build");
	return new CommandRotate(p_Doc);
}
