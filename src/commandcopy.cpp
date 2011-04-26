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
  EM_CERR("CommandCopy::execute");
  assert(context.shape != NULL);
  p_Context->copy(context);

  p_Doc->clearClipBoard();
  // create a copy for each selected vertex
  int index = 0;
  int vtxindex = p_Doc->getSelectedVertex(index);
  while (vtxindex != -1) {
    Vertex3D * vtx = context.shape->getVertex3D(vtxindex);
    Color * color = context.shape->getColor(vtxindex);
    TexCoord * tex = context.shape->getTexCoord(vtxindex);
    assert(vtx != NULL);
    assert(color != NULL);
    assert(tex != NULL);
    p_Doc->addClipBoard(vtxindex, *vtx, *color, *tex);
    ++index;
    vtxindex = p_Doc->getSelectedVertex(index);
  }

  index = 0;
  Polygon3D * poly = p_Doc->getSelectedPolygon(index);
  while (poly != NULL) {
    p_Doc->addClipBoard(poly);
    ++index;
    poly = p_Doc->getSelectedPolygon(index);
  }

  p_Doc->pushUndo(this);
}

void CommandCopy::undo() {
  EM_CERR("CommandCopy::undo");
  assert(p_Context->shape != NULL);

  // TODO copy old clipboard
  p_Doc->clearClipBoard();
}

Command * CommandCopy::build() {
  EM_CERR("CommandCopy::build");
  return new CommandCopy(p_Doc);
}
