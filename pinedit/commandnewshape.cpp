/***************************************************************************
                          commandnewshape.cpp  -  description
                             -------------------
    begin                : Thu Apr 11 2002
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

// application includes
#include "commandnewshape.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Shape3D.h"

CommandNewShape::CommandNewShape(PinEditDoc * doc) : Command(doc) {
}

CommandNewShape::~CommandNewShape() {
}

void CommandNewShape::clearObjects() {
}

void CommandNewShape::execute(const CommandContext & context) {
	assert(context.group != NULL);
	EM_CERR("CommandNewShape::execute");
	p_Context->copy(context);

	p_Context->shape = new Shape3D();
	context.group->addShape3D(p_Context->shape);
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();
	p_Doc->setCurrentShape(p_Context->shape);
	p_Doc->setModified(true);
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("polygon");
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
}

void CommandNewShape::undo() {
	EM_CERR("CommandNewShape::undo");
	assert(p_Context->group != NULL);
	assert(p_Context->shape != NULL);
	p_Context->group->removeShape3D(p_Context->shape);
	delete (p_Context->shape);
	p_Doc->rebuildAll("group");
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("group");
	p_Doc->updateAll("polygon");
}

Command * CommandNewShape::build() {
	return new CommandNewShape(p_Doc);
}
