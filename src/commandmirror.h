/***************************************************************************
                          commandmirror.h  -  description
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

#ifndef COMMANDMIRROR_H
#define COMMANDMIRROR_H

using namespace std;

#include <vector>

#include <command.h>

class Polygon3D;

/** @author Henrik Enqvist */
class CommandMirror : public Command  {
 public:
	CommandMirror(PinEditDoc * doc);
	~CommandMirror();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
	void preview (const CommandContext &, View2D *) {};
	/** 0 = x, 1 = y, 2 = z; */
	void setXYZ(int xyz) { m_iXYZ = xyz; };
	const char * type() { return "CommandMirror"; };
 private:
	int m_iXYZ;
	vector<int> m_vIndex;
	vector<Polygon3D*> m_vPolygon;
};

#endif
