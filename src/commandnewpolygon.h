/***************************************************************************
                          commandnewpolygon.h  -  description
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

#ifndef COMMANDNEWPOLYGON_H
#define COMMANDNEWPOLYGON_H

#include <command.h>

class Polygon3D;

/** @author Henrik Enqvist */
class CommandNewPolygon : public Command  {
 public:
	CommandNewPolygon(PinEditDoc * doc);
	~CommandNewPolygon();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
	void preview (const CommandContext &, View2D *) {};
	const char * type() { return "CommandNewPolygon"; };
 private:
	Polygon3D * p_Polygon;
};

#endif
