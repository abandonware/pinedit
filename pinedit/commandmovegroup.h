/***************************************************************************
                          commandmovegroup.h  -  description
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

#ifndef COMMANDMOVEGROUP_H
#define COMMANDMOVEGROUP_H

#include <command.h>

/** @author Henrik Enqvist IB */
class CommandMoveGroup : public Command  {
 public:
	CommandMoveGroup(PinEditDoc * doc);
	~CommandMoveGroup();
	Command * build();
	void undo();
	void clearObjects();
	void execute(const CommandContext & context);
	void preview(const CommandContext & context, View2D * view2d);
	const char * type() { return "CommandMoveGroup"; };
};

#endif
