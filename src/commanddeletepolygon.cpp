/***************************************************************************
                          commanddeletepolygon.cpp  -  description
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
  vector<Polygon3D*>::iterator iter = m_vPolygon.begin();
  vector<Polygon3D*>::iterator end = m_vPolygon.end();
  for (; iter != end; ++iter) {
    delete (*iter);
  }
}

void CommandDeletePolygon::execute(const CommandContext & context) {
  assert(context.shape != NULL);
  p_Context->copy(context);
  
  int polyindex = 0;
  Polygon3D * poly = p_Doc->getSelectedPolygon(polyindex);
  while (poly != NULL) {
    m_vPolygon.push_back(poly);
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
  EM_CERR("CommandDeletePolygon::execute");
}

void CommandDeletePolygon::undo() {
	EM_CERR("CommandDeletePolygon::undo");
	assert(p_Context->shape != NULL);
	vector<Polygon3D*>::iterator iter = m_vPolygon.begin();
	vector<Polygon3D*>::iterator end = m_vPolygon.end();
	for (; iter != end; ++iter) {
		p_Context->shape->add((*iter));
	}
	p_Doc->rebuildAll("polygon");
	p_Doc->updateAll("polygon");
}

Command * CommandDeletePolygon::build() {
	return new CommandDeletePolygon(p_Doc);
}
