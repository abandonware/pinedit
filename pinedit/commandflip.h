/***************************************************************************
                          commandflip.h  -  description
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

#ifndef COMMANDFLIP_H
#define COMMANDFLIP_H

#include <command.h>

/** @author Henrik Enqvist IB */
class CommandFlip : public Command  {
 public:
	CommandFlip(PinEditDoc * doc);
	~CommandFlip();
	Command * build();
	void undo();
	void execute(const CommandContext & context);
	virtual const char * type() { return "CommandFlip"; };
};

#endif
