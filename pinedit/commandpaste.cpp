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
	}

	/*

	Vertex3D * vtx;
	int index = 0;
	while ( (vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index))) != NULL) {
		Color * color = context.shape->getColor(p_Doc->getSelectedVertex(index));
		TexCoord * tex = context.shape->getTexCoord(p_Doc->getSelectedVertex(index));
		assert(color != NULL);
		assert(tex != NULL);
		int newvtx = context.shape->add(vtx->x + 0.5, vtx->y, vtx->z, 
																		color->r, color->g, color->b, color->a, tex->u , tex->v);
		m_vNewVertex.push_back(newvtx);
		++index;
	}

	// paste needs at least two vertices
	if (p_Doc->getSelectedVertex(1) == -1) return;
	// create a copy for each selected vertex
	int size = context.shape->getVertex3DSize();
	Vertex3D * vtx;
	int index = 0;
	while ( (vtx = context.shape->getVertex3D(p_Doc->getSelectedVertex(index))) != NULL) {
		Color * color = context.shape->getColor(p_Doc->getSelectedVertex(index));
		TexCoord * tex = context.shape->getTexCoord(p_Doc->getSelectedVertex(index));
		assert(color != NULL);
		assert(tex != NULL);
		int newvtx = context.shape->add(vtx->x + 0.5, vtx->y, vtx->z, 
																		color->r, color->g, color->b, color->a, tex->u , tex->v);
		m_vNewVertex.push_back(newvtx);
		++index;
	}

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
					newpoly->add(size + indexA); // this is the vertex pasted from vtxIndexA
					newpoly->add(size + indexB); // this is the vertex pasted from vtxIndexB
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
	*/
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
}

void CommandPaste::undo() {
	cerr << "CommandPaste::undo" << endl;
	assert(p_Context->shape != NULL);

	// delete vertices from end to undo index
	for (int a=p_Context->shape->getVertex3DSize(); a >= m_iUndoIndex; --a) {
		p_Context->shape->removeLooseVertex3D(a);
	}
	/*
	vector<Polygon*>::iterator polyiter = m_vPolygon.begin();
	vector<Polygon*>::iterator polyend = m_vPolygon.end();
	for (; polyiter != polyend; ++polyiter) {
		p_Context->shape->removePolygon((*polyiter));
	}
	*/
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandPaste::build() {
	cerr << "CommandPaste::build" << endl;
	return new CommandPaste(p_Doc);
}
