/***************************************************************************
                          commandnewshape.cpp  -  description
                             -------------------
    begin                : Thu Apr 11 2002
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

void CommandNewShape::execute(const CommandContext & context) {
	assert(context.group != NULL);

	p_Shape = new Shape3D();
	context.group->addShape3D(p_Shape);
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();
	p_Doc->setCurrentShape(p_Shape);
	p_Doc->setModified(true);
	p_Doc->rebuildAll();
	p_Doc->updateAll();
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	cerr << "CommandNewShape::execute" << endl;
}

void CommandNewShape::undo() {
	cerr << "undo for this command not implented" << endl;
}

Command * CommandNewShape::build() {
	return new CommandNewShape(p_Doc);
}
