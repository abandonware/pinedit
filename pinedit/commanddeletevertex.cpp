/***************************************************************************
                          commanddeletevertex.cpp  -  description
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

// general includes
#include <vector>
#include <algorithm>
// qt includes
#include <qinputdialog.h>
// application inlucdes
#include "pineditdoc.h"
#include "commanddeletevertex.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"

CommandDeleteVertex::CommandDeleteVertex(PinEditDoc * doc) : Command(doc) {
}

CommandDeleteVertex::~CommandDeleteVertex() {
}

void CommandDeleteVertex::execute(const CommandContext & context) {
	assert(context.shape != NULL);

	vector<int> v_index;

	int index = 0;
	int vtxindex = p_Doc->getSelectedVertex(index);
	while (vtxindex >= 0) {
		v_index.push_back(vtxindex);
		++index;
		vtxindex = p_Doc->getSelectedVertex(index);
	}

	// remove vertices with descending index so we don't need to 
	// decrement indices
	sort(v_index.begin(), v_index.end());
	vector<int>::reverse_iterator riter = v_index.rbegin();
	vector<int>::reverse_iterator rend = v_index.rend();
	for(; riter != rend; ++riter) {
		cerr << "CommandDeleteVertex::execute 2.5" << endl;
		if (!context.shape->removeLooseVertex3D(*riter)) {
			cerr << "CommandDeleteVertex::execute could not remove vertex " << (*riter) << endl;
		}
	}

	p_Doc->clearSelectedVertex();
	p_Doc->setModified(true);
	p_Doc->rebuildAll();
	p_Doc->updateAll();
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	cerr << "CommandDeleteVertex::execute" << endl;
}

void CommandDeleteVertex::undo() {
}

Command * CommandDeleteVertex::build() {
	return new CommandDeleteVertex(p_Doc);
}
