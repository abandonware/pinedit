/***************************************************************************
                          commanddeletevertex.cpp  -  description
                             -------------------
    begin                : Sat Jun 1 2002
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

using namespace std;

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

void CommandDeleteVertex::clearObjects() {
}

void CommandDeleteVertex::execute(const CommandContext & context) {
	assert(context.shape != NULL);
	EM_CERR("CommandDeleteVertex::execute");
	p_Context->copy(context);

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
		assert(context.shape->getVertex3D(*riter) != NULL);
		Vertex3D vtx = *(context.shape->getVertex3D(*riter));
		Color color = *(context.shape->getColor(*riter));
		TexCoord texcoord = *(context.shape->getTexCoord(*riter));
		if (context.shape->removeLooseVertex3D(*riter)) {
			m_vVertex.push_back(vtx);
			m_vColor.push_back(color);
			m_vTexCoord.push_back(texcoord);
			m_vIndex.push_back(*riter);
		} else {
			EM_CERR("CommandDeleteVertex::execute could not remove vertex " << (*riter));
		}
	}

	p_Doc->clearSelectedVertex();
	p_Doc->setModified(true);
	//p_Doc->rebuildAll("");
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
}

void CommandDeleteVertex::undo() {
	assert(m_vVertex.size() == m_vIndex.size());
	assert(p_Context->shape != NULL);
	EM_CERR("CommandDeleteVertex::undo");
	EM_CERR(m_vVertex.size());
	// insert vertices in ascending order, note they are in descending order in vector
	vector<int>::reverse_iterator rindexiter = m_vIndex.rbegin();
	vector<int>::reverse_iterator rindexend = m_vIndex.rend();
	vector<Vertex3D>::reverse_iterator rvtxiter = m_vVertex.rbegin();
	vector<Color>::reverse_iterator rcoloriter = m_vColor.rbegin();
	vector<TexCoord>::reverse_iterator rtexiter = m_vTexCoord.rbegin();
	for (; rindexiter != rindexend; ++rindexiter, ++rvtxiter, ++rcoloriter, ++rtexiter) {
		p_Context->shape->addAt((*rindexiter), (*rvtxiter).x, (*rvtxiter).y, (*rvtxiter).z,
														(*rcoloriter).r, (*rcoloriter).g, (*rcoloriter).b, (*rcoloriter).a,
														(*rtexiter).u, (*rtexiter).v);
	}
	p_Doc->updateAll("polygon");
}

Command * CommandDeleteVertex::build() {
	return new CommandDeleteVertex(p_Doc);
}
