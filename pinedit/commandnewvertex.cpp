/***************************************************************************
                          commandnewvertex.cpp  -  description
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

#include <iostream>

// application includes
#include "commandnewvertex.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"

CommandNewVertex::CommandNewVertex(PinEditDoc * doc) : Command(doc) {
}

CommandNewVertex::~CommandNewVertex() {
}

void CommandNewVertex::execute(const CommandContext & context) {
	assert(context.shape != NULL);

	m_VtxIndex = context.shape->add(context.x2, context.y2, context.z2);
	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll();
	p_Doc->pushUndo(this);
	cerr << "CommandNewVertex::execute " << context.x2 <<"  "<< context.y2 <<" "<< context.z2 << endl;
}

void CommandNewVertex::undo() {
	cerr << "CommandNewVertex::undo TODO" << endl;
}

Command * CommandNewVertex::build() {
	return new CommandNewVertex(p_Doc);
}
