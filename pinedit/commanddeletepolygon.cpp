/***************************************************************************
                          commanddeletepolygon.cpp  -  description
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
#include "commanddeletepolygon.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"
#include "Polygon.h"

CommandDeletePolygon::CommandDeletePolygon(PinEditDoc * doc) : Command(doc) {
}

CommandDeletePolygon::~CommandDeletePolygon() {
}

void CommandDeletePolygon::clearObjects() {
	vector<Polygon*>::iterator iter = m_vPolygon.begin();
	vector<Polygon*>::iterator end = m_vPolygon.end();
	for (; iter != end; ++iter) {
		delete (*iter);
	}
}

void CommandDeletePolygon::execute(const CommandContext & context) {
	assert(context.shape != NULL);

	int polyindex = 0;
	Polygon * poly = p_Doc->getSelectedPolygon(polyindex);
	while (poly != NULL) {
		context.shape->removePolygon(poly);
		++polyindex;
		poly = p_Doc->getSelectedPolygon(polyindex);
	}

	p_Doc->clearSelectedPolygon();
	p_Doc->setModified(true);
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
	//p_Context = new CommandContext(context);
	p_Doc->pushUndo(this);
	cerr << "CommandDeletePolygon::execute" << endl;
}

void CommandDeletePolygon::undo() {
	cerr << "CommandDeletePolygon::undo" << endl;
	assert(p_Context->shape != NULL);
	vector<Polygon*>::iterator iter = m_vPolygon.begin();
	vector<Polygon*>::iterator end = m_vPolygon.end();
	for (; iter != end; ++iter) {
		p_Context->shape->add((*iter));
	}
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandDeletePolygon::build() {
	return new CommandDeletePolygon(p_Doc);
}
