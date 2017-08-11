/***************************************************************************
                          commandpaste.h  -  description
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

#ifndef COMMANDPASTE_H
#define COMMANDPASTE_H

using namespace std;

#include <vector>

#include <command.h>

class Polygon3D;

/** @author Henrik Enqvist IB */
class CommandPaste : public Command  {
 public:
	CommandPaste(PinEditDoc * doc);
	~CommandPaste();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
    void preview (const CommandContext &, View2D *, QPainter&) {}
    virtual const char * type() { return "CommandPaste"; }
 private:
	int m_iUndoIndex;
	//vector<int> m_vNewVertex;
	vector<Polygon3D*> m_vPolygon;
};

#endif
