/***************************************************************************
                          commandflip.cpp  -  description
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
#include "commandflip.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Polygon.h"
#include "Shape3D.h"

CommandFlip::CommandFlip(PinEditDoc * doc) : Command(doc) {
}

CommandFlip::~CommandFlip() {
}

void CommandFlip::execute(const CommandContext & context) {
	assert(context.shape != NULL);

	int index = 0;
	Polygon * poly = p_Doc->getSelectedPolygon(index);
	while (poly != NULL) {
		// oooh, this is a ugly and slow implementation
		vector<int> vIndex;
		vector<int>::reverse_iterator riter = poly->m_vIndex.rbegin();
		vector<int>::reverse_iterator rend = poly->m_vIndex.rend();
		// TODO flip color and texcoord or not?
		for (; riter != rend; riter++) {
			vIndex.push_back(*riter);
		}			
		vector<int>::iterator iter = vIndex.begin();
		vector<int>::iterator end = vIndex.end();
		poly->m_vIndex.clear();
		for (; iter != end; iter++) {
			poly->m_vIndex.push_back(*iter);
		}
		poly->countNormal();
		index++;
		poly = p_Doc->getSelectedPolygon(index);
	}
	context.shape->countNormals();

	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll();
	p_Doc->pushUndo(this);
	cerr << "flipped polygons" << endl;
}

void CommandFlip::undo() {
}

Command * CommandFlip::build() {
	return new CommandFlip(p_Doc);
}
