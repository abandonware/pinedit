/***************************************************************************
                          commandtexcoord.cpp  -  description
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
#include <math.h>
// qt includes
#include <qpainter.h>
// application includes
#include "commandtexcoord.h"
#include "pineditdoc.h"
#include "view2d.h"
// emilia includes
#include "Private.h"
#include "Shape3D.h"
#include "EMath.h"

CommandTexCoord::CommandTexCoord(PinEditDoc * doc) : Command(doc) {
}

CommandTexCoord::~CommandTexCoord() {
}

void CommandTexCoord::execute(const CommandContext & context) {
	EM_CERR("CommandTexCoord::execute ");
	assert(context.shape != NULL);

	switch (context.type) {
	case XY: {
		EM_CERR("CommandTexCoord::execute XY");
		// find min max x and min max y
		float minx = 9999, maxx = -9999, miny = 9999, maxy = -9999; 
		int index = 0;
		int shindex;
		while ( (shindex = p_Doc->getSelectedVertex(index)) != -1) {
			Vertex3D * vtx = context.shape->getVertex3D(shindex);
			assert(vtx != NULL);
			if (vtx->x < minx) minx = vtx->x;
			if (vtx->x > maxx) maxx = vtx->x;
			if (vtx->y < miny) miny = vtx->y;
			if (vtx->y > maxy) maxy = vtx->y;
			++index;
		}
		float xoffset = maxx - minx;
		float yoffset = maxy - miny;
		index = 0;
		while ( (shindex = p_Doc->getSelectedVertex(index)) != -1) {
			Vertex3D * vtx = context.shape->getVertex3D(shindex);
			TexCoord * texcoord = context.shape->getTexCoord(shindex);
			assert(vtx != NULL);
			assert(texcoord != NULL);
			texcoord->u = (vtx->x - minx)/xoffset;
			texcoord->v = (vtx->y - miny)/yoffset;
			++index;
		}
	} break;
	case XZ: {
		EM_CERR("CommandTexCoord::execute XZ");
		// find min max x and min max y
		float minx = 9999, maxx = -9999, minz = 9999, maxz = -9999; 
		int index = 0;
		int shindex;
		while ( (shindex = p_Doc->getSelectedVertex(index)) != -1) {
			Vertex3D * vtx = context.shape->getVertex3D(shindex);
			assert(vtx != NULL);
			if (vtx->x < minx) minx = vtx->x;
			if (vtx->x > maxx) maxx = vtx->x;
			if (vtx->z < minz) minz = vtx->z;
			if (vtx->z > maxz) maxz = vtx->z;
			++index;
		}
		float xoffset = maxx - minx;
		float zoffset = maxz - minz;
		index = 0;
		while ( (shindex = p_Doc->getSelectedVertex(index)) != -1) {
			Vertex3D * vtx = context.shape->getVertex3D(shindex);
			TexCoord * texcoord = context.shape->getTexCoord(shindex);
			assert(vtx != NULL);
			assert(texcoord != NULL);
			texcoord->u = (vtx->x - minx)/xoffset;
			texcoord->v = (vtx->z - minz)/zoffset;
			++index;
		}
	} break;
	case ZY: {
		EM_CERR("CommandTexCoord::execute ZY");
		// find min max x and min max y
		float minz = 9999, maxz = -9999, miny = 9999, maxy = -9999; 
		int index = 0;
		int shindex;
		while ( (shindex = p_Doc->getSelectedVertex(index)) != -1) {
			Vertex3D * vtx = context.shape->getVertex3D(shindex);
			assert(vtx != NULL);
			if (vtx->z < minz) minz = vtx->z;
			if (vtx->z > maxz) maxz = vtx->z;
			if (vtx->y < miny) miny = vtx->y;
			if (vtx->y > maxy) maxy = vtx->y;
			++index;
		}
		float zoffset = maxz - minz;
		float yoffset = maxy - miny;
		index = 0;
		while ( (shindex = p_Doc->getSelectedVertex(index)) != -1) {
			Vertex3D * vtx = context.shape->getVertex3D(shindex);
			TexCoord * texcoord = context.shape->getTexCoord(shindex);
			assert(vtx != NULL);
			assert(texcoord != NULL);
			texcoord->u = (vtx->z - minz)/zoffset;
			texcoord->v = (vtx->y - miny)/yoffset;
			++index;
		}
	} break;
	}

	//p_Context = new CommandContext(context);
	p_Doc->setModified(true);
	p_Doc->updateAll("polygon");
	p_Doc->pushUndo(this);
}

void CommandTexCoord::undo() {
}

Command * CommandTexCoord::build() {
	CommandTexCoord * command =  new CommandTexCoord(*this);
	return command;
}
