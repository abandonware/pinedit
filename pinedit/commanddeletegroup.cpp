/***************************************************************************
                          commanddeletegroup.cpp  -  description
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

// general includes
#include <iostream>
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

void CommandDeleteGroup::clearObjects() {
	delete p_Context->group;
}

void CommandDeleteGroup::execute(const CommandContext & context) {
	assert(context.group != NULL);
	p_Context->copy(context);

	Group * parent = context.group->getParent();
	assert(parent != NULL);

	parent->removeGroup(context.group);
	// TODO: delete(group) should reside in a 'removeFromUndoStack' function

	p_Doc->setCurrentGroup(NULL);
	p_Doc->setCurrentShape(NULL);
	p_Doc->setModified(true);
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("polygon");
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	cerr << "CommandDeleteGroup::execute" << endl;
}

void CommandDeleteGroup::undo() {
	cerr << "CommandDeleteGroup::undo" << endl;
	assert(p_Context->group != NULL);
	assert(p_Context->group->getParent() != NULL);
	
	p_Context->group->getParent()->add(p_Context->group);
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("polygon");
}

Command * CommandDeleteGroup::build() {
	return new CommandDeleteGroup(p_Doc);
}
