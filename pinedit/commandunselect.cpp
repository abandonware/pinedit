/***************************************************************************
                          commandunselect.cpp  -  description
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
#include "commandunselect.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia
#include "Private.h"
#include "Shape3D.h"


CommandUnSelect::CommandUnSelect(PinEditDoc * doc) : Command(doc) {
}

CommandUnSelect::~CommandUnSelect() {
}

void CommandUnSelect::clearObjects() {
}

void CommandUnSelect::execute(const CommandContext & context) {
	assert(context.shape != NULL);

	CommandContext ct = context;
	//p_Context = new CommandContext(context);

	switch (ct.type) {
	case XY: ct.z1 = -1000; ct.z2 = 1000; break;
	case XZ: ct.y1 = -1000; ct.y2 = 1000; break;
	case ZY: ct.x1 = -1000; ct.x2 = 1000; break;
	default: EM_CERR("unknown type in commandselect::execute");
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
		  p_Doc->unSelectVertex(index);
		}
		index++;
		vtx = ct.shape->getVertex3D(index);
	}
	p_Doc->doSelectPolygons();
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
	EM_CERR("CommandUnSelect::execute from " << ct.x1 <<" "<< ct.y1 <<" "<< ct.z1 << 
		" to " << ct.x2 <<"  "<< ct.y2 <<" "<< ct.z2);
}

void CommandUnSelect::preview(const CommandContext & context, View2D * view2d) {
	view2d->getPainter()->setPen(Qt::blue);
	view2d->getPainter()->drawRect(context.sx1, context.sy1, 
				       context.sx2 - context.sx1, context.sy2 - context.sy1);
	EM_CERR("CommandUnSelect::preview");
}

void CommandUnSelect::undo() {
	EM_CERR("CommandUnSelect::undo TODO");
}

Command * CommandUnSelect::build() {
	return new CommandUnSelect(p_Doc);
}
