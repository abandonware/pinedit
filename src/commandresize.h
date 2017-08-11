/***************************************************************************
                          commandresize.h  -  description
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

#ifndef COMMANDRESIZE_H
#define COMMANDRESIZE_H

using namespace std;

#include <vector>

#include "command.h"

#include "EMath.h"

/** @author Henrik Enqvist IB */
class CommandResize : public Command  {
 public:
	CommandResize(PinEditDoc * doc);
	~CommandResize();
	Command * build();
	void undo();
    void clearObjects() {}
	void execute(const CommandContext & context);
    void preview(const CommandContext & context, View2D * view2d, QPainter&painter);
    virtual const char * type() { return "CommandResize"; }
 private:
	vector<Vertex3D> m_vVertex;
	vector<int> m_vIndex;
};

#endif
