/***************************************************************************
                          commandnewbehavior.cpp  -  description
                             -------------------
    begin                : Fri Apr 12 2002
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

// application includes
#include "pineditdoc.h"
#include "commandnewbehavior.h"
// emilia includes
#include "Private.h"
#include "Group.h"
#include "Engine.h"
#include "BumperBehavior.h"
#include "StateBehavior.h"
#include "ArmBehavior.h"
#include "FakeModuleBehavior.h"
#include "Pinball.h"

CommandNewBehavior::CommandNewBehavior(PinEditDoc * doc) : Command(doc) {
	p_Behavior = NULL;
	m_iBehaviorType = 0;
}

CommandNewBehavior::~CommandNewBehavior() {
}

void CommandNewBehavior::clearObjects() {
}

void CommandNewBehavior::execute(const CommandContext & context) {
	cerr << "CommandNewBehavior::execute" << endl;
	assert(context.group != NULL);

	switch (m_iBehaviorType) {
	case PBL_TYPE_BUMPERBEH:
		p_Behavior = new BumperBehavior();
		break;
	case PBL_TYPE_ARMBEH:
		p_Behavior = new ArmBehavior(true);
		break;
	case PBL_TYPE_STATEBEH:
		p_Behavior = new StateBehavior();
		break;
	case PBL_TYPE_FAKEMODULEBEH:
		p_Behavior = new FakeModuleBehavior("");
		break;
	default:
		p_Behavior = NULL;
	}
	context.group->setBehavior(p_Behavior);

	p_Doc->setModified(true);
	p_Doc->rebuildAll("group");
	//p_Doc->updateAll();
	p_Doc->pushUndo(this);
	//p_Context = new CommandContext(context);
	cerr << "CommandNewBehavior::execute done" << endl;
}

void CommandNewBehavior::undo() {
	cerr << "CommandNewBehavior::undo TODO" << endl;
}

Command * CommandNewBehavior::build() {
	return new CommandNewBehavior(p_Doc);
}

