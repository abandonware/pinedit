/***************************************************************************
                          commandcopy.cpp  -  description
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
#include <qpainter.h>
// application includes
#include "commandcopy.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"
#include "Polygon.h"

CommandCopy::CommandCopy(PinEditDoc * doc) : Command(doc) {
}

CommandCopy::~CommandCopy() {
}

void CommandCopy::clearObjects() {
}

void CommandCopy::execute(const CommandContext & context) {
	cerr << "CommandCopy::execute" << endl;
	assert(context.shape != NULL);
	p_Context->copy(context);

	p_Doc->clearClipBoard();
	// create a copy for each selected vertex
	int size = context.shape->getVertex3DSize();
	Vertex3D * vtx;
	int index = 0;
	while ( (vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index))) != NULL) {
		Color * color = context.shape->getColor(p_Doc->getSelectedVertex(index));
		TexCoord * tex = context.shape->getTexCoord(p_Doc->getSelectedVertex(index));
		assert(color != NULL);
		assert(tex != NULL);
		p_Doc->addClipBoard(*vtx, *color, *tex);
		++index;
	}

	/*
	int vtxIndexA;
	int indexA = 0;
	while ( (vtxIndexA = p_Doc->getSelectedVertex(indexA)) != -1) {
		int vtxIndexB;
		int indexB = indexA+1;
		while ( (vtxIndexB = p_Doc->getSelectedVertex(indexB)) != -1) {
			// create a new polygon if vertex A and B are following each other in the same polygon
			// TODO this is a slow implemention
			Polygon * poly;
			int polyindex = 0;
			int polymax = context.shape->getPolygonSize();
			while ( (poly = context.shape->getPolygon(polyindex)) != NULL && polyindex < polymax) {
				if (poly->connected(vtxIndexA, vtxIndexB)) {
					Polygon * newpoly = new Polygon(context.shape, 4);
					newpoly->add(vtxIndexA);
					newpoly->add(size + indexA); // this is the vertex copyd from vtxIndexA
					newpoly->add(size + indexB); // this is the vertex copyd from vtxIndexB
					newpoly->add(vtxIndexB);
					context.shape->add(newpoly);
					m_vPolygon.push_back(newpoly);
				}
				++polyindex;
			}
			++indexB;
		}
		++indexA;
	}

	// select vertices and polygons
	p_Doc->clearSelectedPolygon();
	p_Doc->clearSelectedVertex();
	vector<int>::iterator iter = m_vNewVertex.begin();
	vector<int>::iterator end = m_vNewVertex.end();
	for (; iter != end; ++iter) {
		p_Doc->selectVertex(*iter);
	}
	p_Doc->doSelectPolygons();
	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
	*/
	p_Doc->pushUndo(this);
}

void CommandCopy::undo() {
	cerr << "CommandCopy::undo" << endl;
	assert(p_Context->shape != NULL);

	// TODO copy old clipboard
	p_Doc->clearClipBoard();
	/*
	vector<Polygon*>::iterator polyiter = m_vPolygon.begin();
	vector<Polygon*>::iterator polyend = m_vPolygon.end();
	for (; polyiter != polyend; ++polyiter) {
		p_Context->shape->removePolygon((*polyiter));
	}
	vector<int>::iterator vtxiter = m_vNewVertex.begin();
	vector<int>::iterator vtxend = m_vNewVertex.end();
	for (; vtxiter != vtxend; ++vtxiter) {
		p_Context->shape->removeLooseVertex3D((*vtxiter));
	}
	*/
}

Command * CommandCopy::build() {
	cerr << "CommandCopy::build" << endl;
	return new CommandCopy(p_Doc);
}
