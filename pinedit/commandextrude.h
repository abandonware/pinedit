/***************************************************************************
                          commandextrude.h  -  description
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

#ifndef COMMANDEXTRUDE_H
#define COMMANDEXTRUDE_H

using namespace std;

#include <vector>

#include <command.h>

class Polygon;

/** @author Henrik Enqvist IB */
class CommandExtrude : public Command  {
 public:
	CommandExtrude(PinEditDoc * doc);
	~CommandExtrude();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
	void preview (const CommandContext &, View2D *) {};
	virtual const char * type() { return "CommandExtrude"; };
 private:
	vector<int> m_vNewVertex;
	vector<Polygon*> m_vPolygon;
};

#endif
