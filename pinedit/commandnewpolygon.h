/***************************************************************************
                          commandnewpolygon.h  -  description
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

#ifndef COMMANDNEWPOLYGON_H
#define COMMANDNEWPOLYGON_H

#include <command.h>

/**
  *@author Henrik Enqvist IB
  */

class CommandNewPolygon : public Command  {
 public:
	CommandNewPolygon(PinEditDoc * doc);
	~CommandNewPolygon();
	Command * build();
	void undo();
	void execute(const CommandContext & context);
	const char * type() { return "CommandNewPolygon"; };
};

#endif
