/***************************************************************************
                          commandaddselect.cpp  -  description
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
#include "commandaddselect.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"

CommandAddSelect::CommandAddSelect(PinEditDoc * doc) : Command(doc) {
}

CommandAddSelect::~CommandAddSelect() {
}

void CommandAddSelect::clearObjects() {
}

void CommandAddSelect::execute(const CommandContext & context) {
	cerr << "CommandAddSelect::execute " << endl;
	assert(context.shape != NULL);

	CommandContext ct = context;

	switch (ct.type) {
	case XY: ct.z1 = -1000; ct.z2 = 1000; break;
	case XZ: ct.y1 = -1000; ct.y2 = 1000; break;
	case ZY: ct.x1 = -1000; ct.x2 = 1000; break;
	default: cerr << "CommandAddSelect::execute unknown type" << endl;
	}

	int index = 0;
	Vertex3D * vtx = ct.shape->getVertex3D(index);
	while (vtx != NULL) {
		if ( ((vtx->x >= ct.x1 && vtx->x <= ct.x2) || 
					(vtx->x >= ct.x2 && vtx->x <= ct.x1)) &&
				 ((vtx->y >= ct.y1 && vtx->y <= ct.y2) || 
					(vtx->y >= ct.y2 && vtx->y <= ct.y1)) &&
				 ((vtx->z >= ct.z1 && vtx->z <= ct.z2) || 
					(vtx->z >= ct.z2 && vtx->z <= ct.z1)) ) {
			p_Doc->selectVertex(index);
		}
		index++;
		vtx = ct.shape->getVertex3D(index);
	}
	p_Doc->doSelectPolygons();
	p_Doc->updateAll("polygon");
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	// this one reports for some strange reason that all are zero ???
	// but selection is made correct !!!
	cerr << "CommandAddSelect::execute " << context.x1 <<" "<< context.y1 <<" "<< context.z1 << 
		" to " << context.x2 <<"  "<< context.y2 <<" "<< context.z2 << endl;
}

void CommandAddSelect::preview(const CommandContext & context, View2D * view2d) {
	cerr << "CommandAddSelect::preview" << endl;
	view2d->getPainter()->setPen(Qt::blue);
	view2d->getPainter()->drawRect(context.sx1, context.sy1, 
																 context.sx2 - context.sx1, context.sy2 - context.sy1);
}

void CommandAddSelect::undo() {
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();
	p_Doc->updateAll("polygon");
}

Command * CommandAddSelect::build() {
	return new CommandAddSelect(p_Doc);
}
