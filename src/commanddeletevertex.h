/***************************************************************************
                          commanddeletevertex.h  -  description
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



#ifndef COMMANDDELETEVERTEX_H
#define COMMANDDELETEVERTEX_H

using namespace std;

#include <command.h>
#include "EMath.h"

class Group;

class CommandDeleteVertex : public Command  {
 public:
	CommandDeleteVertex(PinEditDoc * doc);
	~CommandDeleteVertex();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
    void preview(const CommandContext &, View2D *, QPainter&) {}
    const char * type() { return "CommandDeleteVertex"; }
 private:
	vector<Vertex3D> m_vVertex;
	vector<Color> m_vColor;
	vector<TexCoord> m_vTexCoord;
	vector<int> m_vIndex;
};

#endif
