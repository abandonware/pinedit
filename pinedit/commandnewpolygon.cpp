/***************************************************************************
                          commandnewpolygon.cpp  -  description
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
#include "commandnewpolygon.h"
#include "pineditdoc.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"
#include "Polygon.h"

CommandNewPolygon::CommandNewPolygon(PinEditDoc * doc) : Command(doc) {
	p_Context = new CommandContext();
	p_Context->clear();
	p_Polygon = NULL;
}

CommandNewPolygon::~CommandNewPolygon() {
	delete p_Context;
}

void CommandNewPolygon::clearObjects() {
	delete p_Polygon;
}

void CommandNewPolygon::execute(const CommandContext & context) {
	assert(context.shape != NULL);
	p_Context->copy(context);
	
	p_Polygon = new Polygon(context.shape);
	
	int index = 0;
	int shindex = p_Doc->getSelectedVertex(index);
	while (shindex >= 0) {
		// this code should be in shape3d, find the vertex index in the shape
		assert(context.shape->getVertex3D(shindex) != NULL);
		p_Polygon->add(shindex);
		++index;
		shindex = p_Doc->getSelectedVertex(index);
	}
		
	// don't add to small polys
	if (index < 3) {
		delete p_Polygon;
		p_Polygon = NULL;
	} else {
		context.shape->add(p_Polygon);
		context.shape->countNormals();
		//p_Context = new CommandContext(context);
		p_Doc->doSelectPolygons();
		p_Doc->setModified(true);
		p_Doc->rebuildAll("polygon");
		p_Doc->updateAll("polygon");
		p_Doc->pushUndo(this);
	}
	cerr << "CommandNewPolygon::execute new polygon with " << index << " vertices" << endl;
}

void CommandNewPolygon::undo() {
	cerr << "CommandNewPolygon::undo" << endl;
	assert(p_Polygon != NULL);
	assert(p_Context->shape != NULL);
	p_Context->shape->removePolygon(p_Polygon);
	p_Doc->clearSelectedPolygon();
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandNewPolygon::build() {
	return new CommandNewPolygon(p_Doc);
}
