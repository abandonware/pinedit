/***************************************************************************
                          commandselect.cpp  -  description
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
#include "commandselect.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"


CommandSelect::CommandSelect(PinEditDoc * doc) : Command(doc) {
}

CommandSelect::~CommandSelect() {
}

void CommandSelect::clearObjects() {
}

void CommandSelect::execute(const CommandContext & context) {
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();

	CommandContext ct = context;
	//p_Context = new CommandContext(context);

	switch (context.type) {
	case XY: ct.z1 = -1000; ct.z2 = 1000; break;
	case XZ: ct.y1 = -1000; ct.y2 = 1000; break;
	case ZY: ct.x1 = -1000; ct.x2 = 1000; break;
	default: EM_CERR("CommandSelect::execute unknown type");
	}

	Shape3D * shape = p_Doc->getCurrentShape();
	if (shape == NULL) {
		EM_CERR("CommandSelect::execute no shape selected");
		return;
	}
	int index = 0;
	Vertex3D * vtx = shape->getVertex3D(index);
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
		vtx = shape->getVertex3D(index);
	}
	p_Doc->doSelectPolygons();
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
	// this one reports for some strange reason that all are zero ???
	// but selection is made correct !!!
	EM_CERR("CommandSelect::execute select vertices at " << 
		context.x1 <<" "<< context.y1 <<" "<< context.z1 << 
		" to " << context.x2 <<"  "<< context.y2 <<" "<< context.z2);
}

void CommandSelect::preview(const CommandContext & context, View2D * view2d) {
	EM_CERR("CommandSelect::drawpreview");
	view2d->getPainter()->setPen(Qt::blue);
	view2d->getPainter()->drawRect(context.sx1, context.sy1, 
										 context.sx2 - context.sx1, context.sy2 - context.sy1);
}

void CommandSelect::undo() {
	EM_CERR("CommandSelect::undo");
	p_Doc->clearSelectedPolygon();
	p_Doc->clearSelectedVertex();
	p_Doc->updateAll("polygon");
}

Command * CommandSelect::build() {
	EM_CERR("CommandSelect::build");
	return new CommandSelect(p_Doc);
}
