/***************************************************************************
                          commanddeleteshape.cpp  -  description
                             -------------------
    begin                : Sat Jun 1 2002
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

void CommandDeleteShape::execute(const CommandContext & context) {
	assert(context.shape != NULL);

	Group * parent = context.shape->getParent();
	assert(parent != NULL);

	parent->removeShape3D(context.shape);
	// TODO: delete(group) should reside in a 'removeFromUndoStack' function
	delete(context.shape);

	p_Doc->setCurrentShape(NULL);
	p_Doc->setModified(true);
	p_Doc->rebuildAll();
	p_Doc->updateAll();
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	cerr << "CommandDeleteShape::execute" << endl;
}

void CommandDeleteShape::undo() {
}

Command * CommandDeleteShape::build() {
	return new CommandDeleteShape(p_Doc);
}
