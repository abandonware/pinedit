/***************************************************************************
                          commandnewgroup.cpp  -  description
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
#include <qinputdialog.h>
// application includes
#include "pineditdoc.h"
#include "commandnewgroup.h"
// emilia includes
#include "Private.h"
#include "Group.h"

CommandNewGroup::CommandNewGroup(PinEditDoc * doc) : Command(doc) {
}

CommandNewGroup::~CommandNewGroup() {
}

void CommandNewGroup::clearObjects() {
}

void CommandNewGroup::execute(const CommandContext & context) {
  assert(context.group != NULL);
  EM_CERR("CommandNewGroup::execute");
  p_Context->copy(context);
	  
	  bool ok = FALSE;
	  QString text = QInputDialog::getText(p_Doc->tr( "Enter name for group" ), 
					       p_Doc->tr("Input"), 
						     QLineEdit::Normal, QString::null, &ok, 0, 0 );
		if ( !ok || text.isEmpty() ) {
		  return;
	}
	p_Group = new Group();
	p_Group->setName(text.data());
	p_Group->setProperty(EM_GROUP_NO_BEHAVIOR);
	context.group->add(p_Group);
	p_Doc->setCurrentGroup(p_Group);
	p_Doc->setModified(true);
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("group");
	p_Doc->updateAll("polygon");
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
}

void CommandNewGroup::undo() {
	EM_CERR("CommandNewGroup::undo");
	assert(p_Context->group != NULL);
	p_Context->group->removeGroup(p_Group);
	delete p_Group;
	p_Doc->rebuildAll("group");
	p_Doc->updateAll("group");
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandNewGroup::build() {
	return new CommandNewGroup(p_Doc);
}
