/***************************************************************************
                          commandflip.cpp  -  description
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

void CommandFlip::clearObjects() {
}

void CommandFlip::execute(const CommandContext & context) {
	EM_CERR("CommandFlip::execute");
	assert(context.shape != NULL);
	p_Context->copy(context);

	int index = 0;
	Polygon3D * poly = p_Doc->getSelectedPolygon(index);
	while (poly != NULL) {
		m_vPolygon.push_back(poly);
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
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
}

void CommandFlip::undo() {
	EM_CERR("CommandFlip::undo");
	assert(p_Context->shape != NULL);
	vector<Polygon3D*>::iterator polyiter = m_vPolygon.begin();
	vector<Polygon3D*>::iterator polyend = m_vPolygon.end();

	for (; polyiter != polyend; ++polyiter) {
		// oooh, this is a ugly and slow implementation
		vector<int> vIndex;
		vector<int>::reverse_iterator riter = (*polyiter)->m_vIndex.rbegin();
		vector<int>::reverse_iterator rend = (*polyiter)->m_vIndex.rend();
		// TODO flip color and texcoord or not?
		for (; riter != rend; riter++) {
			vIndex.push_back(*riter);
		}			
		vector<int>::iterator iter = vIndex.begin();
		vector<int>::iterator end = vIndex.end();
		(*polyiter)->m_vIndex.clear();
		for (; iter != end; iter++) {
			(*polyiter)->m_vIndex.push_back(*iter);
		}
		(*polyiter)->countNormal();
	}
	p_Context->shape->countNormals();
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandFlip::build() {
	EM_CERR("CommandFlip::bulld");
	return new CommandFlip(p_Doc);
}
