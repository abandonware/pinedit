/***************************************************************************
                          commandmovegroup.cpp  -  description
                             -------------------
    begin                : Fri Apr 12 2002
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

// qt includes
#include <qpainter.h>
// application includes
#include "view2d.h"
#include "commandmovegroup.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Shape3D.h"

CommandMoveGroup::CommandMoveGroup(PinEditDoc * doc) : Command(doc) {
}

CommandMoveGroup::~CommandMoveGroup() {
}

void CommandMoveGroup::clearObjects() {
}

void CommandMoveGroup::execute(const CommandContext & context) {
	assert(context.group != NULL);

	float dx = context.x2 - context.x1;
	float dy = context.y2 - context.y1;
	float dz = context.z2 - context.z1;
	context.group->addTranslation(dx, dy, dz);

	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll("group");
	p_Doc->pushUndo(this);
	cerr << "move group from " << context.x1 <<" "<< context.y1 <<" "<< context.z1 << 
		" to " << context.x2 <<"  "<< context.y2 <<" "<< context.z2 << endl;
}

void CommandMoveGroup::preview(const CommandContext & context, View2D * view2d) {
	if (context.group == NULL) return;

	Matrix mtxA = EMath::identityMatrix;
	Matrix mtxB = EMath::identityMatrix;
	Matrix mtxC = EMath::identityMatrix;

	Group * g = context.group;
	// build matrix for temporary translation
	Vertex3D vtxT, vtxR;
	g->getRotation(vtxR.x, vtxR.y, vtxR.z);
	g->getTranslation(vtxT.x, vtxT.y, vtxT.z);
	vtxT.x += context.x2 - context.x1;	
	vtxT.y += context.y2 - context.y1;	
	vtxT.z += context.z2 - context.z1;
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
			view2d->drawPolygon(shape, poly, mtxC);
			polyindex++;
			poly = shape->getPolygon(polyindex);
		}
		shindex++;
		shape = g->getShape3D(shindex);
	}
	cerr << "CommandMoveGroup::preview" << endl;
}

void CommandMoveGroup::undo() {
}

Command * CommandMoveGroup::build() {
	return new CommandMoveGroup(p_Doc);
}
