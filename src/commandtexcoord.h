/***************************************************************************
                          commandtexcoord.h  -  description
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

#ifndef COMMANDTEXCOORD_H
#define COMMANDTEXCOORD_H

#include <command.h>

/** @author Henrik Enqvist IB */
class CommandTexCoord : public Command  {
 public:
	CommandTexCoord(PinEditDoc * doc);
	~CommandTexCoord();
	Command * build();
	void undo();
	void clearObjects() {};
	void execute(const CommandContext & context);
	void preview (const CommandContext &, View2D *) {};
	const char * type() { return "CommandTexCoord"; };
};

#endif
