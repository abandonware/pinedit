/***************************************************************************
                          commandpaste.cpp  -  description
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

// general includes
#include <map>
// qt includes
#include <qpainter.h>
// application includes
#include "commandpaste.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"
#include "Polygon.h"

CommandPaste::CommandPaste(PinEditDoc * doc) : Command(doc) {
	m_iUndoIndex = -1;
}

CommandPaste::~CommandPaste() {
}

void CommandPaste::clearObjects() {
}

void CommandPaste::execute(const CommandContext & context) {
	cerr << "CommandPaste::execute" << endl;
	assert(context.shape != NULL);
	p_Context->copy(context);
	m_vPolygon.clear();

	m_iUndoIndex = context.shape->getVertex3DSize();

	vector<int> vIndex;
	vector<Vertex3D> vVertex;
	vector<Color> vColor;
	vector<TexCoord> vTexCoord;
	vector<Polygon*> vPolygon;
	map<int, int> hIndex;

	p_Doc->getClipBoard(vIndex, vVertex, vColor, vTexCoord, vPolygon);
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();

	assert(vVertex.size() == vIndex.size());
	assert(vVertex.size() == vColor.size());
	assert(vVertex.size() == vTexCoord.size());
	cerr << "adding " << vVertex.size() << " vertices " << endl;

	// copy vertices to the end of the shape
	vector<Vertex3D>::iterator viter = vVertex.begin();
	vector<Vertex3D>::iterator vend = vVertex.end();
	vector<int>::iterator iiter = vIndex.begin();
	vector<Color>::iterator citer = vColor.begin();
	vector<TexCoord>::iterator titer = vTexCoord.begin();
	for (; viter != vend; ++viter, ++iiter, ++citer, ++titer) {
 		int index = context.shape->add((*viter).x + 0.5f, (*viter).y, (*viter).z,
 																	 (*citer).r, (*citer).g, (*citer).b, (*citer).a,
 																	 (*titer).u, (*titer).v);
		hIndex.insert(pair<int, int>((*iiter), index));
 		p_Doc->selectVertex(index);
	}
	
	// copy new polygons use table lookup for indices
	vector<Polygon*>::iterator piter = vPolygon.begin();
	vector<Polygon*>::iterator pend = vPolygon.end();
	for (; piter != pend; ++piter) {
		Polygon * newpoly = new Polygon(p_Context->shape);
		int index = 0;
		int vtxindex = (*piter)->getIndex(index);
		while (vtxindex != -1) {
			map<int, int>::iterator mapindex = hIndex.find(vtxindex);
			assert(mapindex != hIndex.end());
			newpoly->add((*mapindex).second);
			++index;
			vtxindex = (*piter)->getIndex(index);
		}
		p_Context->shape->add(newpoly);
		p_Doc->selectPolygon(newpoly);
		m_vPolygon.push_back(newpoly);
	}

	p_Doc->setModified(true);
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
}

void CommandPaste::undo() {
	cerr << "CommandPaste::undo" << endl;
	assert(p_Context->shape != NULL);

	// delete polygons
	vector<Polygon*>::iterator polyiter = m_vPolygon.begin();
	vector<Polygon*>::iterator polyend = m_vPolygon.end();
	for (; polyiter != polyend; ++polyiter) {
		p_Context->shape->removePolygon((*polyiter));
	}

	// delete vertices from end to undo index
	for (int a=p_Context->shape->getVertex3DSize(); a >= m_iUndoIndex; --a) {
		p_Context->shape->removeLooseVertex3D(a);
	}
	p_Doc->clearSelectedVertex();
	p_Doc->clearSelectedPolygon();

	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandPaste::build() {
	cerr << "CommandPaste::build" << endl;
	return new CommandPaste(p_Doc);
}
