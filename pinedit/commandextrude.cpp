/***************************************************************************
                          commandextrude.cpp  -  description
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
#include "commandextrude.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"
#include "Polygon.h"

CommandExtrude::CommandExtrude(PinEditDoc * doc) : Command(doc) {
}

CommandExtrude::~CommandExtrude() {
}

void CommandExtrude::clearObjects() {
}

void CommandExtrude::execute(const CommandContext & context) {
	cerr << "CommandExtrude::execute" << endl;
	assert(context.shape != NULL);
	// extrude needs at least two vertices
	if (p_Doc->getSelectedVertex(1) == -1) return;
	// copy all selected vertices
	int size = context.shape->getVertex3DSize();
	vector<int> vNewVertex;
	Vertex3D * vtx;
	int index = 0;
	while ( (vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index))) != NULL) {
		Color * color = context.shape->getColor(p_Doc->getSelectedVertex(index));
		TexCoord * tex = context.shape->getTexCoord(p_Doc->getSelectedVertex(index));
		assert(color != NULL);
		assert(tex != NULL);
		int newvtx = context.shape->add(vtx->x + 0.5, vtx->y, vtx->z, 
																		color->r, color->g, color->b, color->a, tex->u , tex->v);
		vNewVertex.push_back(newvtx);
		++index;
	}

	int vtxIndexA;
	int indexA = 0;
	while ( (vtxIndexA = p_Doc->getSelectedVertex(indexA)) != -1) {
		int vtxIndexB;
		int indexB = indexA+1;
		while ( (vtxIndexB = p_Doc->getSelectedVertex(indexB)) != -1) {
			// create a new polygon if vertex A and B are following each other in the same polygon
			Polygon * poly;
			int polyindex = 0;
			int polymax = context.shape->getPolygonSize();
			while ( (poly = context.shape->getPolygon(polyindex)) != NULL && polyindex < polymax) {
				if (poly->connected(vtxIndexA, vtxIndexB)) {
					Polygon * newpoly = new Polygon(context.shape, 4);
					newpoly->add(vtxIndexA);
					newpoly->add(size + indexA); // this is the vertex extruded from vtxIndexA
					newpoly->add(size + indexB); // this is the vertex extruded from vtxIndexB
					newpoly->add(vtxIndexB);
					context.shape->add(newpoly);
					cerr << " new poly" << endl;
				}
				++polyindex;
			}
			++indexB;
		}
		++indexA;
	}

	p_Doc->clearSelectedPolygon();
	p_Doc->clearSelectedVertex();
	vector<int>::iterator iter = vNewVertex.begin();
	vector<int>::iterator end = vNewVertex.end();
	for (; iter != end; ++iter) {
		p_Doc->selectVertex(*iter);
	}
	p_Doc->doSelectPolygons();
	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->rebuildAll("polygon");
	//p_Doc->updateAll();
	p_Doc->pushUndo(this);
}

void CommandExtrude::undo() {
}

Command * CommandExtrude::build() {
	return new CommandExtrude(p_Doc);
}
