/***************************************************************************
                          commandrotategroup.cpp  -  description
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
#include "commandrotategroup.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Shape3D.h"

CommandRotateGroup::CommandRotateGroup(PinEditDoc * doc) : Command(doc) {
}

CommandRotateGroup::~CommandRotateGroup() {
}

void CommandRotateGroup::clearObjects() {
}

void CommandRotateGroup::execute(const CommandContext & context) {
	assert(context.group != NULL);
	p_Context->copy(context);

	context.group->getRotation(m_vtxRot.x, m_vtxRot.y, m_vtxRot.z);
	float dx = context.x2 - context.x1;
	float dz = context.z2 - context.z1;
	switch (context.type) {
	case XY: context.group->addRotation(0, 0, dx/PE_ROTATION_FACTOR);	break;
	case XZ: context.group->addRotation(0, dx/PE_ROTATION_FACTOR, 0);	break;
	case ZY: context.group->addRotation(dz/PE_ROTATION_FACTOR, 0, 0);	break;
	}
	
	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll("group");
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
	cerr << "CommandRotateGroup::execute from " << context.x1 <<" "<< context.y1 <<" "<< context.z1 << 
		" to " << context.x2 <<"  "<< context.y2 <<" "<< context.z2 << endl;
}

void CommandRotateGroup::preview(const CommandContext & context, View2D * view2d) {
	cerr << "CommandRotateGroup::preview" << endl;
	if (context.group == NULL) return;

	Matrix mtxA = EMath::identityMatrix;
	Matrix mtxB = EMath::identityMatrix;
	Matrix mtxC = EMath::identityMatrix;

	Group * g = context.group;
	// build matrix for temporary translation
	Vertex3D vtxT, vtxR;
	g->getRotation(vtxR.x, vtxR.y, vtxR.z);
	g->getTranslation(vtxT.x, vtxT.y, vtxT.z);
	switch (context.type) {
	case XY: vtxR.z += (context.x2-context.x1)/PE_ROTATION_FACTOR; break;
	case XZ: vtxR.y += (context.x2-context.x1)/PE_ROTATION_FACTOR; break;
	case ZY: vtxR.x += (context.z2-context.z1)/PE_ROTATION_FACTOR; break;
	}
	EMath::getTransformationMatrix(mtxC, vtxT, vtxR);
	// build backwards matrix stack
	g = g->getParent();
	while (g != NULL) {
		mtxB = mtxC;
		mtxA = g->m_mtxSrc;
		EMath::matrixMulti(mtxB, mtxA, mtxC);
		g = g->getParent();
	}
	g = context.group;
	// draw all polygons
	view2d->getPainter()->setPen(Qt::green);
	int shindex = 0;
	Shape3D * shape = g->getShape3D(shindex);
	while (shape != NULL) {
		int polyindex = 0;
		Polygon * poly = shape->getPolygon(polyindex);
		while (poly != NULL) {
			view2d->drawPolygon(shape, poly, mtxB);
			polyindex++;
			poly = shape->getPolygon(polyindex);
		}
		shindex++;
		shape = g->getShape3D(shindex);
	}
	cerr << "CommandRotateGroup::preview" << endl;
}

void CommandRotateGroup::undo() {
	cerr << "CommandRotateGroup::undo" << endl;
	assert(p_Context->group != NULL);
	p_Context->group->setRotation(m_vtxRot.x, m_vtxRot.y, m_vtxRot.z);
	p_Doc->updateAll("group");
	p_Doc->updateAll("polygon");
}

Command * CommandRotateGroup::build() {
	cerr << "CommandRotateGroup::build" << endl;
	return new CommandRotateGroup(p_Doc);
}
