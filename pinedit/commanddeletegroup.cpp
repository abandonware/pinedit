/***************************************************************************
                          commanddeletegroup.cpp  -  description
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
#include "commanddeletegroup.h"
// emilia includes
#include "Group.h"

CommandDeleteGroup::CommandDeleteGroup(PinEditDoc * doc) : Command(doc) {
}

CommandDeleteGroup::~CommandDeleteGroup() {
}

void CommandDeleteGroup::execute(const CommandContext & context) {
	assert(context.group != NULL);

	Group * parent = context.group->getParent();
	assert(parent != NULL);

	parent->removeGroup(context.group);
	// TODO: delete(group) should reside in a 'removeFromUndoStack' function
	delete(context.group);

	p_Doc->setCurrentGroup(NULL);
	p_Doc->setCurrentShape(NULL);
	p_Doc->setModified(true);
	p_Doc->rebuildAll();
	p_Doc->updateAll();
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	cerr << "CommandDeleteGroup::execute" << endl;
}

void CommandDeleteGroup::undo() {
}

Command * CommandDeleteGroup::build() {
	return new CommandDeleteGroup(p_Doc);
}
