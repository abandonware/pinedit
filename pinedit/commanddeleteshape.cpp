/***************************************************************************
                          commanddeleteshape.cpp  -  description
                             -------------------
    begin                : Sat Jun 1 2002
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
#include <qinputdialog.h>
// application inlucdes
#include "pineditdoc.h"
#include "commanddeleteshape.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Shape3D.h"

CommandDeleteShape::CommandDeleteShape(PinEditDoc * doc) : Command(doc) {
}

CommandDeleteShape::~CommandDeleteShape() {
}

void CommandDeleteShape::clearObjects() {
	delete p_Context->shape;
}

void CommandDeleteShape::execute(const CommandContext & context) {
	assert(context.shape != NULL);
	EM_CERR("CommandDeleteShape::execute");
	p_Context->copy(context);

	Group * parent = context.shape->getParent();
	assert(parent != NULL);

	parent->removeShape3D(context.shape);
	// TODO: delete(group) should reside in a 'removeFromUndoStack' function

	p_Doc->setCurrentShape(NULL);
	p_Doc->setModified(true);
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("polygon");
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
}

void CommandDeleteShape::undo() {
	EM_CERR("CommandDeleteShape::undo");
	assert(p_Context->shape != NULL);
	assert(p_Context->shape->getParent() != NULL);
	
	p_Context->shape->getParent()->addShape3D(p_Context->shape);
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("polygon");
}

Command * CommandDeleteShape::build() {
	return new CommandDeleteShape(p_Doc);
}
