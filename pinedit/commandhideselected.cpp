/***************************************************************************
                          commandhideselected.cpp  -  description
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

// qt includes
#include <qpainter.h>
// application includes
#include "commandhideselected.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"

CommandHideSelected::CommandHideSelected(PinEditDoc * doc) : Command(doc) {
}

CommandHideSelected::~CommandHideSelected() {
}

void CommandHideSelected::execute(const CommandContext & context) {
	cerr << "CommandHideSelected::execute " << endl;
	assert(context.shape != NULL);

	int index = 0;
	int shindex = p_Doc->getSelectedVertex(index);
	for (; shindex != -1; ++index) {
		p_Doc->hideVertex(shindex);
		shindex = p_Doc->getSelectedVertex(index);
	}

	p_Doc->updateAll();
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	// this one reports for some strange reason that all are zero ???
	// but selection is made correct !!!
}

void CommandHideSelected::preview(const CommandContext & context, View2D * view2d) {
	cerr << "CommandHideSelected::preview" << endl;
}

void CommandHideSelected::undo() {
}

Command * CommandHideSelected::build() {
	return new CommandHideSelected(p_Doc);
}
